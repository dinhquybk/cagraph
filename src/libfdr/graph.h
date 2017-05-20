#ifndef GRAPH_H_
#define GRAPH_H_
#include "jrb.h"
#include "dllist.h"
// * Kiểu dữ liệu lưu trọng số cạnh bắt buộc phải là double
//thêm cạnh vào đồ thị
// nếu u,v mà chứa con trỏ thì chỉ copy con trỏ, không copy vùng nhớ tương ứng.
JRB Insert(JRB g,Jval u,Jval v,double w,int (*cmpk)(Jval,Jval));
//trả về đồ thị trên cấu trúc JRB, filename là tên tệp dữ liệu
JRB Load(const char* filename);
//giải phóng bộ nhớ đã cấp phát cho đồ thị g tương thích với hàm load, thường đi cặp với hàm Load
void FreeGraph(JRB g);
//trả về danh sách đỉnh của g
Dllist GetVertices(JRB g);
JRB GetVerticesJrb(JRB g);
//kiểm tra nếu có cạnh từ u->v
int Connected(Jval u,Jval v,int (*cmpk)(Jval,Jval));
//trả về trọng số cạnh u->v
Jval GetWeight(JRB g,Jval u,Jval v,int (*cmpk)(Jval,Jval));
//lấy danh sách đỉnh kề với đỉnh u
// Adjacent(u)={v| có đường đi từ u->v}
Dllist GetAdjacents(JRB g,Jval u,int (*cmpk)(Jval,Jval));
//lấy danh sách đỉnh kề với đỉnh u theo chiều ngược
// BackAdjacent(u)={v| có đường đi từ v->u}
Dllist GetBackAdjacents(JRB g,Jval u,int (*cmpk)(Jval,Jval));
//lấy bậc vào của đỉnh u
// Indegree(u)=| BackAdjacent(u) |
int GetIndegree(JRB g,Jval u,int (*cmpk)(Jval,Jval));
//lấy bậc ra của dỉnh u
// OutDegree(u)=| Adjacent(u) |
int GetOutDegree(JRB g,Jval u,int (*cmpk)(Jval,Jval));
//tạo bản sao của đồ thị g
JRB CloneGraph(JRB g, Jval (*copykey)(Jval)); 
//xóa đỉnh khỏi đồ thị g
JRB DeleteNode(JRB g,Jval u,int (*cmpk)(Jval,Jval),Jval (*ck)(Jval));
//kiểm tra đồ thị có hướng không chu trình
// trả về 1 nếu không có chu trình
// trả về 0 nếu có chu trình
int IsDAG(JRB g,int (*cmpk)(Jval,Jval));
//trả về trật tự topo của đồ thị g
// không thay đổi đồ thị g,trả về danh sách rỗng nếu không có trật tự topo
Dllist TopoOrder(JRB g,int (*cmpk)(Jval,Jval));
//tìm đường đi ngắn nhất từ u đến v
// trả về danh sách rỗng nếu không tồn tại đường đi từ u đến v
Dllist PathDFS(JRB g,Jval u,Jval v,int (*cmpk)(Jval,Jval));
Dllist PathDj(JRB g,Jval u,Jval v,int (*cmpk)(Jval,Jval),double* out_length);
#endif //GRAPH_H