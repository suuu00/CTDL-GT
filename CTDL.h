#define  MAXMB 300
#define  MAXCHO  1000
using namespace std; 

struct MayBay {
	string soHieuMB;
	string loaiMB;
	int soCho;
};
typedef struct DanhSachMB {
	int n=0;
	MayBay *nodes[MAXMB]; 
}ListMB;

struct Date {
    int ngay;
    int thang;
    int nam;
};
struct Hour {
    int gio;
    int phut;
};
struct Time {
    Date date;
    Hour h;
};

// danh sach tuyen tinh cap phat dong
struct Ve {
	string cmnd; // 12 so
};
struct DanhSachVe {
	int SoVeMax;
	int SoVeDaDat; 
	Ve *danhSach; 
};  
//========== CHUYEN BAY 
// DANH SACH LIEN KET DON
struct ChuyenBay {
	string maCB;
	Time thoiGian; 
	string sanBayDen;
	int trangThai; // 0:huy chuyen | 1:con ve | 2:het ve | 3:hoan tat
	string soHieuMB;
	DanhSachVe ve; 
}; 
struct nodeCB {
	ChuyenBay data;
	nodeCB *next;
};
typedef nodeCB *PTRCB; 

// Cay nhi phan tim kiem
struct HanhKhach {
	string cmnd;
	string ho;
	string ten;
	int phai; // 0 la nam, 1 la nu 
};

struct nodeHanhKhach {
	HanhKhach data;
	nodeHanhKhach *right = NULL;
	nodeHanhKhach *left = NULL;
};
typedef nodeHanhKhach *NODEPTR;
