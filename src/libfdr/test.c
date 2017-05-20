#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXFIELDS 100
typedef struct spliter_t{	
	int NF;                   /* Number of fields */
	char *fields[100]; /* Pointers to fields */	
}spliter;
int str_include(char *s,char c){
	while(*s!='\0'){
		if(*s==c) return 1;
		s++;
	}
	return 0;
}
spliter* str_split(char* string,char* chars){
	spliter *sp;
	sp=(spliter*)malloc(sizeof(spliter));
	sp->NF=1;	
	char *p,*q,c;
	p=string;	
	while(*p!='\0'){	
		if(str_include(chars,*p)==1){			
			c=*p;
			*p='\0';			
			sp->fields[sp->NF-1]=strdup(string);
			sp->NF=(sp->NF)+1;			
			*p=c;
			p=p+1;
			string=p;			
		}
		else p++;
	}	
	sp->fields[sp->NF-1]=strdup(string);
	return sp;
}
int main(int argc, char const *argv[])
{
	/* code */
	spliter *split;
	char s[]="nguyen dinh hung,ga vai,cut";
	split=str_split(s," ,");
	printf("%s\n",s );
	
	for(int i=0;i<split->NF;i++){
		printf("%s\n",split->fields[i] );
		free(split->fields[i]);
	}
	free(split);
	return 0;
}