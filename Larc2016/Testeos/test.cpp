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
int prev[sX][sY][4];
int miy=-1;
int mix=-1;
int mio=0;

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

void setPos(){
    miy=0;
    mix=0;
    mio=0;

}

void printmap(){
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
    fprintf (stderr,"uno adelnate") ;
//serialPrintf (fd, "V%f\n",w) ;
delay(1000); ///calcular tiempo que tarda
//serialPrintf (fd, "V0\n",w) ;

}

void GiroDer(){
    fprintf (stderr,"uno derecha") ;
//serialPrintf (fd, "V%f\n",w) ;
delay(1000); ///calcular tiempo que tarda
//serialPrintf (fd, "V0\n",w) ;

}

void GiroIzq(){
    fprintf (stderr,"uno izquierda") ;
//serialPrintf (fd, "V%f\n",w) ;
delay(1000); ///calcular tiempo que tarda
//serialPrintf (fd, "V0\n",w) ;

}

int MinDistIndex(int dist[sX][sY][4], bool visited[sX][sY][4]){
	int mind=1000;
	int min_ind;
	 for (int y=0; y<sY ;y++ ){

        for (int x=0; x<sX ;x++ ){
                for (int o=0; o<4; o++ ){

            if(visited[x][y][o]==false && dist[x][y][o]<mind )
            {
            mind=dist[x][y][o];
            min_ind=y*sX+x+o*(sX*sY);
            }
        }
        }
	 }
	return min_ind;
}

vector<int*> Ruta(int destX, int destY, int destO){

    int values[12][16][4];
    //int prev[12][16][4];

    bool visited[12][16][4];

    vector< int* > route;

    for (int y=0; y<sY ;y++ ){

        for (int x=0; x<sX ;x++ ){

		for(int o=0; o<4; o++){

	            if(x==mix && y==miy && o==mio)
	            {values[x][y][o]=0;
                visited[x][y][o]=false;}
	            else
	            {values[x][y][o]=1000;
	            if(mapa[x][y]==0){

	            visited[x][y][o]=false;}
	            }

			prev[x][y][o]=-1;
	            }


	        }
	}


	while(1){


	int ind=MinDistIndex(values, visited);
    int o=(int) ind/(sX*sY);

	int x=(ind%(sX*sY))%sX;
	int y=(int)(ind%(sX*sY))/sX;
	visited[x][y][o]=true;


	//fprintf (stderr, "x:%i/ y: %i ",x,y) ;

	if(x==destX && y==destY && o==destO) {
		fprintf (stderr, "la ruta es\n") ;

		int ind_=ind;
		while(1)
		{
        int o_=(int) ind_/(sX*sY);
        int x_=(ind_%(sX*sY))%sX;
        int y_=(int)(ind_%(sX*sY))/sX;

        int aux[3]={x_,y_,o_};


        route.push_back(aux);

        fprintf (stderr, "x:%i y: %i o: %i \n",x_,y_,o_) ;
		if (x_==mix && y_== miy && o_==mio) break;
			ind_=prev[x_][y_][o_];
		}

        break;
	}

	if(values[x][y][0]==1000) {
            vector<int*> nada;
            return nada;}

	//calcular distancias de vecinos

	//girar derecha
	if(mapa[x][y]==0 && visited[x][y][o+1]==false && values[x][y][o]+2<values[x][y][o+1] && o+1<4)
	{values[x][y][o+1]=values[x][y][o]+2;
	prev[x][y][o+1]=ind;}

	//girar derecha
	if(mapa[x][y]==0 && visited[x][y][0]==false && values[x][y][o]+2<values[x][y][0] && o==3)
	{values[x][y][0]=values[x][y][o]+2;
	prev[x][y][0]=ind;}

    //girar izquierda
	if(mapa[x][y]==0 && visited[x][y][o-1]==false && values[x][y][o]+2<values[x][y][o-1] && o-1>0)
	{values[x][y][o-1]=values[x][y][o]+2;
	prev[x][y][o-1]=ind;}

	    //girar izquierda
	if(mapa[x][y]==0 && visited[x][y][3]==false && values[x][y][o]+2<values[x][y][3] && o==0)
	{values[x][y][3]=values[x][y][o]+2;
	prev[x][y][3]=ind;}

	///AVANZAR 1


	//vecino de arriba
	if(mapa[x][y-1]==0 && visited[x][y-1][o]==false && values[x][y][o]+1<values[x][y-1][o] && y-1>=0 && o==0)
	{values[x][y-1][o]=values[x][y][o]+1;
	prev[x][y-1][o]=ind;}

	//vecino de abajo
	if(mapa[x][y+1]==0 && visited[x][y+1][o]==false && values[x][y][o]+1<values[x][y+1][o] && y+1<sY && o ==2)
	{values[x][y+1][o]=values[x][y][o]+1;
	prev[x][y+1][o]=ind;}

	//vecino derecha
	if(mapa[x+1][y]==0 && visited[x+1][y][o]==false && values[x][y][o]+1<values[x+1][y][o] && x+1<sX&& o==1)
	{values[x+1][y][o]=values[x][y][o]+1;
	prev[x+1][y][o]=ind;}

	//vecino izquierda
	if(mapa[x-1][y]==0 && visited[x-1][y][o]==false && values[x][y][o]+1<values[x-1][y][o]&& x-1>=0 && o==3)
	{values[x-1][y][o]=values[x][y][o]+1;
	prev[x-1][y][o]=ind;}


	}
return route;

}

void FollowRoute(vector<int*> route){
    int curro=mio;

    while(!route.empty()){

        //int pos[3]=route.back();
        int* pos=route.back();

        if(curro==pos[2])
            OneGrid();

        else if(pos[2]+1==curro)
            GiroDer();

        else if(pos[2]-1==curro)
            GiroIzq();

        else if(pos[2]==0)
            GiroDer();

        else if(pos[2]==0)
            GiroIzq();


        curro=pos[2];
            route.pop_back();
    }

}





int main(void){

initmap();

setPos();

printmap();

vector<int*> ruta=Ruta(11,15,2);
FollowRoute(ruta);

}
