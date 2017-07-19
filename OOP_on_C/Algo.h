#ifndef _ALGOH_
#define _ALGOH_

//Function Pointer Struct as Interface class
typedef struct lAlgo{
	int (*pre_calc)(int a, int b);
	int (*post_calc)(int a, int b);
}lAlgo;

#endif //_ALGOH_
