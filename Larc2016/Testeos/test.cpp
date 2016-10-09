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
int numMov;
int lastMovInd;
int miy=-1;
int mix=-1;
int mio=0;

std::vector< int*> route;

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
    mio=2;

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
    fprintf (stderr,"uno adelante\n") ;
//serialPrintf (fd, "V%f\n",w) ;
delay(1000); ///calcular tiempo que tarda
//serialPrintf (fd, "V0\n",w) ;

}

void GiroDer(){
    fprintf (stderr,"uno derecha\n") ;
//serialPrintf (fd, "V%f\n",w) ;
delay(1000); ///calcular tiempo que tarda
//serialPrintf (fd, "V0\n",w) ;

}

void GiroIzq(){
    fprintf (stderr,"uno izquierda\n") ;
//serialPrintf (fd, "V%f\n",w) ;
delay(1000); ///calcular tiempo que tarda
//serialPrintf (fd, "V0\n",w) ;

}

bool ValidMov(int x, int  y, int o, int tipo){

	if (tipo == 0) // avanzar
	{
		return true;

	}

	else if (tipo == 1) // giro a la derecha
	{
		if (o == 0){
			if (x<1 || y>sY - 2) return false;

			else if (mapa[x - 1][y] != 0 || mapa[x - 1][y + 1] != 0) return false;

			else return true;

		}

		else if (o == 1){
			if (x<1 || y<1) return false;

			else if (mapa[x - 1][y-1] != 0 || mapa[x ][y - 1] != 0) return false;

			else return true;

		}

		else if (o == 2){
			if (x>sX-2) return false;

			else if (mapa[x + 1][y - 1] != 0 || mapa[x+1][y] != 0) return false;

			else return true;

		}

		else {
			if (y>sY-2) return false;

			else if (mapa[x + 1][y + 1] != 0 || mapa[x][y + 1] != 0) return false;

			else return true;

		}
	}


	else if (tipo == 2) // giro a la izquierda
	{
		if (o == 0){
			if (x<sX-2 ) return false;

			else if (mapa[x + 1][y+1] != 0 || mapa[x + 1][y] != 0) return false;

			else return true;

		}

		else if (o == 1){
			if (x<1 || y>sY-2) return false;

			else if (mapa[x - 1][y + 1] != 0 || mapa[x][y + 1] != 0) return false;

			else return true;

		}

		else if (o == 2){
			if (x>sX - 2) return false;

			else if (mapa[x - 1][y - 1] != 0 || mapa[x - 1][y] != 0) return false;

			else return true;

		}

		else {
			if (y<1) return false;

			else if (mapa[x + 1][y - 1] != 0 || mapa[x][y - 1] != 0) return false;

			else return true;

		}
	}

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

void Ruta(int destX, int destY, int destO){

    int values[12][16][4];
    //int prev[12][16][4];

    bool visited[12][16][4];

//    vector< int* > route;
    route.clear();

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
		lastMovInd=ind;
		numMov=0;
		while(1)
		{
		numMov++;

        int o_=(int) ind_/(sX*sY);
        int x_=(ind_%(sX*sY))%sX;
        int y_=(int)(ind_%(sX*sY))/sX;

        int aux[3]={x_,y_,o_};


        fprintf (stderr, "x:%i y: %i o: %i \n",x_,y_,o_) ;
		if (x_==mix && y_== miy && o_==mio) break;

			ind_=prev[x_][y_][o_];
			 route.push_back(aux);
		}

        break;
	}

    /*	if(values[x][y][0]==1000) {
            vector<int*> nada;
            return nada;}*/

	//calcular distancias de vecinos

	bool derOk = ValidMov(x, y, o, 1);
	bool izqOk = ValidMov(x, y, o, 2);

	//girar derecha
	if(derOk && mapa[x][y]==0 && visited[x][y][o+1]==false && values[x][y][o]+2<values[x][y][o+1] && o+1<4)
	{values[x][y][o+1]=values[x][y][o]+2;
	prev[x][y][o+1]=ind;}

	//girar derecha
	if(derOk && mapa[x][y]==0 && visited[x][y][0]==false && values[x][y][o]+2<values[x][y][0] && o==3)
	{values[x][y][0]=values[x][y][o]+2;
	prev[x][y][0]=ind;}

    //girar izquierda
	if(izqOk && mapa[x][y]==0 && visited[x][y][o-1]==false && values[x][y][o]+2<values[x][y][o-1] && o-1>0)
	{values[x][y][o-1]=values[x][y][o]+2;
	prev[x][y][o-1]=ind;}

	    //girar izquierda
	if(izqOk && mapa[x][y]==0 && visited[x][y][3]==false && values[x][y][o]+2<values[x][y][3] && o==0)
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


//return route;

}

void FollowRoute(){//std::vector<int*> route){

    fprintf (stderr, "llegó la ruta es\n") ;
    int curro=mio;

	int ruta[numMov][3];
	int ind_=lastMovInd;
	int i=numMov-1;
	while(1)
		{

       		int o_=(int) ind_/(sX*sY);
	        int x_=(ind_%(sX*sY))%sX;
        	int y_=(int)(ind_%(sX*sY))/sX;

        	//fprintf (stderr, "i: %i x:%i y: %i o: %i \n",i,x_,y_,o_) ;
		if (x_==mix && y_== miy && o_==mio) break;

			 ruta[i][0]=x_;
			 ruta[i][1]=y_;
			 ruta[i][2]=o_;
		i--;

		ind_=prev[x_][y_][o_];
		}



	for(i=1; i<numMov; i++){

	fprintf (stderr, "i: %i x:%i y: %i o: %i \n",i,ruta[i][0],ruta[i][1],ruta[i][2]) ;
        if(curro==ruta[i][2])
            OneGrid();

        else if(ruta[i][2]==curro+1)
            GiroDer();

        else if(ruta[i][2]==curro-1)
            GiroIzq();

        else if(ruta[i][2]==0)
            GiroDer();

        else if(ruta[i][2]==3)
            GiroIzq();


        curro=ruta[i][2];

    }

}


void FindPos(int dist01, int dist02, int dist1, int dist2, int dist3){
	/*
	int totalrx, totalry, meanin;

	meanin = (dist01 + dist02) / 2;

	totalrx = 25 + dist1 + dist3;
	totalry = 33 + dist2 + meanin;

	if (abs(totalrx-200)/200 <0.1) //probablemente rx está en el eje x

	if (abs(totalrx - 300) / 300 <0.1) //probablemente rx está en el eje y

	if (abs(totalry - 200) / 200 <0.1) //probablemente rx está en el eje x

	if (abs(totalry - 300) / 300 <0.1) //probablemente rx está en el eje y
	*/
}


int main(void){
	
	initmap();

	setPos();

	printmap();

	//vector<int*> ruta=Ruta(11,15,2);
	//FollowRoute(ruta);


	Ruta(9,3,2);
	FollowRoute();
	/*

	fprintf (stderr, "fin") ;

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


	serialPrintf (fd, "W%f\n",w) ;}*/

	return 1;
}
