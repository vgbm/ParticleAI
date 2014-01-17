#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> 

#define numMoves 14
#define goalX 10
#define goalY 2

typedef struct{

	int pX;
	int pY;
	int moves[numMoves];
	
} Particle;

typedef enum{

	LEFT=1,
	RIGHT,
	UP,
	DOWN
	
} Direction;

Particle makeMoveList(Particle p){

	int i;
	Direction dir;
	
	for(i=0;i<numMoves;i++){
	
		dir = rand()%4+1;
		p.moves[i]=dir;
		
	}
	
	return p;
}

Particle calcPosition(Particle p){

	int i;
	
	p.pX=0;
	p.pY=0;
	
	for(i=0;i<numMoves;i++){

		switch(p.moves[i]){
			
			case 1:
				p.pX--;
				break;
				
			case 2:
				p.pX++;
				break;
				
			case 3:
				p.pY++;
				break;
				
			case 4:
				p.pY--;
				break;
				
			default:
				printf("There is a severe problem...");
				break;
			
		}
	
	}
	
	return p;

}

float calcDist(Particle p){

	p = calcPosition(p);
	
	return sqrt( pow( p.pX-goalX,2 ) + pow( p.pY-goalY,2 ) ); //distance formula

}

void PrintMoveSet(Particle p){

	int i;
	for(i=0;i<numMoves;i++){
	
		switch(p.moves[i]){
		
			case 1:
				printf("LEFT\t");
				break;
				
			case 2:
				printf("RIGHT\t");
				break;
				
			case 3:
				printf("UP\t");
				break;
				
			case 4:
				printf("DOWN\t");
				break;
				
			default:
				printf("Error in PrintMoveSet");
				break;
		
		}
		
	}
	
	printf("\n");

}

int main(int argc, char *argv[]){

	srand (time(NULL));
	
	Particle p1, p2;
	float smallestDist,tempDist;
	int genCount, i;
	
	
	if(argc == 2){
		genCount = atoi(argv[1]);
	}
	else{
		printf("Bad input");
	}
	
	printf("\n");
	p1 = makeMoveList(p1);

	smallestDist = calcDist(p1);
	
	for(i=0;i<genCount;i++){
		
		printf("\n\n====================Generation %d====================\n\n",i+1);
		
		p2 = makeMoveList(p2);
		tempDist = calcDist(p2);
		
		if(tempDist<smallestDist){
		
			smallestDist = tempDist;
			p1 = p2;
			
		}
		
		PrintMoveSet(p1);
		
		if(smallestDist==0){
			break;
		}
	}
	
	printf("Closest Dist: %f",smallestDist);
	
	return 0;
}