#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <vector>


#include <iostream>

using namespace std;

#define sX 12
#define sY 16

int trig[2]={5,10};
int echo[2]={4,11};
int mapa[sX][sY];
int miy=-1;
int mix=-1;

void setup(){
	fprintf (stderr, "seteando\n") ;
	  if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;

  }


	for (int i=0; i<2;i++){
    	pinMode(trig[i],OUTPUT);
	pinMode(echo[i],INPUT);
	digitalWrite(trig[i],LOW);

	}
fprintf (stderr, "seteo completo\n") ;

	delay(30);
}

int getCM(int i){

    if(i<0 || i>2)
        return -2;

	long travelTime;
	int distance;

	digitalWrite(trig[i],HIGH);
	delayMicroseconds(20);
	digitalWrite(trig[i],LOW);

	long start1 = micros();
	while(digitalRead(echo[i]) == LOW)
	{
		if(micros() - start1>2000)
		{
		digitalWrite(trig[i],HIGH);
		delayMicroseconds(20);
		digitalWrite(trig[i],LOW);

		}
	}

	long startTime = micros();
	while(digitalRead(echo[i])==HIGH);
	 {

	travelTime = micros() - startTime;
	 if(travelTime > 58*600)
      	 return -1;
	 }


	distance = travelTime/58;

	return distance;
}


float AlinControl(int dif){

double Kp = 0.8;

if( abs(dif)<=1 )
    return 0;

float alin = Kp*dif;
if(abs(alin)<5)
return alin;

else
{if(alin>0)return 5;
else return -5;}



}

void initmap(){
// 1 vaca, 2 mesa vacios, 3 mesa llenos, 4 tanque



// mesa vacios

mapa[10][7]=2;
mapa[11][7]=2;
mapa[10][8]=2;
mapa[11][8]=2;


//mesa llenos

mapa[0][7]=3;
mapa[1][7]=3;
mapa[0][8]=3;
mapa[1][8]=3;

}

void printmap(){

    miy=0;
    mix=0;
for (int y=0; y<sY ;y++ ){

for (int x=0; x<sX ;x++ ){

    if(x==mix && y==miy)
    fprintf (stderr, "T") ;
    else
	fprintf (stderr, "%i",mapa[x][y]) ;
	}

	fprintf (stderr, "\n") ;
}
}

void OneGrid(){
//serialPrintf (fd, "V%f\n",w) ;
delay(1000); ///calcular tiempo que tarda
//serialPrintf (fd, "V0\n",w) ;

}

int MinDistIndex(int dist[sX][sY], bool visited[sX][sY]){
	int mind=1000;
	int min_ind;
	 for (int y=0; y<sY ;y++ ){

        for (int x=0; x<sX ;x++ ){
	
	if(visited[x][y]==false && dist[x][y]<mind )
	{
	mind=dist[x][y];
	min_ind=y*sX+x;
	}
	}
	}

	return min_ind;
}

void Ruta(int destX, int destY){

    int values[12][16];
    int prev[12][16];
    bool visited[12][16];
	


    for (int y=0; y<sY ;y++ ){

        for (int x=0; x<sX ;x++ ){

            if(x==mix && y==miy)
            {values[x][y]=0;
		visited[x][y]=false;}
            else
            {values[x][y]=1000;
            if(mapa[x][y]==0){
            int aux[2]={x,y};
            visited[x][y]=false;}}

		prev[x][y]=-1;
            }


        }

    int curX=mix;
    int curY=miy;

	while(1){

		
	int ind=MinDistIndex(values, visited);
	int x=ind%sX;
	int y=(int)ind/sX;
	visited[x][y]=true;


	//fprintf (stderr, "x:%i/ y: %i ",x,y) ;
	
	if(x==destX && y==destY) {
		fprintf (stderr, "ruta\n") ;
		
		int ind_=ind;
		while(1)
		{	
			int x_=ind_%sX;
			int y_=(int)ind_/sX;
			fprintf (stderr, "x:%i/ y: %i ",x_,y_) ;
			if (x_==mix && y_== miy) break;
			ind_=prev[x_][y_];
		}
	break;
	}
	
	//calcular distancias de vecinos
	
	//vecino de arriba
	if(mapa[x][y-1]==0 && visited[x][y-1]==false && values[x][y]+1<values[x][y-1] && y-1>=0)
	{values[x][y-1]=values[x][y]+1;
	prev[x][y-1]=ind;}

	//vecino de abajo
	if(mapa[x][y+1]==0 && visited[x][y+1]==false && values[x][y]+1<values[x][y+1] && y+1<sY)
	{values[x][y+1]=values[x][y]+1;
	prev[x][y+1]=ind;}

	//vecino derecha
	if(mapa[x+1][y]==0 && visited[x+1][y]==false && values[x][y]+1<values[x+1][y] && x+1<sX)
	{values[x+1][y]=values[x][y]+1;
	prev[x+1][y]=ind;}

	//vecino izquierda
	if(mapa[x-1][y]==0 && visited[x-1][y]==false && values[x][y]+1<values[x-1][y]&& x-1>=0)
	{values[x-1][y]=values[x][y]+1;	
	prev[x-1][y]=ind;}
	

	}
}






int main(void){

initmap();

printmap();

Ruta(10,12);

fprintf (stderr, "Comenzar\n") ;
int fd ;

  if ((fd = serialOpen ("/dev/ttyUSB0", 9600)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    //return 1 ;
  }

fprintf (stderr, "Hola Mundos\n") ;

setup();


fprintf (stderr, "bkn\n") ;
//serialPrintf (fd, "HOLA ARDUINO, habla la raspi\n") ;

while(1){


int DistCD=getCM(0);
//delay(30);
int DistCI=getCM(1);


int Dif = DistCD-DistCI;
//fprintf (stderr,"Distance: %icm\n");
fprintf (stderr,"Distance: %icm Distance2: %icm Difference: %icm\n", DistCI,DistCD, Dif);

//fprintf (stderr,"");

if(DistCD<0 || DistCI<0 || abs(Dif)>20) continue;

float w=AlinControl(Dif);
fprintf (stderr,"Vel: %fcm\n", w);


serialPrintf (fd, "W%f\n",w) ;


}

  return 0 ;

}
