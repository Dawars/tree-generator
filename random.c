#include "define.h"

double randDouble(double min, double max){
	return min + ((max-min)*rand()/RAND_MAX);
}

int randInt(int min, int max){
	return min + (rand()%(max-min));
}
