#include <stdio.h>
#include "Algo.h"
#include "Algo1.h"
#include "Algo2.h"

//Macros
#define ALGO1_TYPE	0
#define ALGO2_TYPE	1
#define POST_MUL_NUM	100

//Functions
lAlgo Factory(int algo_type);
int Algo_calc(lAlgo algo, int a, int b);


int main(void){
	int res = 0;

	lAlgo algo1 = Factory(ALGO1_TYPE);
	lAlgo algo2 = Factory(ALGO2_TYPE);

	res = Algo_calc(algo1, 10 ,20);
	printf("algo1: %d\n", res);

	res = Algo_calc(algo2, 10 ,20);
	printf("algo2: %d\n", res);

	return 0;
}


lAlgo Factory(int algo_type){
	lAlgo algo;
	if(algo_type == ALGO1_TYPE){
		lAlgo algo = new_Algo1();
	}else if(algo_type == ALGO2_TYPE){
		lAlgo algo = new_Algo2();
	}else{
	
	}
	return algo;
}

int Algo_calc(lAlgo algo, int a, int b){
	return algo.post_calc(algo.pre_calc(a, b), POST_MUL_NUM);
}

