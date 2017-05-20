#include <stdlib.h>
#include "fields.h"
#include "graph.h"

JRB Load(const char* filename){
	JRB g=make_jrb();
	IS is;
	is=new_inputstruct(filename);
	get_line(is);
	int number_of_rows=atoi(is->text1);
	int u,v,weight;
	//printf("%d\n",number_of_rows );
	while(-1!=get_line(is) && 0<number_of_rows-- && is->NF == 3) {
		u=atoi(is->fields[0]);
		v=atoi(is->fields[1]);
		weight=atof(is->fields[2]);
		gra_insert_int(g,u,v,weight);
	}

	jettison_inputstruct(is);
	return g;
}
//giải phóng bộ nhớ đã cấp phát cho đồ thị g tương thích với hàm load, thường đi cặp với hàm Load
void FreeGraph(JRB g){
	gra_free(g);
}
//trả về danh sách đỉnh của g
Dllist GetVertices(JRB g){
	JRB tree=gra_getvertices(g,jval_copy_i,jval_cmp_i);
	Dllist list=gra_to_dll(tree,jval_copy_i);
	gra_free(tree);	
	return list;
}

//kiểm tra nếu có cạnh từ u->v
int Connected(JRB g,Jval u,Jval v,int (*cmpk)(Jval,Jval)){
	return gra_connected_gen(g,u,v,cmpk);
}
//trả về trọng số cạnh u->v
Jval GetWeight(JRB g,Jval u,Jval v,int (*cmpk)(Jval,Jval)){}
//lấy danh sách đỉnh kề với đỉnh u
// Adjacent(u)={v| có đường đi từ u->v}
Dllist GetAdjacents(JRB g,Jval u,int (*cmpk)(Jval,Jval)){}
//lấy danh sách đỉnh kề với đỉnh u theo chiều ngược
// BackAdjacent(u)={v| có đường đi từ v->u}
Dllist GetBackAdjacents(JRB g,Jval u,int (*cmpk)(Jval,Jval)){}
//lấy bậc vào của đỉnh u
// Indegree(u)=| BackAdjacent(u) |
int GetIndegree(JRB g,Jval u,int (*cmpk)(Jval,Jval)){}
//lấy bậc ra của dỉnh u
// OutDegree(u)=| Adjacent(u) |
int GetOutDegree(JRB g,Jval u,int (*cmpk)(Jval,Jval)){}
//tạo bản sao của đồ thị g
JRB CloneGraph(JRB g, Jval (*copykey)(Jval)){} 
//xóa đỉnh khỏi đồ thị g
JRB DeleteNode(JRB g,Jval u,int (*cmpk)(Jval,Jval),Jval (*ck)(Jval)){}
//kiểm tra đồ thị có hướng không chu trình
// trả về 1 nếu không có chu trình
// trả về 0 nếu có chu trình
int IsDAG(JRB g,int (*cmpk)(Jval,Jval)){}
//trả về trật tự topo của đồ thị g
// không thay đổi đồ thị g,trả về danh sách rỗng nếu không có trật tự topo
Dllist TopoOrder(JRB g,int (*cmpk)(Jval,Jval)){}
//tìm đường đi ngắn nhất từ u đến v
// trả về danh sách rỗng nếu không tồn tại đường đi từ u đến v
Dllist PathDFS(JRB g,Jval u,Jval v,int (*cmpk)(Jval,Jval)){}
Dllist PathDj(JRB g,Jval u,Jval v,int (*cmpk)(Jval,Jval),double* out_length){}
// int main(int argc, char const *argv[])
// {
// 	JRB tree,subtree,ptr,subptr,t,st;
// 	tree=Load("input11.txt");
// 	jrb_traverse(ptr,tree){
// 		printf("%d: ",jval_i(ptr->key));
// 		subtree=(JRB)jval_v(ptr->val);
// 		jrb_traverse(subptr,subtree){
// 			printf("%d(%d) ",jval_i(subptr->key),jval_i(subptr->val));
// 		}
// 		printf("\n");
// 	}	
	
// 	return 0;
// }