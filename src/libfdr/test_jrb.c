#include <stdio.h>
#include "jrb.h"
int main(){
	JRB t=make_jrb();
	struct 
	{
		int id;char* sid;
	}data[10]={
		{0,"khong"},
		{1,"mot"},
		{2,"hai"},
		{3,"ba"},
		{40,"bon"},
		{50,"nam"},
		{6,"sau"}
	};
	for(int i=0;i<10;i++){
		jrb_insert_int(t,data[i].id,new_jval_s(data[i].sid));
	}
	while(1){
		int id,found=0;
		printf("id=");scanf("%d",&id);while(getchar()!='\n');
		JRB r=jrb_find_int(t,id);
		JRB r_gte=jrb_find_gte_int(t,id,&found);
		if(r){
			printf("%s\n",jval_s(jrb_val(r)));
		}
		else printf("Khong tim thay\n");
		if(r_gte){
			printf("%s %d\n",jval_s(jrb_val(r_gte)),found);
		}
		else printf("Khong tim thay\n");
	}
	return 0;
}
