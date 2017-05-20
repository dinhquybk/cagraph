#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "midterm.h"
#include "fields.h"
int CompareI(Jval v1, Jval v2){
	if(v1.i<v2.i) return -1;
	else if(v1.i==v2.i) return 0;
	else return 1;
}

JRB LoadGraph(const char* fname){
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

// tra ve danh sach cac dinh cua do thi g
Dllist GetVertices(JRB g){
	Dllist list;
	JRB ptr;
	list=new_dllist();
	jrb_traverse(ptr,g){
		dll_append(list,new_jval_i(jval_i(ptr->key)));
	}
	return list;
}

// tra ve danh sach cac dinh ke cua u
Dllist GetAdjacents(JRB g, Jval u, int (*cmp)(Jval, Jval)){
	JRB ptr,subtree,subptr;
	Dllist list=new_dllist();
	jrb_traverse(ptr,g){
		if(cmp(u,ptr->key)==0){
			subtree=(JRB)jval_v(ptr->val);
			jrb_traverse(subptr,subtree){
				dll_append(list,new_jval_i(jval_i(subptr->key)));
			}
			return list;
		}
	}
	return NULL;
}

// tra ve danh sach dinh ke cua u theo tawng dan trong so canh
// tÄƒng dáº§n cá»§a trá»ng sá»‘ cáº¡nh
//      hÃ m cmp_key dung de so sanh khoa
//      hÃ m cmp_value dung de so sanh trong so
// vÃ­ dá»¥: vá»›i Ä‘á»“ thá»‹ Ä‘Ã£ cho,
//        GetAdjacentsW(g, new_jval_i(1), CompareI, CompareI)
//        tráº£ vá» {new_jval_i(2), new_jval_i(5), new_jval_i(3)}
Dllist GetAdjacentsW(JRB g, Jval u, int (*cmp_key)(Jval, Jval),
                                  int (*cmp_value)(Jval, Jval)){
	JRB ptr,subtree,subptr,p,jnode;
	Dllist list=new_dllist(),lp,lnode=NULL;
	jrb_traverse(ptr,g){
		if(cmp_key(u,ptr->key)==0){
			subtree=(JRB)jval_v(ptr->val);
			jrb_traverse(subptr,subtree){
					lnode=NULL;
					dll_traverse(lp,list){
						jnode=jrb_find_int(subtree,jval_i(lp->val));						
						if(cmp_value(jnode->val,subptr->val)<=0)
							continue;
						else {
							lnode=lp;
							break;
						}
					}
					if(lnode) dll_insert_b(lnode, new_jval_i(jval_i(subptr->key)));
					else dll_append(list,new_jval_i(jval_i(subptr->key)));																	
			}
			return list;
		}
	}
	return NULL;
}
void FreeGraph(JRB g){
	JRB ptr,subtree;
	jrb_traverse(ptr,g){
		subtree=(JRB)jval_v(ptr->val);
		jrb_free_tree(subtree);
	}
	jrb_free_tree(g);
}
int main(int argc,char* argv[]){
	JRB tree,subtree,ptr,subptr,t,st;
	tree=LoadGraph("input11.txt");
	jrb_traverse(ptr,tree){
		printf("%d: ",jval_i(ptr->key));
		subtree=(JRB)jval_v(ptr->val);
		jrb_traverse(subptr,subtree){
			printf("%d(%d) ",jval_i(subptr->key),jval_i(subptr->val));
		}
		printf("\n");
	}
	Dllist l,ptr2;
	l=GetVertices(tree);
	dll_traverse(ptr2,l){
		printf("%d ,",jval_i(ptr2->val));
	}		
	printf("\n");
	if(argc>1){
		l=GetAdjacents(tree,new_jval_i(atoi(argv[1])),CompareI);
		dll_traverse(ptr2,l){
			printf("%d ,",jval_i(ptr2->val));
		}		
		printf("\n");
	
		l=GetAdjacentsW(tree,new_jval_i(atoi(argv[1])),CompareI,CompareI);
		dll_traverse(ptr2,l){
			printf("%d ,",jval_i(ptr2->val));
		}		
		printf("\n");
	}	
	return 0;
}