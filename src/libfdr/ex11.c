#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"
#include "jrb.h"
#define INFINITE 8888
JRB GetAdjacentList(JRB g,int a){// trả về danh sách các đỉnh mà từ a có thể đến được
	JRB ptr=jrb_find_int(g,a);
	if(ptr) return (JRB)jval_v(ptr->val);
	else return NULL;	
}
int DD(JRB g, int u, int v){
	JRB ptr;
	JRB tmp_g=make_jrb();
	jrb_traverse(ptr,g){
		jrb_insert_int(tmp_g,jval_i(ptr->key),new_jval_i(INFINITE));
	}
	ptr=jrb_find_int(tmp_g,u);
	if(ptr){
		ptr->val=new_jval_i(0);
	}
	else{
		printf("%d not belongs_to G\n",u);
		return -1;
	}

	JRB min_element,adjacentList,tmp;
	int current_value;
	// jrb_traverse(ptr,tmp_g){
	// 		printf("%d(%d) ",jval_i(ptr->key),jval_i(ptr->val) );
	// 	}
	// 	printf("\n");
	do{
		min_element=jrb_first(tmp_g);
		jrb_traverse(ptr,tmp_g){
			if(jval_i(min_element->val)> jval_i(ptr->val)) min_element=ptr;
		}
		//printf("Min node key %d, val %d\n",jval_i(min_element->key),jval_i(min_element->val) );
		if(jval_i(min_element->key)==v) return jval_i(min_element->val);
		current_value=jval_i(min_element->val);
		adjacentList=GetAdjacentList(g,jval_i(min_element->key));
		jrb_traverse(ptr,adjacentList){
			//printf("adje node %d trong so %d\n",jval_i(ptr->key),jval_i(ptr->val) );
			if(tmp=jrb_find_int(tmp_g,jval_i(ptr->key))){
				if(jval_i(tmp->val)>current_value+jval_i(ptr->val)){
					tmp->val=new_jval_i(current_value+jval_i(ptr->val));
					//printf("Update %d thanh %d\n",jval_i(tmp->key),jval_i(tmp->val) );
				}
			}
		}			
		jrb_delete_node(min_element);
		// jrb_traverse(ptr,tmp_g){
		// 	printf("%d(%d) ",jval_i(ptr->key),jval_i(ptr->val) );
		// }
		// printf("\n");

		if(jrb_empty(tmp_g)) return -1;
	}while(1);
	// jrb_traverse(ptr,tmp_g){
	// 	printf("%d: %d \n",jval_i(ptr->key),jval_i(ptr->val));		
	// }
	return 1;	
}
JRB Load(const char* fname){
	JRB tree,tmp_tree; JRB tmp_node,ptr;
	tree=make_jrb();
	IS is;
	is=new_inputstruct(fname);
	get_line(is);
	int number_of_rows=atoi(is->text1);
	int u,v,cost;
	//printf("%d\n",number_of_rows );
	while(-1!=get_line(is) && 0<number_of_rows-- && is->NF == 3) {
		u=atoi(is->fields[0]);
		v=atoi(is->fields[1]);
		cost=atoi(is->fields[2]);
		tmp_node=jrb_find_int(tree,u);
		if(tmp_node){
				tmp_tree=jval_v(tmp_node->val);				
				jrb_insert_int(tmp_tree,v,new_jval_i(cost));
		}
		else{
				tmp_tree=make_jrb();
				jrb_insert_int(tree,u,new_jval_v(tmp_tree));
				jrb_insert_int(tmp_tree,v,new_jval_i(cost));
		}
		
		tmp_node=jrb_find_int(tree,v);
		if(tmp_node){
			tmp_tree=jval_v(tmp_node->val);				
			jrb_insert_int(tmp_tree,u,new_jval_i(cost));
		}
		else{
			tmp_tree=make_jrb();
			jrb_insert_int(tree,v,new_jval_v(tmp_tree));
			jrb_insert_int(tmp_tree,u,new_jval_i(cost));
		}		
	}

	jettison_inputstruct(is);
	return tree;
}
int main(int argc, char const *argv[])
{
	JRB tree,subtree,ptr,subptr,t,st;
	tree=Load("input11.txt");
	jrb_traverse(ptr,tree){
		printf("%d: ",jval_i(ptr->key));
		subtree=(JRB)jval_v(ptr->val);
		jrb_traverse(subptr,subtree){
			printf("%d(%d) ",jval_i(subptr->key),jval_i(subptr->val));
		}
		printf("\n");
	}	
	if(argc>=3)	printf("%d\n",DD(tree,atoi(argv[1]),atoi(argv[2])));
	return 0;
}