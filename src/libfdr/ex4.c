#include <stdio.h>
#include "ex4.h"
Dllist SearchDL(const Dllist list,
				const Jval* item, 
				int (*compare)(const Jval*,const Jval*)){
	Dllist ptr;
	dll_traverse(ptr,list){
		if(compare(&(ptr->val),item)==0) return ptr;
	}
	return NULL;
}

int jval_compare_i(const Jval* x,const Jval* y){
	return x->i-y->i;
}
int jval_compare_f(const Jval* x,const Jval* y){
	float tmp=x->f - y->f;
	if(tmp<0 ) return -1;
	else if(tmp==0) return 0;
		else return 1;
}
int jval_compare_s(const Jval* x,const Jval* y){
	return strcmp(x->s,y->s);
}