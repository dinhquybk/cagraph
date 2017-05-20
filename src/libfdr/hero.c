#include "hero.h"
//----------------------------------------------
/*
JVAL
*/
Jval jval_dup(Jval j,void (*jval_copy)(Jval*,Jval*)){
	Jval new;
	jval_copy(&new,&j);
	return new;
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
Dllist dll_dup(Dllist l,void (*jval_copy)(Jval*,Jval*)){
	Dllist new_list=new_dllist(),ptr;
	if(new_list){
		dll_traverse(ptr,l){
			dll_append(new_list,jval_dup(ptr->val,jval_copy));
		}
	}	
	return new_list;
}
Dllist dll_reverse(Dllist l,void (*jval_copy)(Jval*,Jval*)){
	Dllist new_list=new_dllist(),ptr;
	if(new_list){
		dll_traverse(ptr,l){
			dll_prepend(new_list,jval_dup(ptr->val,jval_copy));
		}
	}	
	return new_list;
}
//sắp xếp dllist mà không ảnh hưởng dllist gốc :
Dllist dll_sort(Dllist l,void (*jval_copy)(Jval*,Jval*),int (*cmp)(Jval,Jval)){
	Dllist new_list=new_dllist(),ptr,new_ptr,node;
	if(new_list){
		dll_traverse(ptr,l){			
			node=NULL;
			dll_traverse(new_ptr,new_list){										
				if(cmp(ptr->val,new_ptr->val)<=0)
					continue;
				else {
					node=new_ptr;
					break;
				}
			}
			if(node) dll_insert_b(node, jval_dup(ptr->val,jval_copy));
			else dll_append(new_list,jval_dup(ptr->val,jval_copy));
		}
	}
	return new_list;
}
//chuyển từ dllist sang g:
JRB dll_to_gra(Dllist l,void (*jval_copy)(Jval*,Jval*),int (*func)(Jval, Jval)){
	JRB g=make_jrb();
	Dllist ptr;
	if(g){
		dll_traverse(ptr,l){
			jrb_insert_gen(g,jval_dup(ptr->val,jval_copy),JNULL,func);
		}
	}
	return g;
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
int gra_connected_gen(JRB g,Jval u,Jval v,int (*func)(Jval,Jval)){// kiểm tra xem có cạnh từ u đến v không
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
void gra_insert_str(JRB g,char* u,char* v,double weight){
	JRB tmp_node,sub_tree;
	tmp_node=jrb_find_str(g,u);
		if(tmp_node){
				sub_tree=jval_v(tmp_node->val);				
				jrb_insert_str(sub_tree,strdup(v),new_jval_d(weight));
		}
		else{
				sub_tree=make_jrb();
				jrb_insert_str(g,strdup(u),new_jval_v(sub_tree));
				jrb_insert_str(sub_tree,strdup(v),new_jval_d(weight));
		}
		
	tmp_node=jrb_find_str(g,v);
		if(tmp_node){
			sub_tree=jval_v(tmp_node->val);				
			jrb_insert_str(sub_tree,strdup(u),new_jval_d(weight));
		}
		else{
			sub_tree=make_jrb();
			jrb_insert_str(g,strdup(v),new_jval_v(sub_tree));
			jrb_insert_str(sub_tree,strdup(u),new_jval_d(weight));
		}	
}
void gra_insert_int(JRB g,int u,int v,double weight){
	JRB tmp_node,sub_tree;
	tmp_node=jrb_find_int(g,u);
		if(tmp_node){
				sub_tree=jval_v(tmp_node->val);				
				jrb_insert_int(sub_tree,v,new_jval_d(weight));
		}
		else{
				sub_tree=make_jrb();
				jrb_insert_int(g,u,new_jval_v(sub_tree));
				jrb_insert_int(sub_tree,v,new_jval_d(weight));
		}
		
	tmp_node=jrb_find_int(g,v);
		if(tmp_node){
			sub_tree=jval_v(tmp_node->val);				
			jrb_insert_int(sub_tree,u,new_jval_d(weight));
		}
		else{
			sub_tree=make_jrb();
			jrb_insert_int(g,v,new_jval_v(sub_tree));
			jrb_insert_int(sub_tree,u,new_jval_d(weight));
		}	
}
void gra_insert_dbl(JRB g,double u,double v,double weight){
	JRB tmp_node,sub_tree;
	tmp_node=jrb_find_dbl(g,u);
		if(tmp_node){
				sub_tree=jval_v(tmp_node->val);				
				jrb_insert_dbl(sub_tree,v,new_jval_d(weight));
		}
		else{
				sub_tree=make_jrb();
				jrb_insert_dbl(g,u,new_jval_v(sub_tree));
				jrb_insert_dbl(sub_tree,v,new_jval_d(weight));
		}
		
	tmp_node=jrb_find_dbl(g,v);
		if(tmp_node){
			sub_tree=jval_v(tmp_node->val);				
			jrb_insert_dbl(sub_tree,u,new_jval_d(weight));
		}
		else{
			sub_tree=make_jrb();
			jrb_insert_dbl(g,v,new_jval_v(sub_tree));
			jrb_insert_dbl(sub_tree,u,new_jval_d(weight));
		}	
}
void gra_insert_gen(JRB g,Jval u,Jval v,double weight,int (*func)(Jval, Jval)){
	JRB tmp_node,sub_tree;
	tmp_node=jrb_find_gen(g,u,func);
		if(tmp_node){
				sub_tree=jval_v(tmp_node->val);				
				jrb_insert_gen(sub_tree,v,new_jval_d(weight),func);
		}
		else{
				sub_tree=make_jrb();
				jrb_insert_gen(g,u,new_jval_v(sub_tree),func);
				jrb_insert_gen(sub_tree,v,new_jval_d(weight),func);
		}
		
	tmp_node=jrb_find_gen(g,v,func);
		if(tmp_node){
			sub_tree=jval_v(tmp_node->val);				
			jrb_insert_gen(sub_tree,u,new_jval_d(weight),func);
		}
		else{
			sub_tree=make_jrb();
			jrb_insert_gen(g,v,new_jval_v(sub_tree),func);
			jrb_insert_gen(sub_tree,u,new_jval_d(weight),func);
		}	
}
//XÓA đồ thị g:
void gra_free(JRB g){
	JRB ptr,subptr,subtree;
	jrb_traverse(ptr,g){
		/*cần làm : free vùng nhớ mà key trỏ tới nếu có */
		subtree=jval_v(ptr->val);
		if(subtree!=NULL){
			jrb_traverse(subptr,subtree){
				/*cần làm : free vùng nhớ mà key trỏ tới nếu có */
				/*cần làm : free vùng nhớ mà val trỏ tới nếu có */				
			}
			jrb_free_tree(subtree);
		}			
	}
	jrb_free_tree(g);
}
//chuyển từ g sang dllist:
Dllist gra_to_dll(JRB g,void (*jval_copy)(Jval*,Jval*)){
	Dllist list=new_dllist();
	JRB ptr;
	if(list){
		jrb_traverse(ptr,g){
			dll_append(list,jval_dup(ptr->key,jval_copy));
		}
	}
	return list;
}
/*
STRING
*/
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
//--------------------------------------