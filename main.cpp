#include <iostream>
#include "veMenu.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	DanhSachMB danhSachMB;
	loadMayBay(danhSachMB);
	PTRCB First = NULL; 
	LoadChuyenBay(First);  
	CapNhatTrangThaiChuyenBay(First);
	NODEPTR root=NULL;
	LoadHanhKhach(root);
	khoiDong(danhSachMB, First, root);
	saveMayBay(danhSachMB);
	GhiFileChuyenBay(First);
	saveHanhKhach(root);
	return 0;
}
