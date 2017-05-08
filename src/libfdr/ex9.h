/*
 input.txt
 A -> B
 B <-> D
 A <-> C

 Tệp input.txt gồm nhiều dòng, mỗi dòng mô tả
 một cạnh của đồ thị:
    A -> B: cạnh có hướng từ A đến B
    A <-> B: cạn vô hướng giữa A và B
 Tên đỉnh có thể nhiều hơn một ký tự.
 */

#include "jrb.h"
  
 // BFS(g, "A")
 //   A: 0
 //   B: 1
 //   C: 1
 //   D: 2
 JRB BFS(JRB g, const char* s);

 // DFS(g, "A")
 //   A: 0
 //   C: 1
 //   B: 1
 //   D: 2
 JRB DFS(JRB g, const char* s);

 // Load("input.txt") trả về đồ thị
 JRB Load(const char* fname);