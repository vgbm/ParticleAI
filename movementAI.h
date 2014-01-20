#define numMoves 6

typedef enum{
	LEFT=1,RIGHT,UP,DOWN
} Direction;

typedef struct{

	int pX;
	int pY;
	int moves[numMoves];
	Direction dir;
	int steps;
	int teleX;
	int teleY;
	
} Particle;


//Various Meta methods
Particle makeMoveList(Particle p);
Particle mutateMoves(Particle p);
Particle singleMutation(Particle p);
Particle initParticle(Particle p);
Particle execMoves( Particle p );
float calcDist(Particle p);
void printMoveSet(Particle p);

//this is the order (from 1+) for the makeMoveSet method, except doNothing is default so as to allow messing with the move pool
//1st method is rand and so on
Particle teleport(int x, int y, Particle p);
Particle move(Particle p);
Particle genDirRand(Particle p);
Particle randMove(Particle p);
Particle genStepsRand(Particle p);
Particle genDirByGoal(Particle p);
Particle genStepsByDist(Particle p);
void doNothing( void );
//end of orig methods

//added methods follow
Particle randTeleX( Particle p );
Particle randTeleY( Particle p );
Particle goalTeleX( Particle p );
Particle goalTeleY( Particle p );
Particle resetTele( Particle p );