#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dllist.h"
#include "fields.h"
#include "jrb.h"
#include "jval.h"
typedef struct spliter_t{	
	int NF;                   /* Number of fields */
	char *fields[100]; /* Pointers to fields */	
}spliter;
int str_include(char *s,char c);
spliter* str_split(char* string,char* chars);