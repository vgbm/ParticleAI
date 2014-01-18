#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> 

#define numMoves 14
#define numParticles 4
#define goalX 1
#define goalY -23

typedef enum{
	LEFT,RIGHT,UP,DOWN
} Direction;

typedef struct{

	int pX;
	int pY;
	int moves[numMoves];
	Direction dir;
	int steps;
	
} Particle;


Particle makeMoveList(Particle p);
Particle mutateMoves(Particle p);
Particle initParticle(Particle p);
Particle execMoves( Particle p );
float calcDist(Particle p);
void printMoveSet(Particle p);

//this is the order (from 1+) for the makeMoveSet method
//1st method is rand and so on
Particle teleport(int x, int y, Particle p);
Particle move(Particle p);
Particle genDirRand(Particle p);
Particle randMove(Particle p);
Particle genStepsRand(Particle p);
Particle genDirByGoal(Particle p);
Particle genStepsByDist(Particle p);
void doNothing( void );


int main(int argc, char *argv[]){	//things to repair:: Main, printMoveSet, makeMoveList, and execMoves;

	srand (time(NULL));
	
	Particle particles[numParticles], bestParticle;
	
	bestParticle = makeMoveList(bestParticle);
	bestParticle = execMoves(bestParticle);
	
	float smallestDist = calcDist(bestParticle),tempDist;
	int genCount, i, a;
	
	if(argc == 2){
	
		genCount = atoi(argv[1]);
	
		printf("\n");
	
		for(i=0;i<genCount;i++){
		
			printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=Generation %d=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n",i+1);
			
			for(a=0;a<numParticles;a++){
	
				particles[a] = mutateMoves(bestParticle);
				particles[a] = execMoves(particles[a]);
				tempDist = calcDist(particles[a]);
				
				if(tempDist<smallestDist){
					smallestDist = tempDist;
					bestParticle = particles[a];
				}
				
			}
			
			printf("__Best particle's move set so far__\n\n");
			printMoveSet(bestParticle);
			
			if( smallestDist == 0 ){
				break;
			}
			
		}
	
		printf("\n\nClosest Dist: %f\n",smallestDist);
		printMoveSet(bestParticle);
		
	}
	
	else{
		printf("Bad input");
	}
	
	return 0;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Methods start here =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


Particle makeMoveList(Particle p){

	int i;
	
	for(i=0;i<numMoves;i++){
	
		p.moves[i] = rand()%8;
		
	}
	
	return p;
}

Particle mutateMoves(Particle p){

	int i;
	
	for(i=0;i<numMoves;i++){
	
		if( (rand()%2) == 1){
		
			p.moves[i] = rand()%8;
		
		}	
	}
	
	return p;
	
}

Particle initParticle(Particle p){

	p.pX=0;
	p.pY=0;
	p.steps=1;
	p.dir = LEFT;

	return p;
}

/* for reference::

Particle teleport(int x, int y, Particle p);
Particle move(Particle p);
Particle genDirRand(Particle p);
Particle randMove(Particle p);
Particle genStepsRand(Particle p);
Particle genDirByGoal(Particle p);
Particle genStepsByDist(Particle p);
void doNothing( void );
*/

Particle execMoves( Particle p ){ //all values are initialized, so all methods CAN be executed, however some with multiple params may do nothing

	int i;
	
	p = initParticle(p); //initialization of the particle so random crap isn't placed in the particle values
	
	for( i=0; i<numMoves; i++){
	
		switch( p.moves[i] ){
		
			case 0:
				p = teleport( 0,0,p); 
				break;
				
			case 1:
				p = move(p);
				break;
				
			case 2:
				p = genDirRand(p);
				break;
				
			case 3:
				p = randMove(p);
				break;
				
			case 4:
				p = genStepsRand(p);
				break;
				
			case 5:
				p = genDirByGoal(p);
				break;
				
			case 6:
				p = genStepsByDist(p);
				break;
				
			case 7:
				doNothing();
			
		}
	}
	
	return p;

}

Particle teleport(int x, int y, Particle p){ //need to figure out how to implement properly

	p.pX=x;
	p.pY=y;
	
	return p;

}

Particle move(Particle p){

	switch(p.dir){
	
	case LEFT:
		p.pX-=p.steps;
		break;
		
	case RIGHT:
		p.pX+=p.steps;
		break;
		
	case UP:
		p.pY+=p.steps;
		break;
		
	case DOWN:
		p.pY-=p.steps;
		break;
	
	}
	return p;
}

Particle genDirRand(Particle p){

	int	intDir=  rand()%4+1;
	
	switch(intDir){
	
		case 1:
			p.dir = LEFT;
			break;
			
		case 2:
			p.dir = RIGHT;
			break;
			
		case 3:
			p.dir = UP;
			break;
			
		case 4:
			p.dir = DOWN;
			break;
			
	}
	
	return p;

}

Particle randMove(Particle p){

	p = genDirRand(p);
	p = genStepsRand(p);
	
	p = move(p);
	
	return p;
}



Particle genStepsRand(Particle p){

	p.steps = rand()%10+1;
	
	return p;
}

Particle genDirByGoal(Particle p){

	int biggestGap = abs((goalX-p.pX));
	
	if( (abs(goalY-p.pY)) > biggestGap ){
	
		if( (goalY-p.pY) < 0){
		
			p.dir = DOWN;

		}
		
		else{
		
			p.dir = UP;
		
		}
	}

	else{
	
		if( (goalX-p.pX) < 0){
		
			p.dir = LEFT;
		
		}
		
		else{
		
			p.dir = RIGHT;
		
		}
		
	}
	
	return p;
}

Particle genStepsByDist(Particle p){

	p = genDirByGoal(p);
	
	if( p.dir == LEFT || p.dir == RIGHT ){
		p.steps = abs(goalX - p.pX);
	}
	
	else{
		p.steps = abs(goalY - p.pY);
	}
	
	return p;
}

void doNothing( void ){ }// an option to waste your turn or can be forced if the move to execute does not have the correct params


float calcDist(Particle p){
	
	return sqrt( pow( p.pX-goalX,2 ) + pow( p.pY-goalY,2 ) ); //distance formula

}

void printMoveSet(Particle p){

	int i;
	
	for( i=0; i<numMoves; i++){
	
		switch( p.moves[i] ){
		
			case 0:
				printf("teleport\t");
				break;
				
			case 1:
				printf("move\t");
				break;
				
			case 2:
				printf("genDirRand\t");
				break;
				
			case 3:
				printf("randMove\t");
				break;
				
			case 4:
				printf("genStepsRand\t");
				break;
				
			case 5:
				printf("genDirByGoal\t");
				break;
				
			case 6:
				printf("genStepsByDist\t");
				break;
				
			case 7:
				printf("doNothing\t");
				break;
			
		}
	}	
	printf("\n");
}
