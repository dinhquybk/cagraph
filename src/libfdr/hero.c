#include "hero.h"
//----------------------------------------------
/*
JVAL
*/
Jval jval_dup(Jval j){
	Jval *new_jval=(Jval*)malloc(sizeof(Jval));
	*new_jval=j;
	new_jval->s=strdup(j.s);
	return *new_jval;
}
int jval_compare_i(const Jval* x,const Jval* y){
	return x->i-y->i;
}
int jval_compare_f(const Jval* x,const Jval* y){
	float tmp=x->f - y->f;
	if(tmp<0 ) return -1;
	else if(tmp==0) return 0;
		else return 1;
}
int jval_compare_s(const Jval* x,const Jval* y){
	return strcmp(x->s,y->s);
}
//----------------------------------------------
/*
DLLIST
*/
Dllist dll_search(const Dllist list,
				const Jval* item, 
				int (*compare)(const Jval*,const Jval*)){
	Dllist ptr;
	dll_traverse(ptr,list){
		if(compare(&(ptr->val),item)==0) return ptr;
	}
	return NULL;
}
Dllist dll_dup(Dllist l){
	Dllist new_list,ptr;
	new_list=new_dllist();
	dll_traverse(ptr,l){
		dll_append(new_list,jval_dup(ptr->val));
	}
	return new_list;
}
Dllist dll_reverse(Dllist l){
	Dllist new_list,ptr;
	new_list=new_dllist();
	dll_traverse(ptr,l){
		dll_prepend(new_list,jval_dup(ptr->val));
	}
	return new_list;
}
//--------------------------------------------------
/*
GRAPH
*/
int gra_connected_str(JRB g,char* u,char* v){// kiểm tra xem có cạnh từ u đến v không
	JRB tree=NULL,ptr=NULL;
	ptr=jrb_find_str(g,u);
	if(ptr){		
		tree=(JRB)jval_v(ptr->val);
		jrb_traverse(ptr,tree){			
			if(strcmp(v,jval_s(ptr->key))==0) return 1;
		}
		return 0;
	}
	else return 0;
}
int gra_connected_int(JRB g,int u,int v){// kiểm tra xem có cạnh từ u đến v không
	JRB tree=NULL,ptr=NULL;
	ptr=jrb_find_int(g,u);
	if(ptr){		
		tree=(JRB)jval_v(ptr->val);
		jrb_traverse(ptr,tree){			
			if(v==jval_i(ptr->key)) return 1;
		}
		return 0;
	}
	else return 0;
}
int gra_connected_dbl(JRB g,double u,double v){// kiểm tra xem có cạnh từ u đến v không
	JRB tree=NULL,ptr=NULL;
	ptr=jrb_find_dbl(g,u);
	if(ptr){		
		tree=(JRB)jval_v(ptr->val);
		jrb_traverse(ptr,tree){			
			if(v==jval_d(ptr->key)) return 1;
		}
		return 0;
	}
	else return 0;
}
int gra_connected_dbl(JRB g,Jval u,Jval v,int (*func)(Jval,Jval)){// kiểm tra xem có cạnh từ u đến v không
	JRB tree=NULL,ptr=NULL;
	ptr=jrb_find_gen(g,u,func);
	if(ptr){		
		tree=(JRB)jval_v(ptr->val);
		jrb_traverse(ptr,tree){			
			if(func(v,ptr->key)==0) return 1;
		}
		return 0;
	}
	else return 0;
}
JRB gra_getadjacents_str(JRB g,char* u){// trả về danh sách các đỉnh mà từ u có thể đến được
	JRB ptr=jrb_find_str(g,u);
	if(ptr) return (JRB)jval_v(ptr->val);
	else return NULL;	
}
JRB gra_getadjacents_int(JRB g,int u){// trả về danh sách các đỉnh mà từ u có thể đến được
	JRB ptr=jrb_find_int(g,u);
	if(ptr) return (JRB)jval_v(ptr->val);
	else return NULL;	
}
JRB gra_getadjacents_dbl(JRB g,double u){// trả về danh sách các đỉnh mà từ u có thể đến được
	JRB ptr=jrb_find_dbl(g,u);
	if(ptr) return (JRB)jval_v(ptr->val);
	else return NULL;	
}
JRB gra_getadjacents_gen(JRB g,Jval u,int (*func)(Jval,Jval)){// trả về danh sách các đỉnh mà từ u có thể đến được
	JRB ptr=jrb_find_gen(g,u,func);
	if(ptr) return (JRB)jval_v(ptr->val);
	else return NULL;	
}
int gra_indegree_str(JRB g,char* u){// tính bậc vào của một đỉnh
	int count=0;
	JRB ptr=NULL,subptr=NULL,subtree=NULL;
	jrb_traverse(ptr,g){
		subtree=(JRB)jval_v(ptr->val);
		jrb_traverse(subptr,subtree){
			if(strcmp(jval_s(subptr->key),u) == 0) {count++;break;}
		}
	}
	return count;
}
int gra_indegree_int(JRB g,int u){// tính bậc vào của một đỉnh
	int count=0;
	JRB ptr=NULL,subptr=NULL,subtree=NULL;
	jrb_traverse(ptr,g){
		subtree=(JRB)jval_v(ptr->val);
		jrb_traverse(subptr,subtree){
			if(jval_i(subptr->key) == u) {count++;break;}
		}
	}
	return count;
}
int gra_indegree_dbl(JRB g,double u){// tính bậc vào của một đỉnh
	int count=0;
	JRB ptr=NULL,subptr=NULL,subtree=NULL;
	jrb_traverse(ptr,g){
		subtree=(JRB)jval_v(ptr->val);
		jrb_traverse(subptr,subtree){
			if(jval_d(subptr->key) == u) {count++;break;}
		}
	}
	return count;
}
int gra_indegree_gen(JRB g,Jval u,int (*func)(Jval,Jval)){// tính bậc vào của một đỉnh
	int count=0;
	JRB ptr=NULL,subptr=NULL,subtree=NULL;
	jrb_traverse(ptr,g){
		subtree=(JRB)jval_v(ptr->val);
		jrb_traverse(subptr,subtree){
			if(func(subptr->key,u) == 0) {count++;break;}
		}
	}
	return count;
}
int gra_outdegree_str(JRB g,char* u){// tính bậc ra của một đỉnh
	int count=0;
	JRB ptr=NULL,subptr=NULL,subtree=NULL;
	ptr=jrb_find_str(g,u);
	if(ptr){
		subtree=(JRB)jval_v(ptr->val);
		jrb_traverse(subptr,subtree){
			count++;
		}
		return count;
	}
	else return -1;
}
int gra_outdegree_int(JRB g,int u){// tính bậc ra của một đỉnh
	int count=0;
	JRB ptr=NULL,subptr=NULL,subtree=NULL;
	ptr=jrb_find_int(g,u);
	if(ptr){
		subtree=(JRB)jval_v(ptr->val);
		jrb_traverse(subptr,subtree){
			count++;
		}
		return count;
	}
	else return -1;
}
int gra_outdegree_dbl(JRB g,double u){// tính bậc ra của một đỉnh
	int count=0;
	JRB ptr=NULL,subptr=NULL,subtree=NULL;
	ptr=jrb_find_dbl(g,u);
	if(ptr){
		subtree=(JRB)jval_v(ptr->val);
		jrb_traverse(subptr,subtree){
			count++;
		}
		return count;
	}
	else return -1;
}
int gra_outdegree_gen(JRB g,Jval u,int (*func)(Jval,Jval)){// tính bậc ra của một đỉnh
	int count=0;
	JRB ptr=NULL,subptr=NULL,subtree=NULL;
	ptr=jrb_find_gen(g,u,func);
	if(ptr){
		subtree=(JRB)jval_v(ptr->val);
		jrb_traverse(subptr,subtree){
			count++;
		}
		return count;
	}
	else return -1;
}
//THÊM cạnh u<->v trọng số cost  vào đồ thị g:
void gra_insert_str(JRB g,char* u,char* v,int cost){
	JRB tmp_node,sub_tree;
	tmp_node=jrb_find_str(g,u);
		if(tmp_node){
				sub_tree=jval_v(tmp_node->val);				
				jrb_insert_str(sub_tree,strdup(v),new_jval_i(cost));
		}
		else{
				sub_tree=make_jrb();
				jrb_insert_str(g,strdup(u),new_jval_v(sub_tree));
				jrb_insert_str(sub_tree,strdup(v),new_jval_i(cost));
		}
		
	tmp_node=jrb_find_str(g,v);
		if(tmp_node){
			sub_tree=jval_v(tmp_node->val);				
			jrb_insert_str(sub_tree,strdup(u),new_jval_i(cost));
		}
		else{
			sub_tree=make_jrb();
			jrb_insert_str(g,strdup(v),new_jval_v(sub_tree));
			jrb_insert_str(sub_tree,strdup(u),new_jval_i(cost));
		}	
}
void gra_insert_int(JRB g,int u,int v,int cost){
	JRB tmp_node,sub_tree;
	tmp_node=jrb_find_int(g,u);
		if(tmp_node){
				sub_tree=jval_v(tmp_node->val);				
				jrb_insert_int(sub_tree,v,new_jval_i(cost));
		}
		else{
				sub_tree=make_jrb();
				jrb_insert_int(g,u,new_jval_v(sub_tree));
				jrb_insert_int(sub_tree,v,new_jval_i(cost));
		}
		
	tmp_node=jrb_find_int(g,v);
		if(tmp_node){
			sub_tree=jval_v(tmp_node->val);				
			jrb_insert_int(sub_tree,u,new_jval_i(cost));
		}
		else{
			sub_tree=make_jrb();
			jrb_insert_int(g,v,new_jval_v(sub_tree));
			jrb_insert_int(sub_tree,u,new_jval_i(cost));
		}	
}
void gra_insert_dbl(JRB g,double u,double v,int cost){
	JRB tmp_node,sub_tree;
	tmp_node=jrb_find_dbl(g,u);
		if(tmp_node){
				sub_tree=jval_v(tmp_node->val);				
				jrb_insert_dbl(sub_tree,v,new_jval_i(cost));
		}
		else{
				sub_tree=make_jrb();
				jrb_insert_dbl(g,u,new_jval_v(sub_tree));
				jrb_insert_dbl(sub_tree,v,new_jval_i(cost));
		}
		
	tmp_node=jrb_find_dbl(g,v);
		if(tmp_node){
			sub_tree=jval_v(tmp_node->val);				
			jrb_insert_dbl(sub_tree,u,new_jval_i(cost));
		}
		else{
			sub_tree=make_jrb();
			jrb_insert_dbl(g,v,new_jval_v(sub_tree));
			jrb_insert_dbl(sub_tree,u,new_jval_i(cost));
		}	
}
void gra_insert_gen(JRB g,double u,double v,int cost,int (*func)(Jval, Jval)){
	JRB tmp_node,sub_tree;
	tmp_node=jrb_find_gen(g,u,func);
		if(tmp_node){
				sub_tree=jval_v(tmp_node->val);				
				jrb_insert_gen(sub_tree,v,new_jval_i(cost),func);
		}
		else{
				sub_tree=make_jrb();
				jrb_insert_gen(g,u,new_jval_v(sub_tree),func);
				jrb_insert_gen(sub_tree,v,new_jval_i(cost),func);
		}
		
	tmp_node=jrb_find_gen(g,v,func);
		if(tmp_node){
			sub_tree=jval_v(tmp_node->val);				
			jrb_insert_gen(sub_tree,u,new_jval_i(cost),func);
		}
		else{
			sub_tree=make_jrb();
			jrb_insert_gen(g,v,new_jval_v(sub_tree),func);
			jrb_insert_gen(sub_tree,u,new_jval_i(cost),func);
		}	
}