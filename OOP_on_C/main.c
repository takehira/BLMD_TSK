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

lAlgo test1 = {Algo1_pre_calc, Algo1_post_calc};

int main(void){
	int res = 0;

	lAlgo algo1 = Factory(ALGO1_TYPE);
	lAlgo algo2 = Factory(ALGO2_TYPE);

	printf("@main.algo1: 0x%x 0x%x\n", algo1.pre_calc, algo1.post_calc);
	printf("@main.test1: 0x%x 0x%x\n", test1.pre_calc, test1.post_calc);
	printf("@main.test1.pre_calc(100, 200): %d\n", test1.pre_calc(100, 200));
	printf("@main.test1.post_calc(100, 200): %d\n", test1.post_calc(100, 200));

	res = Algo_calc(algo1, 10 ,20);
	printf("algo1: %d\n", res);

	res = Algo_calc(algo2, 10 ,20);
	printf("algo2: %d\n", res);

	return 0;
}


lAlgo Factory(int algo_type){
	lAlgo algo;
	if(algo_type == ALGO1_TYPE){
		lAlgo algo1 = new_Algo1();
		algo = algo1;
	}else if(algo_type == ALGO2_TYPE){
		lAlgo algo2 = new_Algo2();
		algo = algo2;
	}else{
	
	}
	printf("@Factory algo: 0x%x 0x%x\n", algo.pre_calc, algo.post_calc);
	return algo;
}

int Algo_calc(lAlgo algo, int a, int b){
	return algo.post_calc(algo.pre_calc(a, b), POST_MUL_NUM);
}

