#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> 

#define numMoves 14
#define numParticles 5
#define goalX 10
#define goalY 2

typedef struct{

	int pX;
	int pY;
	char *moves[numMoves];
	
} Particle;


typedef enum{
	LEFT,RIGHT,UP,DOWN
} Direction;


Particle makeMoveList(Particle p){

	int i;
	
	for(i=0;i<numMoves;i++){
	
		
		
	}
	
	return p;
}

void execMoves( Particle p ){ //use either randMove or doNothing if the correct params don't pop up

}

Particle teleport(int x, int y, Particle p){

	p.pX=x;
	p.pY=y;
	
	return p;

}

Particle move(Direction dir, int steps, Particle p){

	switch(dir){
	
	case LEFT:
		p.pX-=steps;
		break;
		
	case RIGHT:
		p.pX+=steps;
		break;
		
	case UP:
		p.pY+=steps;
		break;
		
	case DOWN:
		p.pY-=steps;
		break;
	
	}
	return p;
}

Particle randMove(Particle p){

	Direction dir = genDirRand();
	int steps = genStepsRand();
	
	p = move(dir,steps,p);
	
	return p;
}

int genDirRand(void){

	Direction dir =  rand()%4+1;
	return  dir;

}

int genStepsRand(void){

	return rand()%10+1;

}

Direction genDirByGoal(Particle p){

	int biggestGap = abs((goalX-p.pX));
	Direction dir;
	
	if( (abs(goalY-p.pY)) > biggestGap ){
	
		if( (goalY-p.pY) < 0){
		
			dir = DOWN;

		}
		
		else{
		
			dir=UP;
		
		}
	}

	else{
	
		if( (goalX-p.pX) < 0){
		
			dir = LEFT;
		
		}
		
		else{
		
			dir = RIGHT;
		
		}
		
	}
	
	return dir;
}

int genStepsByDist(Particle p){

	Direction dir = genDirByGoal(p);
	
	if( dir == LEFT || dir == RIGHT ){
		return abs(goalX - p.pX);
	}
	
	else{
		return abs(goalY - p.pY);
	}
}

void doNothing( void ){ }// an option to waste your turn or can be forced if the move to execute does not have the correct params


float calcDist(Particle p){
	
	return sqrt( pow( p.pX-goalX,2 ) + pow( p.pY-goalY,2 ) ); //distance formula

}

void PrintMoveSet(Particle p){

	int i;
	for(i=0;i<numMoves;i++){
		
	}
	
	printf("\n");

}

int main(int argc, char *argv[]){	//things to repair:: Main, printMoveSet, makeMoveList, and execMoves;

	srand (time(NULL));
	
	Particle particles[numParticles];
	float smallestDist,tempDist;
	int genCount, i;
	
	
	for(i=0;i<numParticles;i++){ //initialize starting position of all particles
	
		particles[i].pX=0;
		particles[i].pY=0;
		
	}
	
	if(argc == 2){
	
		genCount = atoi(argv[1]);
	
		printf("\n");
	
		for(i=0;i<genCount;i++){
		
			printf("\n\n====================Generation %d====================\n\n",i+1);
		
		}
	
		printf("Closest Dist: %f",smallestDist);
		
	}
	
	else{
		printf("Bad input");
	}
	
	
	return 0;
}