/*
Cho tệp văn bản input.txt theo định dạng:
3
1 2 3
số đầu tiên là số lượng số nguyên (n), kế tiếp là n số nguyên cách nhau bởi dấu cách hoặc xuống dòng
hãy dùng API của libfdr hoàn thiện các ham theo nguyên mẫu sau.
*/
// trả về tất cả các vị trí tính từ 0 của x trong tệp input.txt
#include "dllist.h"

Dllist SearchN(const char* fname, int x);