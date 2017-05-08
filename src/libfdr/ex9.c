#include <stdio.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"
#include "ex9.h"
JRB GetAdjacentList(JRB g,char* s){// trả về danh sách các đỉnh mà từ a có thể đến được
	JRB ptr=jrb_find_str(g,s);
	if(ptr) return (JRB)jval_v(ptr->val);
	else return NULL;	
}
JRB BFS(JRB g, const char* s){
	JRB seen,ptr,tmp_list,tree_node,jrb_node;
	Dllist queue,tmp_node;
	JRB result_tree;
	result_tree=make_jrb();

	char* tmp_str;
	queue=new_dllist();
	seen=make_jrb();

	dll_append(queue,new_jval_s(strdup(s)));	
	jrb_insert_str(seen,strdup(s),new_jval_i(0));	
	while(!dll_empty(queue)){
		tmp_node=dll_first(queue);
		tmp_str=jval_s(tmp_node->val);
		jrb_node=jrb_find_str(seen,tmp_str);// tim ra node cha		
		jrb_insert_str(result_tree,strdup(tmp_str),new_jval_i(jval_i(jrb_node->val)));
		tmp_list=(JRB)GetAdjacentList(g,tmp_str);
		if(tmp_list){
			jrb_traverse(ptr,tmp_list){				
				tree_node=jrb_find_str(seen,jval_s(ptr->key));// tim xem co node con nay tren cay seen chua
				if(tree_node==NULL){					
					dll_append(queue,new_jval_s(strdup(jval_s(ptr->key))));								
					jrb_insert_str(seen,jval_s(ptr->key),new_jval_i(1+jval_i(jrb_node->val)));
				}
			}
		}		
		dll_delete_node(tmp_node);			
	}
	return result_tree;
}	

JRB DFS(JRB g,const char* s){
	JRB seen,ptr,tmp_list,tree_node,jrb_node;
	Dllist stack,tmp_node;
	JRB result_tree;
	result_tree=make_jrb();

	char* tmp_str;
	stack=new_dllist();
	seen=make_jrb();

	dll_append(stack,new_jval_s(strdup(s)));	
	jrb_insert_str(seen,strdup(s),new_jval_i(0));	
	while(!dll_empty(stack)){
		tmp_node=dll_last(stack);
		tmp_str=jval_s(tmp_node->val);
		jrb_node=jrb_find_str(seen,tmp_str);// tim ra node cha		
		jrb_insert_str(result_tree,strdup(tmp_str),new_jval_i(jval_i(jrb_node->val)));
		tmp_list=(JRB)GetAdjacentList(g,tmp_str);
		if(tmp_list){
			jrb_traverse(ptr,tmp_list){				
				tree_node=jrb_find_str(seen,jval_s(ptr->key));// tim xem co node con nay tren cay seen chua
				if(tree_node==NULL){					
					dll_append(stack,new_jval_s(strdup(jval_s(ptr->key))));								
					jrb_insert_str(seen,jval_s(ptr->key),new_jval_i(1+jval_i(jrb_node->val)));
				}
			}
		}		
		dll_delete_node(tmp_node);			
	}
	return result_tree;
}

// Load("input.txt"
JRB Load(const char* fname){
	JRB tree,tmp_tree; JRB tmp_node,ptr;
	tree=make_jrb();
	IS is;
	is=new_inputstruct(fname);
	while(-1!=get_line(is) && is->NF == 3) {
		tmp_node=jrb_find_str(tree,is->fields[0]);
		if(tmp_node){
				tmp_tree=jval_v(tmp_node->val);				
				jrb_insert_str(tmp_tree,strdup(is->fields[2]),JNULL);
		}
		else{
				tmp_tree=make_jrb();
				jrb_insert_str(tree,strdup(is->fields[0]),new_jval_v(tmp_tree));
				jrb_insert_str(tmp_tree,strdup(is->fields[2]),JNULL);
		}
		if(strcmp(is->fields[1],"->")==0){
			//printf("co huong\n");			
		}
		else{
			//printf("vo huong\n");
			tmp_node=jrb_find_str(tree,is->fields[2]);
			if(tmp_node){
					tmp_tree=jval_v(tmp_node->val);				
					jrb_insert_str(tmp_tree,strdup(is->fields[0]),JNULL);
			}
			else{
					tmp_tree=make_jrb();
					jrb_insert_str(tree,strdup(is->fields[2]),new_jval_v(tmp_tree));
					jrb_insert_str(tmp_tree,strdup(is->fields[0]),JNULL);
			}
		}
	}

	jettison_inputstruct(is);
	return tree;
}
int main(int argc, char const *argv[])
{
	JRB tree,subtree,ptr,subptr,t,st;
	tree=Load("input.txt");
	jrb_traverse(ptr,tree){
		printf("%s: ",jval_s(ptr->key));
		subtree=(JRB)jval_v(ptr->val);
		jrb_traverse(subptr,subtree){
			printf("%s",jval_s(subptr->key));
		}
		printf("\n");
	}
	t=BFS(tree,"A");
	jrb_traverse(ptr,t){
		printf("%s: %d\n",jval_s(ptr->key),jval_i(ptr->val));		
	}
	t=DFS(tree,"A");
	jrb_traverse(ptr,t){
		printf("%s: %d\n",jval_s(ptr->key),jval_i(ptr->val));		
	}	
	return 0;
}