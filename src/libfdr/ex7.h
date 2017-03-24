/*
  Äá»c dá»¯ liá»‡u tyáº¿n xe bus tá»« tá»‡p vÄƒn báº£n theo Ä‘á»‹nh dáº¡ng sau:
  ------------VÃ­ dá»¥ ná»™i dung file bus.txt-------------------
[STATIONS]
S1=DBHKN
S2=Cong vien Thong Nhat
S3=Ho Hoan Kiem
S4=Thai Ha
S5=Chua Boc
S6=BX My Dinh
[LINES]
M1=S6 S5 S3
M2=S1 S2 S3 S4 S5 S6
  -----------------------------------------------------------
  Hàm LoadData trả về vá» Ä‘á»“ thá»‹ Web theo cáº¥u trÃºc:
    S1: (S2: M2) 
    S2: (S3: M2),
    ...
    S5: (S3: M1), (S6: M2)
  - *nodes lÃ  cÃ¢y lÆ°u dá»¯ liá»‡u vá» Ä‘á»‰nh:
      (S1:DHBKHN), (S2:Cong vien thong nhat) ...
  - *lines lÃ  cÃ¢y lÆ°u dá»¯ liá»‡u vá» tuyáº¿n Ä‘Æ°á»ng:
      (M1: (S6, S5, S3)), (M2: (S1, S2, S3, S4, S5, S6))
      
  gá»£i Ã½: JRB, new_jval_s(char*), Dlllist
*/

#include "jrb.h"

JRB LoadData(const char* fname, JRB* nodes, JRB* lines);