#ifndef MIDTERM_H_

#include "dllist.h"
#include "jrb.h"
#include "jval.h"

/*
 *** LÆ°u Ã½ cung cáº¥p há» vÃ  tÃªn Ä‘áº§y Ä‘á»§ vÃ  mssv trong Ä‘Ã¡p Ã¡n.
 ***         VÃ­ dá»¥: // Há» vÃ  tÃªn: Nguyá»…n VÄƒn A 
 ***                // MSSV: 123456
 Cho Ä‘á»“ thá»‹ vÃ´ hÆ°á»›ng cÃ³ trá»ng sá»‘ Ä‘á»‰nh nguyÃªn lÆ°u
 trong tá»‡p vÄƒn báº£n theo cáº¥u trÃºc sau:
   6
   1 2 5
   3 4 9
   1 3 8
   3 5 2
   1 5 6
   2 4 5
 HÃ£y hoÃ n thÃ nh nhá»¯ng API sau.
*/

// v1, v2 chá»©a du lieu kieu int
// tráº£ vá»: -1 náº¿u v1 < v2
//          0 náº¿u v1 == v2
//          1 náº¿u v1 > v2
int CompareI(Jval v1, Jval v2);

// Äá»c dá»¯ liá»‡u Ä‘á»“ thá»‹ tá»« tá»‡p
JRB LoadGraph(const char* fname);

// tra ve danh sach cac dinh cua do thi g
Dllist GetVertices(JRB g);

// tra ve danh sach cac dinh ke cua u
Dllist GetAdjacents(JRB g, Jval u, int (*cmp)(Jval, Jval));

// tra ve danh sach dinh ke cua u theo tawng dan trong so canh
// tÄƒng dáº§n cá»§a trá»ng sá»‘ cáº¡nh
//      hÃ m cmp_key dung de so sanh khoa
//      hÃ m cmp_value dung de so sanh trong so
// vÃ­ dá»¥: vá»›i Ä‘á»“ thá»‹ Ä‘Ã£ cho,
//        GetAdjacentsW(g, new_jval_i(1), CompareI, CompareI)
//        tráº£ vá» {new_jval_i(2), new_jval_i(5), new_jval_i(3)}
Dllist GetAdjacentsW(JRB g, Jval u, int (*cmp_key)(Jval, Jval),
                                  int (*cmp_value)(Jval, Jval));

#endif  // MIDTERM_H_