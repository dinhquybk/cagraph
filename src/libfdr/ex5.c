#include "ex5.h"
#include <stdlib.h>
#include "fields.h"
Dllist SearchN(const char* fname, int x){
	Dllist list; int n,i,index=0; IS is;
	list=new_dllist();	
	is=new_inputstruct(fname);
	get_line(is);
	n=atoi(is->text1);
	while( 0<n && -1!=get_line(is)){
		for(i=0; i<is->NF && n>0 ;i++,n--,index++){
			if(atoi(is->fields[i])==x) {
				dll_append(list,new_jval_i(index));				
			}
		}
	}
	jettison_inputstruct(is);
	return list;
}
int main(int argc, char const *argv[])
{
	Dllist l,ptr;	
	l=SearchN("input.txt",13);
	dll_traverse(ptr,l){
		printf("%d, ",jval_i(ptr->val));
	}
	return 0;
}