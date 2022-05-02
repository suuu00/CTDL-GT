#include <string>
#include <stdlib.h> // free 
#include <fstream>
#include<ctime> 
#define TRUE 1
#define FALSE 0
#include "Ngay_Gio.h" 
string td_chuyen_bay[7] = {"Ma CB: ", "San bay den: ", "Ngay: ", "Gio: ", "Trang thai: ", "So hieu MB: ", "So ghe trong: "};
string td_khach[5] = {"CNMD: ", "Ho: ", "Ten: ", "Gioi tinh: ", "Ho ten: "};
string td_ve[7] = {"Ma CB: ", "San bay den: ", "Gio: ","Ngay: ", "So ghe: ", "CMND: ", "Ho ten: " }; 
// tim nut co vi tri la i 
PTRCB nodepointer(PTRCB First, int i)
{
	PTRCB p;
	int vitri=1;
	p = First;
	while(p != NULL && vitri < i)
	{
		p = p->next;
		vitri++;
	}
	return(p);
}
// Tac vu position: xac dinh vi tri cua nut p trong danh sach lien ket
int position(PTRCB First, PTRCB p)
{
	int vitri;
	PTRCB q;
	q = First;
	vitri = 1;
	while(q != NULL && q != p)
	{
		q = q->next;
		vitri++;
	}
   if(q == NULL)
      return(-1);
   return(vitri);
}
// Tac vu Empty: kiem tra danh sach lien ket co bi rong khong
int Empty(PTRCB First)
{
   return(First == NULL ? TRUE : FALSE);
}
// Phep toan clearlist: xoa tat ca cac nut trong danh sach lien ket
void clearlist(PTRCB &First)
{
   PTRCB p, q;  // q la nut truoc, p la nut sau
   p = First;
   while(First != NULL)
   {
      p = First;
      First = First->next;
      free(p);
   }
}
void traverse(PTRCB First)
{
   PTRCB p;
   p = First;
   if(p == NULL)
      printf("\n   (Khong co chuyen bay nao trong danh sach)");
   while(p != NULL)
   {
      	cout<< p->data.maCB<<endl;
  	 	cout<< p->data.sanBayDen<<endl;
		cout<< p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam<<endl; 
   		cout<< p->data.trangThai<<endl;
	 	cout<< p->data.soHieuMB<<endl;
       p = p->next;
   }
}
 //them mot nut co noi dung x vao dau danh sach lien ket 
void Insert_First(PTRCB &First, PTRCB p)
{
   p->next = First;
   First = p;
}
// them mot nut co noi dung x vào nut co dia chi p trong danh sach lien ket first 
void Insert_after(PTRCB p, PTRCB q)
{
   if(p == NULL)
		printf("khong them phan tu vao danh sach duoc");
   else
   { 
      q->next = p->next;
      p->next = q;
   }
}
void chuan_hoa0(string &s) // tat ca la ky tu thuong
{
	// xoa khoang trang dau
	while(s[0] == ' ')
	{
		s.erase(s.begin() + 0);
	}
	// xoa khoang trang cuoi
	while(s[s.length()-1] == ' ')
	{
		s.erase(s.begin() + s.length() - 1);
	}
	// xoa khoang trang giua
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == ' ' && s[i+1] == ' ')
		{
			s.erase(s.begin() + i);
			i--;
		}
	}
	// chuan hoa ki tu
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] >= 'A' && s[i] <= 'Z')
		{
			s[i] += 32;
		}
	}
}
void chuan_hoa1(string &s) // in hoa chu cai dau cua moi tu
{
	// xoa khoang trang dau
	while(s[0] == ' ')
	{
		s.erase(s.begin() + 0);
	}
	// xoa khoang trang cuoi
	while(s[s.length()-1] == ' ')
	{
		s.erase(s.begin() + s.length() - 1);
	}
	// xoa khoang trang giua
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == ' ' && s[i+1] == ' ')
		{
			s.erase(s.begin() + i);
			i--;
		}
	}
	// chuan hoa ki tu
	if(s[0] >= 'a' && s[0] <= 'z')
	{
		s[0] -= 32;
	}
	for(int i=1 ; i<s.length() ; i++)
	{
		if(s[i] == ' ')
		{
			i++;
			if(s[i] >= 'a' && s[i] <= 'z')
			{
				s[i] -= 32; // in hoa ki tu dau cua moi tu
			}
		}
		else
		{
			if(s[i] >= 'A' && s[i] <= 'Z')
			{
				s[i] += 32;
			}
		}
	}
}
void chuan_hoa2(string &s) // tat ca la ky tu in hoa
{
	// xoa khoang trang dau
	while(s[0] == ' ')
	{
		s.erase(s.begin() + 0);
	}
	// xoa khoang trang cuoi
	while(s[s.length()-1] == ' ')
	{
		s.erase(s.begin() + s.length() - 1);
	}
	// xoa khoang trang giua
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == ' ' && s[i+1] == ' ')
		{
			s.erase(s.begin() + i);
			i--;
		}
	}
	 
	// chuan hoa ki tu
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] -= 32;
		}
	}
}
void Create_list(PTRCB &First) {
	PTRCB Last ;
	PTRCB temp =  new nodeCB; //con tro trung gian de them
	string kiemTraMaCB; 
	cout<<"Ma chuyen bay: ";
	cin >> kiemTraMaCB; 
	while (kiemTraMaCB.compare("0")!=0 ){
		temp->data.maCB = kiemTraMaCB;
		cout<<"San bay den: ";
		cin >> temp->data.sanBayDen;
		cout<<"Trang thai: ";
		cin >> temp->data.trangThai;
		cout<<"So hieu may bay: ";
		cin >> temp->data.soHieuMB;
		if (First==NULL)		
			First=temp;
		else
			Last->next = temp;
		Last=temp;
		temp->next = NULL;
		temp = new nodeCB;
		cout<<"Ma chuyen bay moi: ";
		cin >> kiemTraMaCB; 
		//cin>> temp->data.maCB;
	}
}

bool CheckChuyenBay (PTRCB &First , string str) // neu trung thi tra ve false 
{
	PTRCB p;
	for (p = First; p!=NULL; p=p->next)
		if (str.compare(p->data.maCB) == 0) return true;
	return false;
}
bool Check_SoHieuMB (DanhSachMB &ds, string str)
{
	for (int i=0; i < ds.n; i++) 
	{
		if (str.compare(ds.nodes[i]->soHieuMB) == 0) return true;
	}
	return false;
}

int Dem_ChuyenBay (PTRCB First)
{
	int dem = 0; 
	PTRCB p;
	for (p = First; p!=NULL; p=p->next)
	{
		dem++; 
	}
	return dem; 
 } 
void check_ThoiGian (PTRCB p)
{
						Date n_date;
						Hour n_hour; 
						Date v = NgayHienTai(); 
						cout<< "Thoi gian (HH:mm dd/MM/yyyy):  ";
						do {
	 						cin>> n_hour.gio>>n_hour.phut;
 							cin>> n_date.ngay>>n_date.thang>>n_date.nam;
 							if (check_Date(n_date) != true) {
								cout<<"Nhap lai, thoi gian (HH:mm dd/MM/yyyy): ";
							} else if (GioHopLe(n_hour)==false) {
								cout<<"Nhap lai, thoi gian (HH:mm dd/MM/yyyy): ";
							}
						} while (check_Date(n_date) != true || GioHopLe(n_hour)==false);
	 					p->data.thoiGian.date = n_date;
	 					p->data.thoiGian.h=n_hour;	
 } 
 
void themCB( PTRCB &First, ListMB &ds)
{
			int b; // neu = 0 thoat khong them nua, con 1 thi them
			string str; 
			PTRCB temp =  new nodeCB;
			cout<<"\tThem chuyen bay\n";
			cout<<"Lua chon ( 0: Thoat || 1: Them): "; 
			cin>>b;
				while (b != 0) {
					fflush(stdin);
					cout<<"Ma chuyen bay moi (nhap den khi khong trung): ";
					do {
						getline (cin, str);
						if (str.compare("") == true) cout<<"Nhap lai, ma chuyen bay: ";
						else {
							chuan_hoa2(str); 
							if (CheckChuyenBay(First, str) == true) cout<<"Nhap lai, ma chuyen bay: ";
							else {
								temp->data.maCB = str;
							} 
						}
					}while (CheckChuyenBay(First, str) == true); 
					cout<<"San bay den: ";
					getline (cin, str); 
					chuan_hoa2(str);
					temp->data.sanBayDen = str; 
					check_ThoiGian(temp); 
					cout<<"Trang thai: 1\n";
					temp->data.trangThai = 1;
					fflush(stdin);
					cout<<"So hieu may bay: ";
					
					do {
						getline (cin, str);
						if (str.compare("") == true) cout<<"Nhap lai, ma chuyen bay: ";
						else {
							chuan_hoa2(str); 
							if (Check_SoHieuMB(ds, str) == false) cout<<"Nhap lai, so hieu may bay: "; 
							else {
								temp->data.soHieuMB = str;
							} 
						}
					} while (Check_SoHieuMB(ds, str) == false);
					Insert_First(First, temp);
					cout<<"Lua chon ( 0: Thoat || 1: Them): "; 
					cin>>b;
					temp =  new nodeCB;
			}
}

PTRCB TimKiemTheoMaCB (PTRCB &First , string str)
{
	PTRCB p;
	if (First == NULL) return NULL;
	for (p = First; p!=NULL; p=p->next)
		if (str.compare(p->data.maCB) == 0) 
			return p;
	return NULL;
}

//Nhan them trong khoang nay
PTRCB TimKiemTheoNgayThang (PTRCB &First , string thoiGian[3])
{
	PTRCB p;
	if (First == NULL) return NULL;
	for (p = First; p!=NULL; p=p->next)
		if ((stoi(thoiGian[0]) == p->data.thoiGian.date.ngay) && (stoi(thoiGian[1]) == p->data.thoiGian.date.thang)
										&& (stoi(thoiGian[2]) == p->data.thoiGian.date.nam)) 
			return p;
	return NULL;
}
PTRCB TimKiemTheoSanBayDen (PTRCB &First , string str)
{
	PTRCB p;
	if (First == NULL) return NULL;
	for (p = First; p!=NULL; p=p->next)
		if (str.compare(p->data.sanBayDen) == 0) 
			return p;
	return NULL;
}
//void TimKiemTheoDiaDiemVaThoiGian (PTRCB First , string chuoi[4], int x, int y)
//{
//	PTRCB p;
//	int j=0;
//	if (First == NULL) {
//		gotoxy (76,34);
//		cout<<"Khong co chuyen bay phu hop";
//		sleep(1500);
//		gotoxy (76, 34);
//		cout << setw(60) << setfill(char(32)) << " "; 
//		char k;
//		do {
//			
//		}
//	}
//	for (p = First; p!=NULL; p=p->next)
//		if ((stoi(chuoi[0]) == p->data.thoiGian.date.ngay) && (stoi(chuoi[1]) == p->data.thoiGian.date.thang)
//			&& (stoi(chuoi[2]) == p->data.thoiGian.date.nam) && (chuoi[3].compare(p->data.sanBayDen) == 0)){
//					gotoxy(x, y+j);
//			      	cout<< " "<<p->data.maCB<<" ";
//			      	gotoxy(x+7, y+j);
//			  	 	cout<< " "<<p->data.sanBayDen<<" ";
//			  	 	gotoxy(x+24, y+j);
//					cout<< " "<<p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" ";
//					gotoxy(x+24+10, y+j);
//					cout<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam; 
//			   		gotoxy(x+44+3, y+j);
//					if (p->data.trangThai == 1)cout<<p->data.ve.SoVeMax-p->data.ve.SoVeDaDat;
//					gotoxy(x+59+3, y+j);
//				 	cout<< " "<<p->data.soHieuMB<<" ";	
//					j++;						
//				}
//}

// Nhan them trong khoang nay
void HieuChinhThoiGian (PTRCB &First)
{
	int t;
	cout<<"\tHieu chinh thoi gian bay\n";
	cout<<"1: Theo thoi gian\n2: Theo ma chuyen bay\n" ;
	cout<<"Lua chon: "; 
	cin>>t;
	switch (t)
	{
		case 1:
			{
				Date date;
				cout<<"Nhap thoi gian can chinh sua (dd/MM/yyyy): ";
				NhapNgay(date);
				int i = 0; 
				int vitri = 0; 
				static int a[100]; 
				PTRCB p;
				for (p = First; p!=NULL; p=p->next)
				{
					vitri++; 
					if (p->data.thoiGian.date.nam == date.nam && p->data.thoiGian.date.thang == date.thang && p->data.thoiGian.date.ngay == date.ngay)
					{
						 a[i]=vitri;
						 i++; 
						cout<<"Chuyen bay "<<i<<":\n"; 
						cout<< p->data.maCB<<endl;
  	 					cout<< p->data.sanBayDen<<endl;
						cout<< p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam<<endl; 
   						cout<< p->data.trangThai<<endl;
	 					cout<< p->data.soHieuMB<<endl;
	 					
					} 
				}
			
				int viTriHieuChinh; 
				cout<<"Chuyen bay muon chinh sua: "; // nhap 0 hoac >i de Thoat
				cin>>viTriHieuChinh;
				while (viTriHieuChinh > 0 & viTriHieuChinh <= i)
				{
					p = nodepointer(First, a[viTriHieuChinh-1]);
					if (p != NULL)
					{
						check_ThoiGian(p);	
				 	}
					cout<<"Chuyen bay muon chinh sua: "; 
					cin>>viTriHieuChinh;  	
			}
				break;
			}
		case 2:
			{
				string str;
				cout<<"Nhap ma chuyen bay can chinh sua: ";
				cin>>str; 
				PTRCB p = TimKiemTheoMaCB(First, str);				
				if (p != NULL)
				{
					Date n_date;
					Hour n_hour;
					cout<< "Chuyen bay can hieu chinh\n";
					cout<< p->data.maCB<<endl;
  	 				cout<< p->data.sanBayDen<<endl;
					cout<< p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam<<endl; 
   					cout<< p->data.trangThai<<endl;
	 				cout<< p->data.soHieuMB<<endl;
					check_ThoiGian(p);
				}
				else 
				{
					cout<<"Khong chinh sua duoc!\n";
					break; 
				 } 
				break;
			}		
	}
 } 
// Cap nhat du lieu khi huy chuyen
void HuyCB (PTRCB p)
{
	p->data.trangThai = 0;
	
	
	
	// cap nhat lai ve voi CMND = ""
	
	
 } 
 // Huy chuyen bay theo ma chuyen bay 
 void HuyChuyenBay (PTRCB &First)
 {
 	string macb;
	cout<<"Nhap ma chuyen bay can huy chuyen: ";
	cin>>macb;	
 	PTRCB p = TimKiemTheoMaCB(First, macb);
 	if (p != NULL)
 	{
 		HuyCB(p);
 		cout<<p->data.trangThai;
	 }
 }
 
//============== XU LY DANH SACH VE ================
int TimKiem_MB_SH (DanhSachMB &dsmb, string str) // tim kiem vi tri cua may bay theo so hieu
{
	for (int i=0; i < dsmb.n; i++)
	{
		if (str.compare(dsmb.nodes[i]->soHieuMB) == 0) return i;
	}
	return -1;
 } 
void LaySoGhe_MayBay  (PTRCB p, DanhSachMB &dsmb)
{
	if (TimKiem_MB_SH(dsmb, p->data.soHieuMB) >= 0)
	{
		p->data.ve.SoVeMax = dsmb.nodes[TimKiem_MB_SH(dsmb, p->data.soHieuMB)]->soCho;
	}
	else // neu khong co so hieu chuyen bay trong ds may bay thì so ve =0 
	p->data.ve.SoVeMax = 0; 
}

 
 
 
 
 
 
