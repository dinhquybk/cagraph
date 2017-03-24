#include <stdio.h>
#include "fields.h"
 // a	b  c 	d
void show(IS is){
	printf("Name: %s\n",is->name );
	printf("Line: %d\n",is->line );
	printf("Text1: %s\n",is->text1 );
	printf("Text2: %s\n",is->text2 );
	printf("NF: %d\n",is->NF );
	for(int i=0;i<is->NF;i++)
		puts(is->fields[i]);
	if(is->file) printf("Is FILE\n");
	else printf("Is PIPE\n");
	printf("----------------------\n");
}
int main(int argc, char const *argv[])
{
	IS is;
	is=new_inputstruct("test_fields.c");
	int num;
	while(-1!=get_line(is)){
		show(is);
	}	
	jettison_inputstruct(is);
	return 0;
}