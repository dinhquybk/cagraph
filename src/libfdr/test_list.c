#include "dllist.h"
#include "ex4.h"
#include <stdio.h>
#include <stdlib.h>
void Print(Dllist list){
	Dllist ptr;
	dll_traverse(ptr,list){
		//printf("%d ",jval_i(ptr->val) );
		printf("%f ",jval_f(ptr->val) );
	}
	printf("\n");
	dll_rtraverse(ptr,list){
		//printf("%d ",jval_i(ptr->val) );
		printf("%f ",jval_f(ptr->val) );
	}
	printf("\n");
}
int main(int argc, char const *argv[])
{
	Dllist list=new_dllist();
	srand(time(NULL));
	for(int i=1;i<=10;i++){
		//dll_append(list,new_jval_i(i*10));
		dll_append(list,new_jval_f(i*10.0));
	}
	Print(list);
	//dll_delete_node(dll_first(list));
	//Print(list);
	Jval x;
	/*
	printf("Search int : \n");scanf("%d",&x.i);while(getchar()!='\n');
	if( SearchDL(list,&x,jval_compare_i)!=NULL ) printf("Tim thay\n");
	else printf("Khong tim thay\n");
	*/

	printf("Search float : \n");scanf("%f",&x.f);while(getchar()!='\n');
	if( SearchDL(list,&x,jval_compare_f)!=NULL ) printf("Tim thay\n");
	else printf("Khong tim thay\n");

	free_dllist(list);
	return 0;
}