#include "ex6.h"
#include "fields.h"
#include <stdlib.h>
#include <stdio.h>
JRB LoadMatrix(const char* fname){
	IS is; int n,i,j;
	JRB tree, subtree, *trees;
	
	is=new_inputstruct(fname);
	get_line(is);
	n=atoi(is->text1);

	tree=make_jrb();
	trees=(JRB*)malloc(n* sizeof(JRB));

	for(i=0;i<n;i++){
		trees[i]=make_jrb();
		jrb_insert_int(tree,i,new_jval_v(trees[i]));
	}

	for(i=0; i<n; i++) {		
		if( -1==get_line(is) || is->NF != n) {printf("bad input_file\n");abort();}

		for(j=0; j<n; j++) {
			if(atoi(is->fields[j])!=0 && j!=i) {
				jrb_insert_int(trees[i],j,JNULL);			
			}
		}		
	}
	
	jettison_inputstruct(is);
	return tree;
}

JRB LoadList(const char* fname){
	IS is; int num_of_v,num_of_e,i,j;
	JRB tree, *trees;
	tree=make_jrb();
	is=new_inputstruct(fname);
	if(-1==get_line(is) || is->NF != 2) {printf("Bad input_file\n");abort();}
	num_of_v=atoi(is->fields[0]);
	num_of_e=atoi(is->fields[1]);
	trees=(JRB*)malloc(num_of_v* sizeof(JRB));

	if(-1==get_line(is) || is->NF != num_of_v) {printf("Bad input_file\n");abort();}
	for(i=0;i<num_of_v;i++){
		trees[i]=make_jrb();
		jrb_insert_int(tree,atoi(is->fields[i]),new_jval_v(trees[i]));
	}
	JRB tree1,tree2; int v1,v2;
	//printf("xong\n");
	for(i=0;i<num_of_e;i++){		
		if( -1==get_line(is) || is->NF != 2) {printf("bad input_file\n");abort();}
		v1=atoi(is->fields[0]);v2=atoi(is->fields[1]);
		//printf("%d %d\n",v1,v2 );
		if(v1!=v2){
			tree1=(JRB)jval_v((jrb_find_int(tree,v1)->val));
			tree2=(JRB)jval_v((jrb_find_int(tree,v2)->val));
			jrb_insert_int(tree1,v2,JNULL);
			jrb_insert_int(tree2,v1,JNULL);	
		}
	}
	jettison_inputstruct(is);
	return tree;
}
#include "ex8.h"
int main(int argc, char const *argv[])
{
	JRB t,st,ptr,subptr; JRB tmp=NULL;
	t=LoadMatrix("matrix.txt");
	jrb_traverse(ptr , t ){
		printf("%2d:  ", jval_i(ptr->key) );
			st=(JRB)jval_v(ptr->val);
			jrb_traverse( subptr , st ){
				printf("%2d ", jval_i(subptr->key) );				
			}			
			printf("\n");
	}	
	for(int i=0;i<4;i++){
		if(tmp=GetAdjacentList(t,i)) {
			jrb_traverse( subptr , tmp ){
				//printf("%2d ", jval_i(subptr->key) );				
			}			
			printf("\n");
		}
		printf("InDegree of %d:  %d\n",i, InDegree(t,i) );
		printf("OutDegree of %d:  %d\n",i, OutDegree(t,i) );
	}
	return 0;

	jrb_traverse(ptr , t ){
		jrb_free_tree((JRB)jval_v(ptr->val));		
	}
	jrb_free_tree(t);

	t=LoadList("list.txt");
	
	jrb_traverse(ptr , t ){
		printf("%2d:  ", jval_i(ptr->key) );
			st=(JRB)jval_v(ptr->val);
			jrb_traverse( subptr , st ){
				printf("%2d ", jval_i(subptr->key) );				
			}			
			printf("\n");
	}
	
	// for(int i=1;i<6;i++){
	// 	if(tmp=GetAdjacentList(t,i)) {
	// 		jrb_traverse( subptr , tmp ){
	// 			//printf("%2d ", jval_i(subptr->key) );				
	// 		}			
	// 		printf("\n");
	// 	}
	// 	printf("InDegree of %d:  %d\n",i, InDegree(t,i) );
	// 	printf("OutDegree of %d:  %d\n",i, OutDegree(t,i) );
	// }
		

	jrb_traverse(ptr , t ){
		jrb_free_tree((JRB)jval_v(ptr->val));		
	}
	jrb_free_tree(t);
	
	return 0;
}