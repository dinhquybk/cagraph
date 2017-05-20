#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
int filecmp(char* fname1,char* fname2){
	FILE *f1=fopen(fname1,"r");
	FILE *f2=fopen(fname2,"r");
	char c1,c2;
	int line=1;
	if(f1 && f2){
		do{
			c1=fgetc(f1);
			c2=fgetc(f2);
			if(c1!=c2) return line;
			if(c1=='\n') line++;			
		}while(!feof(f1)||!feof(f2));
		return 0;
	}
	else{
		return -1;
	}	
}
int main(int argc, char const *argv[])
{
	FILE *f,*f1,*f2;
	//TEST LOAD:
	JRB g,subtree,ptr,subptr;	
	char in[][16]={"input1.txt","input2.txt","input3.txt"};
	char out[][16]={"input1r","input2r","input3r"};
	int tmp;
	for(int i=0;i<3;i++){
		f=fopen("load","w");
		g=Load(in[i]);	
		jrb_traverse(ptr,g){
			fprintf(f,"%d: ",jval_i(ptr->key));
			subtree=(JRB)jval_v(ptr->val);
			jrb_traverse(subptr,subtree){
				fprintf(f,"%d(%0.0f) ",jval_i(subptr->key),jval_d(subptr->val));
			}
			fprintf(f,"\n");
		}	
		fclose(f);
		printf("Test case: %d\n",i+1 );
		switch(tmp=filecmp("load",out[i])){
			case -1:
				printf("Cannot open file\n");
				break;
			case 0:
				printf("Load OK \n");
				break;
			default:
				printf("Load FAILED at line %d\n",tmp );
				break;
		}
		FreeGraph(g);		
	}	

	return 0;
}