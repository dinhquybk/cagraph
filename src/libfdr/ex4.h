#ifndef EX4_H_
#define EX4_H_

#include "dllist.h"

// Tim kiem tuan tu, tra ve phan tu dau tien
//    - Tra ve nut co gia tri = item neu tim thay
//    - Tra ve NULL neu khong tim thay
//    - Jval co the luu gia tri int, float, char*
Dllist SearchDL(const Dllist list, 
                const Jval* item,
                int (*compare)(const Jval*, const Jval*));

// so sÃ¡nh trÆ°á»ng i
int jval_compare_i(const Jval*, const Jval*);

// so sÃ¡nh trÆ°á»ng f
int jval_compare_f(const Jval*, const Jval*);

// so sÃ¡nh trÆ°á»ng s
int jval_compare_s(const Jval*, const Jval*);

#endif  // EX4_H_