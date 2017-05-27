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
//----------------------------------------------
/*
JVAL
*/
Jval jval_dup(Jval j,void (*jval_copy)(Jval*,Jval*));
Jval jval_dup_i(Jval j);
Jval jval_dup_d(Jval j);
Jval jval_dup_s(Jval j);
int jval_compare_i(const Jval* x,const Jval* y);
int jval_compare_f(const Jval* x,const Jval* y);
int jval_compare_d(const Jval* x,const Jval* y);
int jval_compare_s(const Jval* x,const Jval* y);
int jval_cmp_i(Jval x,Jval y);
int jval_cmp_f(Jval x,Jval y);
int jval_cmp_d(Jval x,Jval y);
int jval_cmp_s(Jval x,Jval y);
void jval_copy_i(Jval *des,Jval *src);
void jval_copy_f(Jval *des,Jval *src);
void jval_copy_d(Jval *des,Jval *src);
void jval_copy_s(Jval *des,Jval *src);
//----------------------------------------------
/*
DLLIST
*/
Dllist dll_find_str(Dllist root,char* key);
Dllist dll_find_int(Dllist root,int key);
Dllist dll_find_dbl(Dllist root,double key);
Dllist dll_find_gen(Dllist root,Jval key,int (*cmp)(Jval, Jval));
Dllist dll_getelement(Dllist l,int index);
void dll_free(Dllist l);
int dll_size(Dllist l);
Dllist dll_dup(Dllist l,void (*jval_copy)(Jval*,Jval*));
Dllist dll_reverse(Dllist l,void (*jval_copy)(Jval*,Jval*));
//sắp xếp dllist mà không ảnh hưởng dllist gốc :
Dllist dll_sort(Dllist l,void (*jval_copy)(Jval*,Jval*),int (*cmp)(Jval,Jval));
//show danh sach list:
void dll_display(Dllist l,void (*show)(Dllist));
//chuyển từ dllist sang gra:
JRB dll_to_gra(Dllist l,void (*jval_copy)(Jval*,Jval*),int (*cmp)(Jval, Jval));
//--------------------------------------------------
/*
GRAPH
*/
//  nhân bản một cây jrb
JRB jrb_dup(JRB tree,int (*cmp)(Jval,Jval),void (*jval_copy_key)(Jval*,Jval*),void (*jval_copy_val)(Jval*,Jval*));
//--------------------------------------------------
/*
GRAPH
*/
int gra_connected_str(JRB g,char* u,char* v);
int gra_connected_int(JRB g,int u,int v);
int gra_connected_dbl(JRB g,double u,double v);
int gra_connected_gen(JRB g,Jval u,Jval v,int (*cmp)(Jval,Jval));
JRB gra_getadjacents_str(JRB g,char* u);
JRB gra_getadjacents_int(JRB g,int u);
JRB gra_getadjacents_dbl(JRB g,double u);
JRB gra_getadjacents_gen(JRB g,Jval u,int (*cmp)(Jval,Jval),void (*jval_copy)(Jval*,Jval*));
JRB gra_backgetadjacents_str(JRB g,char* u);
JRB gra_backgetadjacents_int(JRB g,int u);
JRB gra_backgetadjacents_dbl(JRB g,double u);
JRB gra_backgetadjacents_gen(JRB g,Jval u,int (*cmp)(Jval,Jval),void (*jval_copy)(Jval*,Jval*));
// tính bậc vào của đỉnh
int gra_indegree_str(JRB g,char* u);
int gra_indegree_int(JRB g,int u);
int gra_indegree_dbl(JRB g,double u);
int gra_indegree_gen(JRB g,Jval u,int (*cmp)(Jval,Jval));
// tính bậc ra của đỉnh
int gra_outdegree_str(JRB g,char* u);
int gra_outdegree_int(JRB g,int u);
int gra_outdegree_dbl(JRB g,double u);
int gra_outdegree_gen(JRB g,Jval u,int (*cmp)(Jval,Jval));
// thêm cạnh u<->v trọng weight vào đồ thị g
void gra_insert_str(JRB g,char* u,char* v,double weight);
void gra_insert_int(JRB g,int u,int v,double weight);
void gra_insert_dbl(JRB g,double u,double v,double weight);
void gra_insert_gen(JRB g,Jval u,Jval v,double weight,int (*cmp)(Jval, Jval));
// xóa một đỉnh u của đồ thị g
void gra_delete_str(JRB g,char* u);
void gra_delete_int(JRB g,int u);
void gra_delete_dbl(JRB g,double u);
void gra_delete_gen(JRB g,Jval u,int (*cmpkey)(Jval,Jval));
// lấy trọng số của cạnh từ u đến v
double gra_getweight(JRB g,Jval u,Jval v,int (*cmp)(Jval,Jval));
// lấy phần tử thứ index trong đồ thị
JRB gra_getelement(JRB g,int index);
// lấy cây chứa đỉnh của g
JRB gra_getvertices(JRB g,int (*cmp)(Jval,Jval),void (*jval_copy)(Jval*,Jval*));
// tính số đỉnh trong g
int gra_size(JRB g);
// hiển thị đồ thị g
void gra_display(JRB g,void (*show)(JRB));
// nhân bản dồ thị g
JRB gra_dup(JRB g,int (*cmpkey)(Jval,Jval),
	int (*cmpsubkey)(Jval,Jval),
	void (*jval_copy_key)(Jval*,Jval*),
	void (*jval_copy_subkey)(Jval*,Jval*),
	void (*jval_copy_subval)(Jval*,Jval*)
	);
// xóa đồ thị g:
void gra_free(JRB g);
// chuyển từ g sang dllist:
Dllist gra_to_dll(JRB g,void (*jval_copy)(Jval*,Jval*));
/*
STRING
*/
int str_include(char *s,char c);
spliter* str_split(char* string,char* chars);
void spliter_free(spliter *sp);
//--------------------------------------
typedef struct fcmp_t{
	int line;
	int col;
	int same;	
}filecompare;
filecompare filecmp(char* fname1,char* fname2);