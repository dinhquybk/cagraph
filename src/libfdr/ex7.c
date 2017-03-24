#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fields.h"
#include "dllist.h"
#include "ex7.h"
void process_string(char *str, char **station, char **name){
	char *p;
	p=str;
	while(*p!= '\0' && *p != '=' )p++; *p='\0'; *station=strdup(str); *p='=';
	str=p+1;
	while(*p!= '\0' && *p != '\n' )p++; *p='\0';*name=strdup(str);	
}
JRB LoadData(const char* fname,JRB* nodes,JRB* lines) {
	IS is; char *station_key=NULL,*station_val=NULL; int i;Jval tmp_jval;
	JRB tmp_tree=NULL; JRB results=NULL; Dllist tmp_list=NULL;
	is=new_inputstruct(fname,"r");
	get_line(is);
	results=make_jrb();	*nodes=make_jrb();	*lines=make_jrb();
	while(-1!=get_line(is) && is->text1[0] != '[') {
		process_string(is->text1, &station_key, &station_val);		
		jrb_insert_str(*nodes,station_key,new_jval_s(station_val));
		jrb_insert_str(results,station_key,new_jval_v(make_jrb()));
	}		
	char *mo=NULL;
	while(-1!=get_line(is)){
		process_string(is->fields[0],&mo,&(is->fields[0]));		
		tmp_jval=new_jval_v(tmp_list=new_dllist());
		jrb_insert_str(*lines,mo,tmp_jval);

		for(i=0; i< is->NF; i++){			
			dll_append(tmp_list,new_jval_s(strdup(is->fields[i])));
			tmp_tree=jrb_find_str(results,is->fields[i]);
			if(tmp_tree){				
				if(i+1<is->NF) jrb_insert_str((JRB)jval_v(tmp_tree->val),strdup(is->fields[i+1]),new_jval_s(mo));
			}
			else{
				printf("File has errors\n"); abort();
			}				
		}				
	}	
	jettison_inputstruct(is);

	return results;
}

int main(int argc, char const *argv[])
{
	/* code */
	JRB r,nodes,lines,tree_ptr; Dllist list,list_ptr;
	r=LoadData("bus.txt",&nodes,&lines);
	printf("Test nodes:\n");
	jrb_traverse(tree_ptr , nodes ){		
		printf("(%s: %s) ", jval_s(tree_ptr->key),jval_s(tree_ptr->val) );		
		printf("\n");		
	}

	printf("Test lines:\n");
	jrb_traverse(tree_ptr , lines ){		
		printf(" %s -> ", jval_s(tree_ptr->key) );
		list=(Dllist)jval_v(tree_ptr->val);
		jrb_traverse(list_ptr , list ){
			printf("%s ", jval_s(list_ptr->val));		
		}
		printf("\n");		
	}

	printf("Test results:\n");
	JRB tmp_tree=NULL,tmp_tree2=NULL,t;
	jrb_traverse(tmp_tree , r ){
		printf("%s : ", jval_s(tmp_tree->key));
		t=(JRB)jval_v(tmp_tree->val);
		jrb_traverse(tmp_tree2 ,t  ){
			printf("(%s : %s) ", jval_s(tmp_tree2->key),jval_s(tmp_tree2->val)  );		
		}
		printf("\n");		
	}	
	return 0;
}
