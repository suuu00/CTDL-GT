#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include "mylib.h"
#include <sstream>
#include <iomanip>
#include "CTDL.h"
#include "MayBay.h"
#include "NhanLib.h"
#include "loadFile.h"
#include "ghiFile.h" 
#include "huonglib.h"
using namespace std;
const int UP = -72;
const int DOWN = -80;
const int LEFT = -75;
const int RIGHT = -77;
const int TAB = 9;
const int ENTER = 13;   
const int BACKSPACE = 8;
const int SPACE = 32;
const int CtrlS = 19;
const int CtrlF = 6;
const int InSert = -82;
const int DEL = -83;
const int ESC = 27;
const int F1 = -59;
const int F2 = -60;
const int F3 = - 61;
const int FirstX = 0;
const int FirstY = 9;
const int SecondX = 40;
const int ThirdX = 124;
const int FourX = 140;
const int maxRow = 15;
const int x_thongBao = 76;
const int y_thongBao = 34;
const int x_chuyenBay = 76;
const int y_chuyenBay = 12;
const int x_CB_DatVe = 41;
const int y_CB_DatVe = 25; 
int GetKey() //Dung de phan biet phim mui ten vs phim thuong 
{
	char key;
	key = getch();
	if(key == -32 || key == 0)
		return (-getch());
	return key;	
}
void Normal () {
	SetColor(15);
	SetBGColor(0);
}
void HighLight () {
	SetColor(4);
	SetBGColor(14);
}			              
void veHop (int x, int y, int dai, int rong, int color, int bang, string str){
	SetColor(color);
	SetBGColor(0);
	for (int ix=x; ix<=dai+x; ix++){
		gotoxy(ix, y);
		cout << char(196);
		gotoxy(ix, y+rong);
		cout << char(196);
	}
	for (int iy=y; iy<=rong+y; iy++){
		gotoxy(x, iy);
		cout << char(179);
		gotoxy(x+dai, iy);
		cout << char(179);
	}
	gotoxy(x, y); cout << char(218);
	gotoxy(x+dai, y); cout << char(191);
	gotoxy(x, y+rong); cout << char(192);
	gotoxy(x+dai, y+rong); cout << char(217);
	
	if (bang==1)
		for (int ix=x+1; ix<dai+x; ix++){
			gotoxy(ix, y+2);
			cout << char(196); 
		}
		gotoxy (x+1, y+1);
		cout<<str;
}
string huong_dan[] = {	"ESC: Quay lai ",			//0 
						"LEFT/RIGHT: Chuyen trang ",//1 
						"UP/DOWN: Di chuyen ",		//2 
						"CTRL+S: Luu ",				//3 
						"CTRL+F: Tim kiem ",		//4 
						"INSERT: Them ",			//5 
						"DELETE: Xoa/huy ",			//6 
						"F2: Hieu chinh thoi gian ",//7 
						"ENTER: Chon chuyen bay  " ,//8 
						"ENTER: Dat ghe ",			//9 
						"F1: Ket xuat khach hang"	//10 
}; 
void in_huong_dan (int y, int hd) {
	Normal();
	gotoxy(1, FirstY+10+y);
	cout << setw(34)<< setfill(char(32)) << " ";
	gotoxy(1, FirstY+10+y);
	cout << huong_dan[hd];
}
void xoa_huong_dan () {
	Normal();
	for (int i=0; i<9; i++){
	gotoxy(1, FirstY+10+i);
	cout << setw(34)<< setfill(char(32)) << " ";
	}
}
void veBangMB (int x, int y, int soLuong){
	veHop(x, y, 20, soLuong+3, 10, 1,"So hieu may bay" );
	veHop(x+20, y, 44, soLuong+3, 10, 1, "Loai may bay");
	veHop(x+64, y, 7, soLuong+3, 10, 1, "So cho");
}
char mnNgoai [7][50] =   {"1. Quan ly may bay        ",
			              "2. Quan ly chuyen bay     ",
			              "3. Quan ly ve",
			              "4. Xem ds ve cua chuyen bay X",
			              "5. Xem ds chuyen bay ",
			              "6. In ds ve trong cua chuyen bay X",
			              "7. Ket thuc chuong trinh  ",};
int menuNgoai (char mn[7][50]){
	Normal();
	int chon=0;
	veHop(0, 8, 35, 10, 15, 1,"QUAN LY CAC CHUYEN BAY");
	veHop (0, 19, 35, 12, 15,0, "");
	for (int i=0; i<7; i++){
		gotoxy(FirstX+1, FirstY+i+2);
		cout << mn[i];
	}
	gotoxy(FirstX+1, FirstY+chon+2);
	HighLight();
	cout << mn[chon];
	char kytu;
	do{
		kytu = GetKey(); 
		switch (kytu){
			case UP: if (chon+1>1){
					Normal();
              		gotoxy(FirstX+1, FirstY+chon+2);
              		cout << mn[chon];
              		chon --;
              		HighLight();
              		gotoxy(FirstX+1, FirstY+chon+2);
              		cout << mn[chon];
				}
				break;
			case DOWN :if (chon+1 <7){
	  		        Normal();
              		gotoxy(FirstX+1, FirstY+chon+2);
              		cout << mn[chon];
              		chon ++;
              		HighLight();
              		gotoxy(FirstX+1, FirstY+chon+2);
              		cout << mn[chon];
              		
  			  	}
  			  	break;
  			case ENTER : return chon+1;
		}
	}while (1);
}
void veMenuMayBay (){
	veHop(SecondX+50, FirstY, 17, 20, 15, 1, "So hieu may bay" ); 
	veHop(SecondX+50+17, FirstY, 42, 20, 15, 1, "               Loai may bay               ");
	veHop(SecondX+50+59, FirstY, 8, 20, 15, 1, "So cho");
	gotoxy(FourX, FirstY+21);
	cout << "Trang:    /   " ;
}
void xoaTrang (int x, int y){
	Normal();
	for(int i = 0; i < maxRow; i++){
		gotoxy(x+1, y+3+i);
		cout << "               "; 
		gotoxy(x+18, y+3+i);
		cout << "                                        "; 
		gotoxy(x+60, y+3+i);
		cout << "      ";
	}
}
void xoabang (int x, int y, int soDong, int soKiTuCanXoa){
	Normal();
	for(int i = 0; i < soDong; i++){
		gotoxy(x, y+i);
		cout << setw(soKiTuCanXoa) << setfill(char(32)) << " ";
	}
}
void resetBangThem(){
	for (int i=1; i<=3; i++){
		gotoxy(SecondX+15, FirstY+i);
		cout << setw(31) << setfill(char(32)) << " ";
	}
	gotoxy(ThirdX+15, FirstY+1);
}
void resetMenuMayBay (int x, int y){
	Normal();
	for(int i = 0; i < maxRow; i++){
		gotoxy(x+1, y+3+i);
		cout << "               "; 
		gotoxy(x+18, y+3+i);
		cout << "                                        "; 
		gotoxy(x+60, y+3+i);
		cout << "      ";
	}
}
void duLieuMayBay (DanhSachMB &danhSachMB, int x, int y, int trangSo, int trangCuoi){

	gotoxy(FourX+7, FirstY+21);
	cout << trangSo+1;
	gotoxy(FourX+12, FirstY+21);
	cout << trangCuoi;
	
	int j=0;
	for(int i = 0+trangSo*maxRow; i < maxRow+trangSo*maxRow; i++){ 
		if (i==danhSachMB.n)
			break;
		if (j==maxRow)
			j=0;
		gotoxy(x+1, y+3+j);
		cout << " " <<danhSachMB.nodes[i]->soHieuMB<< " "; 
		gotoxy(x+18, y+3+j);
		cout << " " << danhSachMB.nodes[i]->loaiMB<< " "; 
		gotoxy(x+60, y+3+j);
		cout << " " << danhSachMB.nodes[i]->soCho<< " ";
		j++;
	}
}
int xuLy1Dong (DanhSachMB &danhSachMB, int viTri, int trangSo, int coMau){
	if (viTri+trangSo*15 == danhSachMB.n)
		return 0;
	if (coMau == 1)
		HighLight();
	else Normal();
	gotoxy(SecondX+50+1, FirstY+3+viTri);
	cout << " " << danhSachMB.nodes[viTri+trangSo*15]->soHieuMB<< " "; 
	gotoxy(SecondX+50+18, FirstY+3+viTri);
	cout << " " << danhSachMB.nodes[viTri+trangSo*15]->loaiMB<< " "; 
	gotoxy(SecondX+50+60, FirstY+3+viTri);
	cout << " " << danhSachMB.nodes[viTri+trangSo*15]->soCho<< " ";

}
void xoaBang (int x, int y, int soDong){
	Normal();
	for(int i = 0; i < soDong; i++){
		gotoxy(x, y+i);
		cout << "                                                    "; 
	}
}
void veThemMayBay (){
	Normal();
	veHop(SecondX, FirstY, 46, 5, 15, 0, "");
	gotoxy(SecondX+1, FirstY+1);
	cout << "So hieu:";
	gotoxy(SecondX+1, FirstY+2);
	cout << "Loai may bay:";
	gotoxy(SecondX+1, FirstY+3);
	cout << "So cho:";
	int n, vt = 0, soHieu = 0, loai = 0, soCho = 0;
	string shtam, ltam, sotam;
	gotoxy(SecondX+15, FirstY+1);
}
void ChuanHoaMa(string &s){  // In hoa tat ca chu cai trong ma
	for(size_t i = 0; i < s.length(); i++) //Xoa khoang trang thua
	{
		if(s[i] == ' ')
		{
			s.erase(i, 1);
			i--;
		}
	}
	for(size_t i = 0; i < s.length(); i++) //Xoa khoang trang thua
	{
		if(s[i] >= 97 && s[i] <= 122)
		{
			s[i] = s[i] - 32;
		}
	}
}
void ChuanHoaString(string &s) // Xoa khoang trang thua vs in hoa chu cai dau
{
	for(size_t i = 0; i < s.length(); i++) //Xoa khoang trang thua
	{
		if(s[0] == ' ')
		{
			s.erase(0, 1);
			i--;
		}
		else if(s[i] == ' ' && s[i + 1] == ' ')
		{
			s.erase(i, 1);
			i--;
		}
		else if(s[s.length() - 1] == ' ') s.erase(s.length() - 1, 1);
	}
	for(size_t i = 0; i < s.length(); i++) //In hoa chu cau dau
	{
		if(s[0] >= 97 && s[0] <= 122)
		{
			s[0] = s[0] - 32;
		}
		if(s[i] == ' ')
		{
			if(s[i + 1] >= 97 && s[i + 1] <= 122)
				s[i + 1] = s[i + 1] - 32;
		}
		if(s[i] != ' ')
		{
			if(s[i + 1] >= 65 && s[i + 1] <= 90)
				s[i + 1] = s[i + 1] + 32;
		}
	}
}
int xuLiNhapMayBay (DanhSachMB &danhSachMB){
	int n, vt = 0, soHieu = 0, loai = 0, soCho = 0, check =0;					
	string soTam;
	MayBay *mayBay;
	mayBay = new MayBay;
	char c;
	gotoxy(SecondX+15 + mayBay->soHieuMB.length(), FirstY+1 + vt);
	do
	{
		c = GetKey();
		switch (c)
		{
			case UP: if(vt + 1 > 1) //Dua con nhay len tren
			{
				vt--;
				if(vt == 0) gotoxy(SecondX+15 + mayBay->soHieuMB.length(), FirstY+1 + vt);
				else if(vt == 1) gotoxy(SecondX+15 + mayBay->loaiMB.length(), FirstY+1 + vt);
				else gotoxy(SecondX+15 + soTam.length(), FirstY+1 + vt);
			} break;
			case ENTER: if(vt + 1 < 3) //Xuong dong
			{
				vt++;
				if(vt == 0) gotoxy(SecondX+15 + mayBay->soHieuMB.length(), FirstY+1 + vt);
				else if(vt == 1) gotoxy(SecondX+15 + mayBay->loaiMB.length(), FirstY+1 + vt);
				else gotoxy(SecondX+15 + soTam.length(), FirstY+1 + vt);
			} break;
			case DOWN: if(vt + 1 < 3) //Xuong dong
			{
				vt++;
				if(vt == 0) gotoxy(SecondX+15 + mayBay->soHieuMB.length(), FirstY+1 + vt);
				else if(vt == 1) gotoxy(SecondX+15 + mayBay->loaiMB.length(), FirstY+1 + vt);
				else gotoxy(SecondX+15 + soTam.length(), FirstY+1 + vt);
			} break;
			
			case CtrlS: //Luu doc gia
			{
				ChuanHoaMa(mayBay->soHieuMB);
				ChuanHoaString(mayBay->loaiMB);
				if(mayBay->soHieuMB.compare("") == 0)
				{
					HighLight();
					gotoxy(SecondX+10, FirstY+6); cout << "Khong duoc de trong so hieu may bay";
					Sleep(2000);
					Normal();
					gotoxy(SecondX+10, FirstY+6); cout << "                                   ";
					vt=0;
					gotoxy(SecondX+15 + mayBay->soHieuMB.length(), FirstY+1 + vt);
					
				}
				else if(mayBay->loaiMB.compare("") == 0)
				{
					HighLight();
					gotoxy(SecondX+10, FirstY+6); cout << "Khong duoc de trong loai may bay";
					Sleep(2000);
					Normal();
					gotoxy(SecondX+10, FirstY+6); cout << "                                   ";
					vt=1;
					gotoxy(SecondX+15 + mayBay->loaiMB.length(), FirstY+1 + vt);
				}
				else if(soTam.compare("") == 0)
				{
					HighLight();
					gotoxy(SecondX+10, FirstY+6); cout << "Khong duoc de trong so cho ngoi";
					Sleep(2000);
					Normal();
					gotoxy(SecondX+10, FirstY+6); cout << "                                   ";
					vt=2;
					gotoxy(SecondX+15 + soTam.length(), FirstY+1 + vt);
				}
				else if (stoi(soTam) < 20)
				{
					HighLight();
					gotoxy(SecondX+10, FirstY+6); cout << "So cho ngoi it nhat la 20";
					Sleep(2000);
					Normal();
					gotoxy(SecondX+10, FirstY+6); cout << "                          ";
					vt=2;
					gotoxy(SecondX+15 + soTam.length(), FirstY+1 + vt);
				}
				else
				{
					check = CheckTrungMaMayBay(danhSachMB, mayBay->soHieuMB);
					if (check != -1){
						HighLight();
						gotoxy(SecondX+10, FirstY+6);
						cout << "So hieu may bay bi trung";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+10, FirstY+6);
						cout << "                        ";
						vt=0;
						gotoxy(SecondX+15 + mayBay->soHieuMB.length(), FirstY+1 + vt);
					}else{
						mayBay->soCho = stoi(soTam);
						Insert_item(danhSachMB, danhSachMB.n, mayBay);
						delete mayBay;
						HighLight();
						gotoxy(SecondX+10, FirstY+6); cout << "Du lieu da duoc luu lai ";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+10, FirstY+6); cout << "                        ";
						return 1;			
					}
				}
				break;
			}
			case ESC: return 0;
			default: switch(vt)
			{
				case 0: //Vi tri con tro o phan soHieu
				{
					if(c == BACKSPACE)
					{
						if(mayBay->soHieuMB.length() > 0)
						{
							gotoxy(SecondX+15 + mayBay->soHieuMB.length()-1, FirstY+1 + vt); cout << " ";
							gotoxy(SecondX+15 + mayBay->soHieuMB.length()-1, FirstY+1 + vt);
							mayBay->soHieuMB = mayBay->soHieuMB.substr(0, mayBay->soHieuMB.length()-1);
						}		
					}
					else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57)) //Lay chu cai hoa, chu thuong, so
					{
						mayBay->soHieuMB +=c;
						cout << c;
					}	
				} break;
				case 1: //Vi tri con tro o phan loai
				{
					if(c == BACKSPACE)
					{
						if(mayBay->loaiMB.length() > 0)
						{
							gotoxy(SecondX+15 + mayBay->loaiMB.length()-1, FirstY+1 + vt); cout << " ";
							gotoxy(SecondX+15 + mayBay->loaiMB.length()-1, FirstY+1 + vt);
							mayBay->loaiMB = mayBay->loaiMB.substr(0, mayBay->loaiMB.length()-1);
						}	
					}
					else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 32) //Lay chu cai in thuong, in hoa vs khoang trang
					{
						mayBay->loaiMB +=c;
						cout << c;
					}
				} break;
				case 2: //Vi tri con tro o phan soCho
				{
					if(c == BACKSPACE)
					{
						if(soTam.length() > 0)
						{
							gotoxy(SecondX+15 + soTam.length()-1, FirstY+1 + vt); cout << " ";
							gotoxy(SecondX+15 + soTam.length()-1, FirstY+1 + vt);
							soTam = soTam.substr(0, soTam.length()-1);
						}	
					}
					else if(c >= 48 && c <= 57) //Chi lay so
					{
						soTam += c;
						cout << c;
					}
				} break;
			}
		}
	} while(1);
}
int xuLiChinhSuaMayBay (DanhSachMB &danhSachMB, int viTri, int trangSo, PTRCB First){
	MayBay mb;
	mb.soHieuMB = danhSachMB.nodes[viTri+trangSo*15]->soHieuMB;
	mb.loaiMB = danhSachMB.nodes[viTri+trangSo*15]->loaiMB;
	mb.soCho = danhSachMB.nodes[viTri+trangSo*15]->soCho;
	gotoxy(SecondX+15, FirstY+1);
	cout << mb.soHieuMB;
	gotoxy(SecondX+15, FirstY+2);
	cout << mb.loaiMB;
	gotoxy(SecondX+15, FirstY+3);
	cout << mb.soCho;
	string soTam;
	soTam = to_string(danhSachMB.nodes[viTri+trangSo*15]->soCho);
	char c;
	int vt=1;
	int tonTai=0;
	tonTai = timMayBayTrongChuyenBay(First, mb.soHieuMB);
	if (tonTai == 1){
		gotoxy(SecondX+15 + mb.loaiMB.length(), FirstY+2);
		do{
			c = GetKey();
			switch (c)
			{
				case ESC: return 1;
				case CtrlS: //Luu doc gia
				{
					ChuanHoaString(mb.loaiMB);
					if(mb.loaiMB.compare("") == 0)
					{
						HighLight();
						gotoxy(SecondX+10, FirstY+6); cout << "Khong duoc de trong loai may bay";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+10, FirstY+6); cout << "                                   ";
						vt=1;
						gotoxy(SecondX+15 + mb.loaiMB.length(), FirstY+2);
					}
					else
					{
						danhSachMB.nodes[viTri+trangSo*15]->loaiMB = mb.loaiMB;
						HighLight();
						gotoxy(SecondX+10, FirstY+6); cout << "Du lieu da duoc luu lai";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+10, FirstY+6); cout << "                       ";	
						return 1;			
					}
					break;
				}
				default:{
					if(c == BACKSPACE)
						{
							if(mb.loaiMB.length() > 0)
							{
								gotoxy(SecondX+15 + mb.loaiMB.length()-1, FirstY+2); cout << " ";
								gotoxy(SecondX+15 + mb.loaiMB.length()-1, FirstY+2);
								mb.loaiMB = mb.loaiMB.substr(0, mb.loaiMB.length()-1);
							}	
						}
					else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57)|| c == 32) //Lay chu cai in thuong, in hoa , so vs khoang trang
						{
							mb.loaiMB +=c;
							cout << c;
						}
					break;
				}
			}
		}while (1);	
	}else if(tonTai==0){
		gotoxy(SecondX+15 + mb.loaiMB.length(), FirstY+2);
		do
		{
			c = GetKey();
			switch (c)
			{
				case UP: if(vt + 1 > 2) //Dua con nhay len tren
				{
					vt--;
					if(vt == 1) gotoxy(SecondX+15 + mb.loaiMB.length(), FirstY+1 + vt);
					else gotoxy(SecondX+15 + soTam.length(), FirstY+1 + vt);
				} break;
				case ENTER: if(vt + 1 < 3) //Xuong dong
				{
					vt++;
					if(vt == 1) gotoxy(SecondX+15 + mb.loaiMB.length(), FirstY+1 + vt);
					else gotoxy(SecondX+15 + soTam.length(), FirstY+1 + vt);
				} break;
				case DOWN: if(vt + 1 < 3) //Xuong dong
				{
					vt++;
					if(vt == 1) gotoxy(SecondX+15 + mb.loaiMB.length(), FirstY+1 + vt);
					else gotoxy(SecondX+15 + soTam.length(), FirstY+1 + vt);
				} break;
				
				case CtrlS: //Luu doc gia
				{
					ChuanHoaString(mb.loaiMB);
					if(mb.loaiMB.compare("") == 0)
					{
						HighLight();
						gotoxy(SecondX+10, FirstY+6); cout << "Khong duoc de trong loai may bay";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+10, FirstY+6); cout << "                                   ";
						vt=1;
						gotoxy(SecondX+15 + mb.loaiMB.length(), FirstY+1 + vt);
					}
					else if(soTam.compare("") == 0)
					{
						HighLight();
						gotoxy(SecondX+10, FirstY+6); cout << "Khong duoc de trong so cho ngoi";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+10, FirstY+6); cout << "                                ";
						vt=2;
						gotoxy(SecondX+15 + soTam.length(), FirstY+1 + vt);
					}
					else if (stoi(soTam) < 20)
					{
						HighLight();
						gotoxy(SecondX+10, FirstY+6); cout << "So cho ngoi it nhat la 20";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+10, FirstY+6); cout << "                          ";
						vt=2;
						gotoxy(SecondX+15 + soTam.length(), FirstY+1 + vt);
					}
					else
					{
						danhSachMB.nodes[viTri+trangSo*15]->loaiMB = mb.loaiMB;
						danhSachMB.nodes[viTri+trangSo*15]->soCho = stoi(soTam);
						HighLight();
						gotoxy(SecondX+10, FirstY+6); cout << "Du lieu da duoc luu lai";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+10, FirstY+6); cout << "                       ";	
						return 1;			
					}
					break;
				}
				case ESC: return 0;
				default: switch(vt)
				{
					case 1: //Vi tri con tro o phan loai
					{
						if(c == BACKSPACE)
						{
							if(mb.loaiMB.length() > 0)
							{
								gotoxy(SecondX+15 + mb.loaiMB.length()-1, FirstY+1 + vt); cout << " ";
								gotoxy(SecondX+15 + mb.loaiMB.length()-1, FirstY+1 + vt);
								mb.loaiMB = mb.loaiMB.substr(0, mb.loaiMB.length()-1);
							}	
						}
						else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 32) //Lay chu cai in thuong, in hoa vs khoang trang
						{
							mb.loaiMB +=c;
							cout << c;
						}
					} break;
					case 2: //Vi tri con tro o phan soCho
					{
						if(c == BACKSPACE)
						{
							if(soTam.length() > 0)
							{
								gotoxy(SecondX+15 + soTam.length()-1, FirstY+1 + vt); cout << " ";
								gotoxy(SecondX+15 + soTam.length()-1, FirstY+1 + vt);
								soTam = soTam.substr(0, soTam.length()-1);
							}	
						}
						else if(c >= 48 && c <= 57) //Chi lay so
						{
							soTam += c;
							cout << c;
						}
					} break;
				}
			}
		} while(1);
	}
}
int xuLiXoaMayBay (DanhSachMB &danhSachMB, int viTri, int trangSo){
	Normal();
	veHop(SecondX+10, FirstY+6, 30, 5, 15, 1, "Ban co chac chan muon xoa ?");
	gotoxy(SecondX+20, FirstY+9);
	cout << " Yes ";
	gotoxy(SecondX+25, FirstY+9);
	HighLight();
	cout << " No ";
	int vt=1;
	char c;
	do{
		c=GetKey();
		switch(c){
			case LEFT:{
				if (vt+1>1){
					vt--;
					gotoxy(SecondX+25, FirstY+9);
					Normal();
					cout << " No ";
					gotoxy(SecondX+20, FirstY+9);
					HighLight();
					cout << " Yes ";
				}
				break;
			}
			case RIGHT:{
				if (vt+1<2){
					vt++;
					gotoxy(SecondX+20, FirstY+9);
					Normal();
					cout << " Yes ";
					gotoxy(SecondX+25, FirstY+9);
					HighLight();
					cout << " No ";
				}
				break;
			}
			case ENTER: {
				if (vt==1){
					xoabang(SecondX+10, FirstY+6, 7, 35);
					return 0;
				}else if (vt==0){
					xoabang(SecondX+10, FirstY+6, 7, 35);
					Delete_item (danhSachMB, viTri+trangSo*15);
					return 1;
				}
				break;
			}
		}
	}while (1);
}
int menuMayBay (DanhSachMB &danhSachMB, PTRCB First){
	in_huong_dan(1, 0); 
	in_huong_dan(2, 1); 
	in_huong_dan(3, 2);
	in_huong_dan(4, 5);
	in_huong_dan(5, 3); 
	in_huong_dan(6, 6);
	int chon=0, trangSo=0, check=0, tonTai=0;			
	int maxPage = danhSachMB.n/15;
	if (danhSachMB.n%15 != 0)
		maxPage++;
	
	gotoxy(FourX+7, FirstY+21);
	cout << trangSo+1;
	gotoxy(FourX+12, FirstY+21);
	cout << maxPage;
	char kytu;
	gotoxy(SecondX+1, FirstY+chon);
	xuLy1Dong (danhSachMB, chon, trangSo, 1);
	do{
		kytu = GetKey();
		switch (kytu){
			case UP: if (chon+1>1){
              		//gotoxy(SecondX+1,FirstY+chon);
              		xuLy1Dong (danhSachMB, chon, trangSo, 0);
              		chon --;
              		
              		xuLy1Dong (danhSachMB, chon, trangSo, 1);
				}
				break;
			case DOWN: if (chon+1 <maxRow){
              		//gotoxy(SecondX+1,FirstY+chon);
              		xuLy1Dong (danhSachMB, chon, trangSo, 0);
              		chon ++;
              	
              		//gotoxy(SecondX+1,FirstY+chon);
              		if (xuLy1Dong (danhSachMB, chon, trangSo, 1)==0){
              			chon--;
              			gotoxy(SecondX+1,FirstY+chon);
              			xuLy1Dong (danhSachMB, chon, trangSo, 1);
					}
  			  	}
  			  	break;
  			case LEFT: if (trangSo+1>1){
  					resetMenuMayBay(SecondX+50,FirstY);
  					trangSo--;
  					chon=0;
  					duLieuMayBay(danhSachMB, SecondX+50, FirstY, trangSo, maxPage);
					xuLy1Dong (danhSachMB, chon, trangSo, 1);
  				}
  				break;
  			case RIGHT: if (trangSo+1<maxPage){
  					resetMenuMayBay(SecondX+ 50,FirstY);
  					trangSo++;
  					chon=0;
  					duLieuMayBay(danhSachMB, SecondX+50, FirstY, trangSo, maxPage);
  					xuLy1Dong (danhSachMB, chon, trangSo, 1);
  				}
  				break;
  		//	case 8: duLieuMayBay(danhSachMB, SecondX+50, FirstY, trangSo, maxPage);
  			case DEL: {
  				tonTai = timMayBayTrongChuyenBay(First, danhSachMB.nodes[chon+trangSo*15]->soHieuMB);
  				if (tonTai == 1){
  					gotoxy(SecondX+10, FirstY+6);
  					HighLight();
  					cout << " Khong the xoa may bay nay ";
  					Sleep(2000);
  					gotoxy(SecondX+10, FirstY+6);
  					Normal();
  					cout << "                           ";
				}else if (tonTai == 0){
					check = xuLiXoaMayBay(danhSachMB, chon, trangSo);
					if (check == 0)	break;
					else if (check == 1){
						gotoxy(SecondX+10, FirstY+6);
	  					HighLight();
	  					cout << " Da xoa thanh cong ";
	  					Sleep(2000);
	  					gotoxy(SecondX+10, FirstY+6);
	  					Normal();
	  					cout << "                   ";
	  					return 0;
					}
				}
				break;
			  }
  			case InSert:{
					veThemMayBay(); 
					do{
						check = xuLiNhapMayBay(danhSachMB);
						if (check == 0){
							xoabang(SecondX, FirstY, 6, 50);
							return 0;
						}else if (check == 1){
							resetBangThem();
							maxPage = danhSachMB.n/15;
							if (danhSachMB.n%15 != 0)
								maxPage++;
							resetMenuMayBay(SecondX+50, FirstY);
	  						duLieuMayBay(danhSachMB, SecondX+50, FirstY, maxPage-1, maxPage);
						} 
					}while(1);
			  	}
			  	break;
			// Xu ly chinh sua;
  			case Enter: {
					veThemMayBay(); 
					check = xuLiChinhSuaMayBay(danhSachMB, chon, trangSo, First);
					if (check == 0){
						xoabang(SecondX, FirstY, 6, 50);
					}else if(check ==1){
						xoabang(SecondX, FirstY, 6, 50);
						Normal();
						gotoxy(SecondX+50+1, FirstY+3+chon);
						cout << setw(15) << setfill(char(32))<< " "; 
						gotoxy(SecondX+50+18, FirstY+3+chon);
						cout << setw(40) << setfill(char(32))<< " "; 
						gotoxy(SecondX+50+60, FirstY+3+chon);
						cout << setw(4) << setfill(char(32))<< " "; 
						xuLy1Dong (danhSachMB, chon, trangSo, 1);
					}
					
					break;
			  	}
  			case ESC: {
  				xoabang(SecondX, FirstY, 25, 90); 
				return -1;
			  }
		}
	}while (1);
}
//========================CHUYEN BAY ======================================================================= 
void veMenuChuyenBay (){
	veHop(SecondX, FirstY, 34, 15, 15, 1, "Chuyen bay");
	veHop(SecondX+35, FirstY, 7, 20, 15, 1, "Ma CB"); 
	veHop(SecondX+7+35, FirstY, 17, 20, 15, 1, "San bay den");
	veHop(SecondX+24+35, FirstY, 10, 20, 15, 1, "Gio");
	veHop(SecondX+24+10+35, FirstY, 13, 20, 15, 1, "Ngay");
	veHop(SecondX+44+35+3, FirstY, 15, 20, 15, 1, "Trang thai");
	veHop(SecondX+59+35+3, FirstY, 17, 20, 15, 1, "So hieu may bay");
	veHop(SecondX+35, FirstY+20+2, 59+17, 4 , 15, 1, "Thong bao"); 
	gotoxy(ThirdX-15+30, FirstY+21);
	cout << "Trang:   /   " ;
}  
void xoaTrang_CB (int x, int y) { // xoa trang chuyen bay, chi xoa noi dung khong xoa bang 
	Normal();
	for(int i = 0; i < maxRow; i++){
		gotoxy (x, y+i); // ma so cb 
		cout << setw(7-1) << setfill(char(32)) << " ";
		gotoxy(x+7, y+i); // san bay 
      	cout << setw(17-1) << setfill(char(32)) << " ";
      	gotoxy(x+24, y+i); // gio 
  	 	cout << setw(10-1) << setfill(char(32)) << " ";
  	 	gotoxy(x+24+10, y+i); // gio 
  	 	cout << setw(11) << setfill(char(32)) << " ";
  	 	gotoxy(x+44+3, y+i); 
  	 	cout << setw(15-1) << setfill(char(32)) << " ";
		gotoxy(x+59+3, y+i);
		cout << setw(17-1) << setfill(char(32)) << " "; 
	}
}
int xuLy1Dong_CB (PTRCB First, int viTri, int trangSo, int coMau){ // khop voi  veMenuChuyenBay (){
	if (viTri+trangSo*15 == Dem_ChuyenBay(First))
		return 0;
	if (coMau == 1)
		HighLight();
	else Normal();
	PTRCB p = nodepointer(First, viTri+trangSo*15+1);
	gotoxy(SecondX+1+35, FirstY+3+viTri); 
    cout<< " "<<p->data.maCB<<" ";
   	gotoxy(SecondX+7+1+35, FirstY+3+viTri);
 	cout<< " "<<p->data.sanBayDen<<" ";
 	gotoxy(SecondX+24+1+35, FirstY+3+viTri);
	cout<<" "<< p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" ";
	gotoxy(SecondX+31+1+35+3, FirstY+3+viTri);
	cout<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam; 
   	gotoxy(SecondX+44+1+35+3, FirstY+3+viTri);
	//cout<< " "<<p->data.trangThai<<" ";
	if (p->data.trangThai == 0) cout<<" Huy chuyen ";
	if (p->data.trangThai == 1) cout<<" Con ve ";
	if (p->data.trangThai == 2) cout<<" Het ve ";
	if (p->data.trangThai == 3) cout<<" Hoan tat "; 
	gotoxy(SecondX+59+1+35+3, FirstY+3+viTri);
 	cout<< " "<<p->data.soHieuMB<<" ";
}
int xuLy1Dong_CB_SHMB (DanhSachMB &danhSachMB, int viTri, int trangSo, int coMau){ // khop de xu ly nhap so hieu may bay 
	if (viTri+trangSo*15 == danhSachMB.n)
		return 0;
	if (coMau == 1)
		HighLight();
	else Normal();
	gotoxy(SecondX+1+35, FirstY+3+viTri);
	cout << " " << danhSachMB.nodes[viTri+trangSo*15]->soHieuMB<< " "; 
	gotoxy(SecondX+18+35, FirstY+3+viTri);
	cout << " " << danhSachMB.nodes[viTri+trangSo*15]->loaiMB<< " "; 
	gotoxy(SecondX+60+35, FirstY+3+viTri);
	cout << " " << danhSachMB.nodes[viTri+trangSo*15]->soCho<< " ";

}
string thong_bao_cb[] = {"Ngay khong hop le!!! Moi nhap lai",				//0
						 "Gio khong hop le!! Moi nhap lai	",				//1
						 "Ma chuyen bay da ton tai!! Moi nhap lai",			//2
						 "Khong duoc de trong!!Moi nhap",					//3
						 "Chuyen bay khong the cap nhat!! Moi chon lai",	//4
						 "Ban da dat ve o chuyen bay nay!!",				//5
						 "Khong co chuyen bay kha dung!!!",					//6
						 "Dat ve thanh cong.",								//7	
						 "May bay chua the su dung",						//8 
						 "Thong tin khong hop le! Moi nhap lai.",			//9 
						 "Huy ve thanh cong.",								//10 
						 "Chon chuyen bay de huy ve hoac ESC de thoat",		//11 
						 "Danh sach ve trong"		,						//12
						 "Ghe da duoc dat "									//13 
						 			
};
void in_thong_bao_cb(int tb) // tb la so thu tu cua thong bao
{
	Normal();
	gotoxy(x_thongBao, y_thongBao);
	cout << setw(60) << setfill(char(32)) << " ";
	HighLight();
	gotoxy(x_thongBao, y_thongBao);
	cout << thong_bao_cb[tb];
	Sleep(2000);
	Normal();
	gotoxy(x_thongBao, y_thongBao);
	cout << setw(60) << setfill(char(32)) << " "; 
		
}
void xoa_xac_nhan(int y)
{
	for(int i=0 ; i<8 ; i++)
	{
		gotoxy(SecondX, y+i);
		cout << setw(35) << setfill(char(32)) << " ";
	}
}
int xac_nhan(int y, string s1)
{
	Normal();
	show_cur(0);
	string s[2] = {"  Co   ", " Khong "};
	int x[2] = {45, 55}, chon = 0, k = s[0].length()+1;
//	gotoxy(SecondX, FirstY+y-2); cout << s1;
	gotoxy(SecondX, y-2); cout << s1;
	gotoxy(x[0]-1, y-1); cout << char(218) << setw(k) << setfill(char(196)) << char(191);
	gotoxy(x[1]-1, y-1); cout << char(218) << setw(k) << setfill(char(196)) << char(191);
	gotoxy(x[0]-1, y); cout << char(179) << s[0] << char(179);
	gotoxy(x[1]-1, y); cout << char(179) << s[1] << char(179);
	gotoxy(x[0]-1, y+1); cout << char(192) << setw(k) << setfill(char(196)) << char(217);
	gotoxy(x[1]-1, y+1); cout << char(192) << setw(k) << setfill(char(196)) << char(217);
	HighLight();
	gotoxy(x[chon], y); cout << s[chon];
	int key;
	while(true)
	{
		key = GetKey();
		if(key == 224) key = GetKey();
		switch(key)
		{
			case LEFT:
				if(chon == 0)
				{
					Normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon = 1;
					HighLight();
					gotoxy(x[chon], y); cout << s[chon];
					break;
				}
				if(chon+1 > 1)
				{
					Normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon--;
					HighLight();
					gotoxy(x[chon], y); cout << s[chon];
				}
				break;
			case RIGHT:
				if(chon == 1) 
				{
					Normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon = 0;
					HighLight();
					gotoxy(x[chon], y); cout << s[chon];
					break;
				}
				if(chon+1 < 2)
				{
					Normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon++;
					HighLight();
					gotoxy(x[chon], y); cout << s[chon];
				}
				break;
			case ENTER:
				Normal();
				return chon;
		}
	}
}
void  Input_idflight(string &result, int &main_temp)
{	
	int count = result.length();
	gotoxy(SecondX+1+td_chuyen_bay[0].length(), FirstY+3);
	show_cur(1);
	cout << result;
	while(true)
	{
		while(kbhit())
		{
			int key = GetKey();
			if((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == 95 || (key >= 48 && key <= 57))
			{
				if(count <= 15)
				{
					if(key >= 97 && key <= 122)	key -= 32;
					cout << char(key);
					result += char(key);
					count++;
				}
			}
			else if(key == 8 && !result.empty())
			{
				cout << "\b" << " " << "\b";
				result.erase(result.end()-1);
				count--;
			}
			else if(key == ENTER)
			{	if(result.empty())
					{
						in_thong_bao_cb(3);
								return;
					}
				else
				main_temp++;
				return;
			}
			else if(key == 224)
			{
				key = GetKey();
				if(key == DOWN) 
				{if(result.empty())
				{
						in_thong_bao_cb(3);
						return;
					
				}
				main_temp++;
				return;
				}
			}
			else if (key==ESC)
			{
				
				string s = "Thoat se khong luu chuyen bay";
				int x = xac_nhan(FirstY+22, s);
				if(x==0) {
				xoa_xac_nhan(FirstY+20);	
				main_temp=7;
				return;
				
				}
				else if(x==1){
					xoa_xac_nhan(FirstY+20);
					return;
					
				}
				
			
			}
		}
	}
}

void Input_place(string &result, int &main_temp)
{
	int count = result.length();
	bool isSpaced = false;
	gotoxy(SecondX+1+td_chuyen_bay[1].length(), FirstY+3+1);
	show_cur(1);
	while(true)
	{
		while(kbhit())
		{
			int key = GetKey();
			if((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == 95 || key == 32 )
			{
				if (!isSpaced && key == 32 &&result.at(result.length()-1)!= static_cast<char>(32) )
				{
					cout << (char)key;
					result += (char)key;
					
					isSpaced = true;
				}
				else if(key >= 97 && key <= 122)	{
					key -= 32;
					cout << char(key);
					result += char(key);
			
					isSpaced = false;
					}
				
			}
			else if(key == 8 && !result.empty())
			{	
				
				cout << "\b" << " " << "\b";
				result.erase(result.end()-1);
				isSpaced = false;
			}
			
				
			
			else if(key == ENTER)
			{	if(result.at(result.length()-1)== static_cast<char>(32))
					{
						result.erase(result.end()-1);
						main_temp++;
						return;
						}	
				else 
				main_temp++;
				return;
			}
			else if(key == 224)
			{
				key = GetKey();
				if(key == DOWN) main_temp++;
				else if(key == UP) main_temp--;
				return;
			}
			else if (key==27)
			{
				
				string s = "Thoat se khong luu chuyen bay";
				int x = xac_nhan(FirstY+19, s);
				if(x==0) {
				xoa_xac_nhan(FirstY+20);	
				main_temp=7;
				return;
				
				}
				else if(x==1){
					xoa_xac_nhan(FirstY+20);
					return;
				}
			}
		}
	}
}
void ValidateDate(int count, int &tam, int &main_temp, Date &result)
{
	while (true)
	{
		while (kbhit())
		{
			int key = GetKey();
			
				if (key >= 48 && key <= 57 && count <4){
					if(tam==1&&count==2) {
				
					gotoxy(SecondX+1+td_chuyen_bay[2].length(), FirstY+3+2);
					cout<<setw(2)<<setfill(char(32))<<" ";
					gotoxy(SecondX+1+td_chuyen_bay[2].length(), FirstY+3+2);
					result.ngay=0;
				}
				else if(tam==2&&count==2)
				{
					gotoxy(SecondX+1+td_chuyen_bay[3].length()+3+1, FirstY+3+2);
					cout<<setw(2)<<setfill(char(32))<<" ";
					gotoxy(SecondX+1+td_chuyen_bay[3].length()+3+1, FirstY+3+2);
				  	result.thang =0;
				}
				else if(tam==3&&count==0)
				{	
					gotoxy(SecondX+1+td_chuyen_bay[3].length()+3+3+1, FirstY+3+2);
					cout<<setw(4)<<setfill(char(32))<<" ";
					gotoxy(SecondX+1+td_chuyen_bay[3].length()+3+3+1, FirstY+3+2);
					result.nam=0;
				}
				int f = key - 48;
			
					cout << f;
					if(tam==1)result.ngay = result.ngay * 10 + (f);
					else if(tam==2)result.thang = result.thang * 10 + (f);
					else if(tam==3)result.nam = result.nam * 10 + (f);
					if(count==3&&tam<=2)
						{
							tam++;
							return;
							
						}
					count++;
				
			}
		
			
			else if (key == 13)
			{
				tam++;
				if(tam==4) main_temp++;

				return;

			}
			
			else if(key==75 && tam>1)
			{	tam--;
				return;
				
			}
			else if(key==77 && tam<3)
			{	tam++;
				return;
				
			}
			else if (key == 8 && count >2)
			{
				cout << "\b" << " " << "\b";
				
				if(tam==1) result.ngay /= 10;
				else if(tam==2) result.thang /=10;
				else if(tam==3) result.nam /=10;
				count--;
			}
			else if(key == 80)
				{	tam=4;
					main_temp++;
					return;
				}
				else if (key==27)
			{
				
				string s = "Thoat se khong luu chuyen bay";
				int x = xac_nhan(FirstY+22, s);
				if(x==0) {
				tam=4;
				main_temp = 7;
				xoa_xac_nhan(FirstY+20);	
				return;
				}
				else if(x==1){
					xoa_xac_nhan(FirstY+20);
					return;
					
				}
			}
			else if(key == 72)
				{	tam=4;
					main_temp--;
					return;
				}
			
		}

		}
}
Date Input_date(Date &n, int &main_temp) {	
Date v = NgayHienTai();
int temp1 = 1;
	while(true){
		switch(temp1)
		{
			case 1: {
				gotoxy(SecondX+1+td_chuyen_bay[2].length(), FirstY+3+2);
				show_cur(1);
				ValidateDate(2, temp1, main_temp, n);
				break;
			}
			case 2: {
				gotoxy(SecondX+1+td_chuyen_bay[2].length()+3+3, FirstY+3+2);
				show_cur(1);
				ValidateDate(2, temp1, main_temp, n);
				break;
			}
			case 3: {
				gotoxy(SecondX+1+td_chuyen_bay[2].length()+3+3+3, FirstY+3+2);
				show_cur(1);
				ValidateDate(0, temp1, main_temp, n);
				break;
			}
			default: {
				
				if (!NgayHopLe(n)&&main_temp==4)
				{
					in_thong_bao_cb(0);
					gotoxy(SecondX+1+td_chuyen_bay[2].length(), FirstY+3+2);
					cout << setw(20) << setfill(char(32)) << " ";
					gotoxy(SecondX+1+td_chuyen_bay[2].length(), FirstY+3+2);
					cout<<"  /  /";
					temp1=1;
					main_temp--;
				}
				if(!SoSanhNgay(n, v))
				{
					in_thong_bao_cb(0);
					gotoxy(SecondX+1+td_chuyen_bay[2].length(), FirstY+3+2);
					cout << setw(20) << setfill(char(32)) << " ";
					gotoxy(SecondX+1+td_chuyen_bay[2].length(), FirstY+3+2);
					cout<<"  /  /";
					temp1=1;
					main_temp--;
					
				}
				else	
				return n;
				break;
				}
		}	
	}	
}
void ValidateHour(int count, int &tam, int &main_temp, Hour &result)
{
	while (true)
	{
		while (kbhit())
		{
			int key = GetKey();
			if (key >= 48 && key <= 57 && count <4)
			{	if(tam==1&&count==2) 
					{	//gotoxy(X_BOX+td_chuyen_bay[4].length()+3, Y_BOX+9);
						//lay gio 
						gotoxy(SecondX+1+td_chuyen_bay[3].length(), FirstY+3+3);
						cout<<setw(2)<<setfill(char(32))<<" ";
						gotoxy(SecondX+1+td_chuyen_bay[3].length(), FirstY+3+3);
						result.gio=0;
					}
				else if (tam==2&&count==2) 
					{	//gotoxy(X_BOX+td_chuyen_bay[4].length()+3+3, Y_BOX+9);
						// lay phut 
						gotoxy(SecondX+1+td_chuyen_bay[3].length()+3, FirstY+3+3);
						cout<<setw(2)<<setfill(char(32))<<" ";
						gotoxy(SecondX+1+td_chuyen_bay[3].length()+3, FirstY+3+3);
						result.phut=0;
					}
					int f = key-48;
					cout << f;
					if(tam==1) result.gio = result.gio * 10 + (f);
					else if(tam==2) result.phut = result.phut*10 +(f);
					if(count==3&&tam<2)
					{
						tam++;
						return;
						
					}
					count++;
				
			}
			
			else if (key == 13)
			{
				tam++;
				if(tam==3) main_temp++;

				return;

			}
			
			else if(key==75 && tam>1)
			{	tam--;
				return;
				
			}
			else if(key==77 && tam<2)
			{	tam++;
				return;
				
			}
			else if (key == 8 && count >2)
			{
				cout << "\b" << " " << "\b";
				if(tam==1) result.gio /= 10;
				else if(tam==2) result.phut /= 10;
				count--;
			}
			else if(key == 80)
				{	tam=3;
					main_temp++;
					return;
				}
			else if(key == 72)
				{	tam=3;
					main_temp--;
					return;
				}
			else if (key==27)
			{
				string s = "Thoat se khong luu chuyen bay";
				int x = xac_nhan(FirstY+22, s);
				if(x==0) {
				tam = 4; 
				xoa_xac_nhan(FirstY+20);	
				main_temp=7;
				return;
				
				}
				else if(x==1){
					xoa_xac_nhan(FirstY+20);
					return;
					
				}
			}	
		}
	}
}
Hour Input_time(Hour &n, int &main_temp)
{	//Hour v= GioHienTai();
	int temp1 = 1;
	while(true){
		switch(temp1)
		{
			case 1: {
				gotoxy(SecondX+1+td_chuyen_bay[3].length(), FirstY+3+3);		
				show_cur(1);
				ValidateHour(2, temp1, main_temp, n);
				break;
			}
			case 2: {
				gotoxy(SecondX+1+td_chuyen_bay[3].length()+3, FirstY+3+3);
				show_cur(1);
				ValidateHour(2, temp1, main_temp,n);
				break;
			}
		
			default: {
				
				if (!GioHopLe(n)&&main_temp==5)
				{	
					in_thong_bao_cb(1);
					gotoxy(SecondX+1+td_chuyen_bay[3].length(), FirstY+3+3);
					cout << setw(10) << setfill(char(32)) << " ";
					gotoxy(SecondX+1+td_chuyen_bay[3].length(), FirstY+3+3);
					cout<<"  :";
					temp1=1;
					main_temp--;
				}
				else 
				return n;
				break;	
			};
		}
}
}
//Chon so hieu may bay
int nhap_SHMB (string &n,DanhSachMB &danhSachMB)
{ 
	int chon=0, trangSo=0; 								int check=0;			
	int maxPage = danhSachMB.n/15;
	if (danhSachMB.n%15 != 0)
		maxPage++;
	
	gotoxy(ThirdX-8+35, FirstY+21);
	cout << trangSo+1;
	gotoxy(ThirdX-3+35, FirstY+21);
	cout << maxPage;
	char kytu;
	gotoxy(SecondX+1+35, FirstY+chon);
	xuLy1Dong_CB_SHMB (danhSachMB, chon, trangSo, 1);
	do{
		kytu = GetKey();
		switch (kytu){
			case UP: if (chon+1>1){
              		xuLy1Dong_CB_SHMB (danhSachMB, chon, trangSo, 0);
              		chon --;
              		xuLy1Dong_CB_SHMB (danhSachMB, chon, trangSo, 1);
				}
				break;
			case DOWN: if (chon+1 <maxRow){
              		xuLy1Dong_CB_SHMB (danhSachMB, chon, trangSo, 0);
              		chon ++;
              		if (xuLy1Dong_CB_SHMB (danhSachMB, chon, trangSo, 1)==0){
              			chon--;
              			gotoxy(SecondX+1+35,FirstY+chon);
              			xuLy1Dong_CB_SHMB (danhSachMB, chon, trangSo, 1);
					}
  			  	}
  			  	break;
  			case LEFT: if (trangSo+1>1){
  					xoaTrang(SecondX+35, FirstY);
  					trangSo--;
  					chon=0;
  					duLieuMayBay(danhSachMB, SecondX+35, FirstY, trangSo, maxPage);
					xuLy1Dong_CB_SHMB (danhSachMB, chon, trangSo, 1);
  				}
  				break;
  			case RIGHT: if (trangSo+1<maxPage){
  					xoaTrang(SecondX+35, FirstY);
  					trangSo++;
  					chon=0;
  					duLieuMayBay(danhSachMB, SecondX+35, FirstY, trangSo, maxPage);
  					xuLy1Dong_CB_SHMB (danhSachMB, chon, trangSo, 1);
  				}
  				break;
  			case ENTER: {
  					Normal();
  					for(int i=0 ; i<22 ; i++)
					{
					gotoxy(x_chuyenBay-1, y_chuyenBay-3+i);
					cout << setw(85) << setfill(char(32)) << " ";
					}
  					return chon+trangSo*15; 
			  } 
  			case 8: xoaTrang(SecondX+35, FirstY); break;
  			case ESC : return -1;
		}
		if (check ==1)
			break;
	}while (1);
}
bool check_SoHieuMB (PTRCB First, PTRCB temp)
{
		PTRCB p;
	for (p = First; p!=NULL; p=p->next)
	{
		if ((temp->data.soHieuMB).compare(p->data.soHieuMB) == 0 )
		{
		if (temp->data.thoiGian.date.nam == p->data.thoiGian.date.nam && 
			temp->data.thoiGian.date.thang == p->data.thoiGian.date.thang &&
			temp->data.thoiGian.date.ngay == p->data.thoiGian.date.thang &&
			temp->data.thoiGian.h.gio == p->data.thoiGian.h.gio &&
			temp->data.thoiGian.h.phut == p->data.thoiGian.h.phut ) 
			{ 
				return false;
			}
		}
	}
	return true; 
 } 
void Choose_idplane(string &n,int &soChoMax, int &main_temp,DanhSachMB &ds)
{	try_again:
	show_cur(0);
	int maxPage = ds.n/15;
	if (ds.n%15 != 0)
		maxPage++;
//	if(!n.empty())
//	{	show_cur(1);
//		gotoxy(SecondX+1+td_chuyen_bay[5].length(), FirstY+3+4);
//		cout<<n;
//	}
//	else{
	do{
	
	gotoxy(SecondX+1+td_chuyen_bay[5].length(), FirstY+3+4);
	cout<<"Nhan Enter de chon";
	Sleep(300);
	gotoxy(SecondX+1+td_chuyen_bay[5].length(), FirstY+3+4);
	cout<<setw(20)<<setfill(char(32))<<" ";
	Sleep(300);
	
	}while(!kbhit());
//	}

	while(true)
	{	
		while(kbhit())
		{	
			int key = GetKey();;
			 if(key==UP) {main_temp--;
			return; 
			}
			else if(key==DOWN) {
			if(n.empty())
			{
				in_thong_bao_cb(3);
						return;
				}
			
			main_temp++;
			
			return;
			}
			else if (key==ESC)
			{
				
				string s = "Thoat se khong luu chuyen bay";
				int x = xac_nhan(FirstY+22, s);
				if(x==0) {
				xoa_xac_nhan(FirstY+20);	
				main_temp=7;
				return;
				
				}
				else if(x==1){
					xoa_xac_nhan(FirstY+20);
					return;
					
				}
				
			
			}
			else if(key==ENTER)
			{	
				int thoat; 
				xoaTrang(x_chuyenBay-1, y_chuyenBay-3);
				for(int i=0 ; i<22 ; i++)
				{
					gotoxy(x_chuyenBay-1, y_chuyenBay-3+i);
					cout << setw(85) << setfill(char(32)) << " ";
				}
				veHop(SecondX+35, FirstY, 17, 20, 15, 1, "So hieu may bay" ); 
				veHop(SecondX+17+35, FirstY, 42, 20, 15, 1, "               Loai may bay               ");
				veHop(SecondX+59+35, FirstY, 8, 20, 15, 1, "So cho");
				gotoxy(FourX, FirstY+21);
				cout << "Trang:    /   " ;
				do{
					duLieuMayBay(ds, SecondX+35, FirstY, 0, maxPage);
					thoat = nhap_SHMB ( n, ds);
					if (thoat == -1)
					{
						return;	
					}
					else {
						n = ds.nodes[thoat]->soHieuMB;
						soChoMax = ds.nodes[thoat]->soCho; 
						Normal();
						gotoxy(SecondX+1+td_chuyen_bay[5].length(), FirstY+3+4);
						cout<<n;
						main_temp++;	
						return;
					}
				}while (1);	
				return;		
			}
			}
	}
	
	
	return;	
}

void duLieuChuyenBay (PTRCB First, int x, int y, int trangSo){
	PTRCB p;
	p=First;
	gotoxy(ThirdX-15+37, FirstY+21);
	cout << trangSo+1;
   	if(p == NULL)
    printf("\n   (Khong co chuyen bay nao trong danh sach)");
	int j=0;
	for(int i = 0+trangSo*maxRow; i < maxRow+trangSo*maxRow; i++){ 
		p = nodepointer(First, i+1);
		if (j==maxRow)
			j=0;
		if  (p==NULL)
			break; 
       	gotoxy(x, y+j);
      	cout<< " "<<p->data.maCB<<" ";
      	gotoxy(x+7, y+j);
  	 	cout<< " "<<p->data.sanBayDen<<" ";
  	 	gotoxy(x+24, y+j);
		cout<< " "<<p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" ";
		gotoxy(x+24+10, y+j);
		cout<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam; 
   		gotoxy(x+44+3, y+j);
   		if (p->data.trangThai == 0) cout<<" Huy chuyen ";
		if (p->data.trangThai == 1) cout<<" Con ve ";
		if (p->data.trangThai == 2) cout<<" Het ve ";
		if (p->data.trangThai == 3) cout<<" Hoan tat "; 
		gotoxy(x+59+3, y+j);
	 	cout<< " "<<p->data.soHieuMB<<" ";
       	p = p->next;
       	j++;
	}
}

void nhap_cb (PTRCB &First, DanhSachMB &ds){
	xoabang(SecondX+1, FirstY+3, 12,32); 
	Normal();
	gotoxy (SecondX+1, FirstY+3);
	cout<< td_chuyen_bay[0];
	gotoxy (SecondX+1, FirstY+4);
	cout<< td_chuyen_bay[1];
	gotoxy (SecondX+1, FirstY+5);
	cout<< td_chuyen_bay[2];
	gotoxy (SecondX+1, FirstY+6);
	cout<< td_chuyen_bay[3];
	gotoxy (SecondX+1, FirstY+7);
	cout<< td_chuyen_bay[5];
	for(int i=0 ; i<5 ; i++)
	{	
	if(i==2){
		gotoxy(SecondX+1+8, FirstY+3+i); cout<<"/  /";
		}
	else if(i==3){
		gotoxy(SecondX+1+7, FirstY+3+i); cout<<":";	
		}
	}
	string str; 
	PTRCB temp =  new nodeCB;
	int n,vt=0, check =0;					
	char c;
	gotoxy(SecondX+1+td_chuyen_bay[0].length(), FirstY+3);
	int f=1, t = 1; // temp la bien tam de nhan UP DOWN
	try_again: // tao diem goto
	while(true)
	{
		f = t;
		switch(f)
		{
			case 1:
				{
				 Input_idflight(str, t);
				 if (CheckChuyenBay(First, str) == true)
				 {
				 	in_thong_bao_cb(2); 
				 	gotoxy(SecondX+1+td_chuyen_bay[0].length(), FirstY+3);
					cout << setw(10) << setfill(char(32)) << " ";
					str = "";
					t--;
				  } 
				  else {
					temp->data.maCB = str;
				  }
				break;
				}
			case 2:
				{
					fflush(stdin);
					Input_place(temp->data.sanBayDen, t);
					break;
				}
			case 3: 
				{
					Input_date(temp->data.thoiGian.date, t);
				break;
				}
			case 4:
				{ 
					Input_time(temp->data.thoiGian.h, t);
				break;
				}
			case 5:
				{
					 Choose_idplane(temp->data.soHieuMB, temp->data.ve.SoVeMax, t, ds);
				break;
				}
			case 6: 
				{
					if (check_SoHieuMB(First, temp)==false)
					{
						gotoxy(SecondX+1+td_chuyen_bay[5].length(), FirstY+3+4);
						cout << setw(10) << setfill(char(32)) << "  ";
						in_thong_bao_cb(8);
						temp->data.soHieuMB = ""; 
						t = 5;
						break; 
					 } 
					 else {
					string s = "Xac nhan lap chuyen bay moi";
					int x = xac_nhan(FirstY+22, s);
					if(x==0)
					{
						temp->data.trangThai = 1;
						temp->data.ve.danhSach = new Ve[temp->data.ve.SoVeMax]; 
						temp->data.ve.SoVeDaDat = 0;
						for (int i = 0; i<temp->data.ve.SoVeMax; i++) {
							temp->data.ve.danhSach[i].cmnd = "";
						}
						Insert_First(First, temp);
						xoa_xac_nhan(FirstY+20);
						return;
					}
					else if(x==1)
					{
						
						t = 5;
						xoa_xac_nhan(FirstY+20);
						break;
					}
					}
					
				}	
			case 7:
				{
					xoabang(SecondX+1, FirstY+3, 12,32); 
					xoa_xac_nhan(FirstY+20);
					return;	
				}
		}
	}
}

void xuat_1CB (PTRCB First, int viTri, int trangSo, int coMau)
{
	PTRCB p = nodepointer(First, viTri+trangSo*15+1);
	Normal();
	gotoxy (SecondX+1, FirstY+3);
	cout<< td_chuyen_bay[0]<<p->data.maCB;
	gotoxy (SecondX+1, FirstY+4);
	cout<< td_chuyen_bay[1]<<p->data.sanBayDen;
	gotoxy (SecondX+1, FirstY+5);
	cout<< td_chuyen_bay[2]<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam;
	gotoxy (SecondX+1, FirstY+6);
	cout<< td_chuyen_bay[3]<<p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut;
	gotoxy (SecondX+1, FirstY+7);
	cout<< td_chuyen_bay[4]<<p->data.trangThai;
	gotoxy (SecondX+1, FirstY+8);
	cout<< td_chuyen_bay[5]<<p->data.soHieuMB;
}
void hieu_chinh_ThoiGian_CB(PTRCB &First, int chon, int trangSo)
{
	xuat_1CB(First, chon, trangSo, 0); 
	PTRCB p = nodepointer(First, chon+trangSo*15+1); 	
	Normal();
	gotoxy (SecondX+1+td_chuyen_bay[2].length(), FirstY+5);
	show_cur(1);
	int n,vt=0, check =0;					
	char c;
	Date n_date; 	
	Hour n_hour; 
	int f=1, t = 3; // temp la bien tam de nhan UP DOWN
	try_again: // tao diem goto
	while(true)
	{
		f = t;
		switch(f)
		{
			case 3: 
				{
					Input_date(n_date, t);
				break;
				}
			case 4:
				{
					Input_time(n_hour, t);
				break;
				}
			case 5:
				{
					string s = "Xac nhan hieu chinh thoi gian";
					int x = xac_nhan(FirstY+22, s);
					if(x==0)
					{ 
						show_cur(0); 
						p->data.thoiGian.date = n_date;
						p->data.thoiGian.h = n_hour; 
						xoa_xac_nhan(FirstY+17);
						return;
					}
					else if(x==1)
					{
						
						t = 3;
						xoa_xac_nhan(FirstY+17);
						break;
					}
				break;
				}
			case 7:
				{
					xoabang(SecondX+1, FirstY+3, 12,32); 
					xoa_xac_nhan(FirstY+17);
					return;	
				}
		}
	}
} 
void huy_chuyenBay (PTRCB &First, int chon, int trangSo) {
	show_cur(0); 
	Normal();
	PTRCB p = nodepointer(First, chon+trangSo*15+1);
	if (p->data.trangThai == 1 || p->data.trangThai == 2) {
		p->data.trangThai = 0; // set trang thai huy chuyen = 0
	} else if (p->data.trangThai == 0 || p->data.trangThai == 3)
	{
		in_thong_bao_cb(4);
		return;
	}
	string s = "Xac nhan huy chuyen";
	int x = xac_nhan(FirstY+22, s);
	if(x==0)
	{ 
		show_cur(0); 
		p->data.ve.SoVeDaDat = p->data.ve.SoVeDaDat -1;
		for (int i = 0; i < p->data.ve.SoVeMax; i++ ) {
			p->data.ve.danhSach[i].cmnd = "";
		}
		xoa_xac_nhan(FirstY+17);
		xoaTrang_CB(x_chuyenBay, y_chuyenBay);
		veMenuChuyenBay();
		duLieuChuyenBay(First, x_chuyenBay, y_chuyenBay, trangSo) ;
		xuLy1Dong_CB(First, chon, trangSo, 1);
		return;
	}else if(x==1)	{			
		xoa_xac_nhan(FirstY+17);
		return;
	}
	
} 
int QuanLyChuyenBay (PTRCB &First,DanhSachMB &ds ){
	in_huong_dan(1, 0);
	in_huong_dan(2, 1);
	in_huong_dan(3, 2);
	in_huong_dan(4, 8);
	in_huong_dan(5, 5);
	in_huong_dan(6, 7);
	veMenuChuyenBay();
	duLieuChuyenBay(First, x_chuyenBay, y_chuyenBay, 0) ;
	int chon=0, trangSo=0;  
	int check=0;
	int temp = Dem_ChuyenBay(First); 			
	int maxPage = temp/15;
	if (temp%15 != 0)
		maxPage++; 
	gotoxy(ThirdX-15+37, FirstY+21);
	cout << trangSo+1;
	gotoxy(ThirdX-15+41, FirstY+21);
	cout << maxPage;
	char kytu;
	gotoxy(SecondX+1, FirstY+chon);
	xuLy1Dong_CB(First, chon, trangSo, 1); 
	do{
		kytu = GetKey();
		switch (kytu){
			case UP: if (chon+1>1){
              		xuLy1Dong_CB(First, chon, trangSo, 0);
              		chon --;
              		xuLy1Dong_CB(First, chon, trangSo, 1);
				}
				break;
			case DOWN: if (chon+1 <maxRow){
              		xuLy1Dong_CB(First, chon, trangSo, 0);
              		chon ++;
              		if (xuLy1Dong_CB(First, chon, trangSo, 1)==0){
              			chon--;
              			gotoxy(SecondX+1,FirstY+chon);
              			xuLy1Dong_CB(First, chon, trangSo, 1);
					}
  			  	}
  			  	break;
  			case LEFT: if (trangSo+1>1){
  					xoaTrang_CB(x_chuyenBay, y_chuyenBay);
  					trangSo--;
  					chon=0;
  					duLieuChuyenBay(First, x_chuyenBay, y_chuyenBay, trangSo);
					xuLy1Dong_CB(First, chon, trangSo, 1);
  				}
  				break;
  			case RIGHT: if (trangSo+1<maxPage){
  					xoaTrang_CB(x_chuyenBay, y_chuyenBay);
  					trangSo++;
  					chon=0;
  					duLieuChuyenBay(First, x_chuyenBay, y_chuyenBay, trangSo);
  					xuLy1Dong_CB(First, chon, trangSo, 1);
  				}
  				break;
  			case InSert:{ 
					nhap_cb(First, ds);
					xoaTrang_CB(x_chuyenBay, y_chuyenBay); 
					veMenuChuyenBay();
					duLieuChuyenBay(First, x_chuyenBay, y_chuyenBay, 0);
					xuLy1Dong_CB(First, chon, trangSo, 1);
					xoabang(SecondX+1, FirstY+3,12,32);	
			  	}break;
			case F2: {	// hieu chinh thoi gian
					hieu_chinh_ThoiGian_CB(First, chon, trangSo);
					xoaTrang_CB(x_chuyenBay, y_chuyenBay);
					veMenuChuyenBay();
					duLieuChuyenBay(First, x_chuyenBay, y_chuyenBay, 0) ;
					xuLy1Dong_CB(First, chon, trangSo, 1);
					xoabang(SecondX+1, FirstY+3,12,32);	
					break;
			}
			case DEL: {
					huy_chuyenBay (First, chon, trangSo); 
				
					break;
			} 
			case ENTER: {
				xoabang(SecondX+1, FirstY+3,12,32);
              	xuat_1CB(First, chon, trangSo, 0);
              	break;
            }
  			case ESC : 
			  {
			  	
			  	xoa_huong_dan();
			  	xoabang(SecondX, FirstY,29,120);
			  	return -1;
			  }
		}
		if (check ==1)
			break;
	}while (1);
}
//===========Cap nhat trang thai chuyen bay========
bool ChuyenBayDaHoanTat (PTRCB p) {
	Date d_ht = NgayHienTai();
	Hour h_ht = GioHienTai();
	if (p->data.thoiGian.date.nam < d_ht.nam) return true;
	else if (p->data.thoiGian.date.nam > d_ht.nam) return false;
	else if (p->data.thoiGian.date.nam == d_ht.nam) {
		if (p->data.thoiGian.date.thang < d_ht.thang) return true;
		else if (p->data.thoiGian.date.thang > d_ht.thang) return false;
		else if (p->data.thoiGian.date.thang == d_ht.thang) {
			if (p->data.thoiGian.date.ngay < d_ht.ngay) return true;
			else if (p->data.thoiGian.date.ngay > d_ht.ngay) return false;
			else if (p->data.thoiGian.date.ngay > d_ht.ngay) {
				if (!SoSanhGio(p->data.thoiGian.h, h_ht)) return true;
				else if  (SoSanhGio(p->data.thoiGian.h, h_ht)) return false;
				else return false; 
			}
		}
	}
} 
void CapNhatTrangThaiChuyenBay (PTRCB &First) {
	for (PTRCB p = First; p!=NULL; p=p->next) {
		if (p->data.trangThai == 1 && ChuyenBayDaHoanTat(p)){
			p->data.trangThai = 3; // da hoan tat 
		} else if (p->data.trangThai == 2 && ChuyenBayDaHoanTat(p) ) {
			p->data.trangThai = 3; // da hoan tat 
		} else if (p->data.trangThai == 3 && ChuyenBayDaHoanTat(p)!= true ) 		{
			p->data.trangThai = 1;
		} else if (p->data.trangThai == 1 && p->data.ve.SoVeDaDat == p->data.ve.SoVeMax)   {
			p->data.trangThai = 2; //het ve 
		} else if (p->data.trangThai == 2 && p->data.ve.SoVeDaDat != p->data.ve.SoVeMax)   {
			p->data.trangThai = 1; // tu het ve chuyen sang con ve
		} else if (p->data.trangThai == 0 && p->data.ve.SoVeDaDat != 0)			{
			 p->data.trangThai = 1;
		}		 
		 
		// co the them nhieu nua, nao them thi chinh 
	} 
} 
//===========DAT VE, HUY VE ====================================================================================================================
void taoDSCBMoi (PTRCB First, PTRCB &n_First) {
				PTRCB Last ; 
				PTRCB temp;  
				for (PTRCB p = First; p!=NULL; p=p->next)
				{
					if (p->data.trangThai == 1)
					{
						temp = new nodeCB();
						temp->data = p->data;
						if (n_First==NULL)		 
							n_First=temp;
						else {
							Last->next = temp;
						}
						Last=temp;
						temp->next = NULL;
					}
				}
}
bool check_DSVe_CMND (PTRCB p, string cmnd) {
	if (p->data.ve.SoVeDaDat == 0)
	{
		return false; 
	 } else {
	for (int i=0; i<p->data.ve.SoVeMax;i++) {
		 if (p->data.ve.danhSach[i].cmnd == cmnd)		 	return true; 
		}
	}
	return false; 
} 
int laySoVe_CMND (PTRCB p, string cmnd) {
	for (int i=0; i<p->data.ve.SoVeMax; i++) {
		if (p->data.ve.danhSach[i].cmnd == cmnd ) return i;
	}
	return -1;
} 
void xuat_1Ve (PTRCB First, int viTri, int trangSo, int coMau, int sl, int a[], string cmnd) {
	if (a[viTri+trangSo*15] == -1) {
		gotoxy (SecondX+1, FirstY+12);
		cout<<"Khach da huy ve"; 
	} else {
	PTRCB p = nodepointer(First, a[viTri+trangSo*15]);
	Normal();
	int soVe = laySoVe_CMND(p, cmnd);
	gotoxy (SecondX+1, FirstY+16);
	cout<< td_ve[0]<<p->data.maCB;
	gotoxy (SecondX+1, FirstY+17);
	cout<< td_ve[1]<<p->data.sanBayDen;
	gotoxy (SecondX+1, FirstY+18);
	cout<< td_ve[2]<<p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut;
	gotoxy (SecondX+1, FirstY+19);
	cout<< td_ve[3]<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam;
	gotoxy (SecondX+1, FirstY+20);
	cout<< td_ve[4]<<soVe+1;
	}
}
void xoaTrang_QuanLyVe (int x, int y) {
	Normal();
	for(int i = 0; i < maxRow; i++){
		gotoxy (x, y+i); // ma so cb 
		cout << setw(7-1) << setfill(char(32)) << " ";
		gotoxy(x+7, y+i); // san bay 
      	cout << setw(17-1) << setfill(char(32)) << " ";
      	gotoxy(x+24, y+i); // gio 
  	 	cout << setw(10-1) << setfill(char(32)) << " ";
  	 	gotoxy(x+34, y+i); // ngay 
  	 	cout << setw(13-1) << setfill(char(32)) << " ";
  	 	gotoxy(x+47, y+i); // so ve 
  	 	cout << setw(7-1) << setfill(char(32)) << " ";
		gotoxy(x+54, y+i); // ho ten khach 
		cout << setw(25-1) << setfill(char(32)) << " "; 
	}
}
void veMenuQuanLyVe() {
	veHop(SecondX, FirstY, 34, 7, 15, 1, "Thong tin khach");
	veHop(SecondX, FirstY+8, 34, 4, 15, 0, "");
	veHop(SecondX, FirstY+13, 34, 10, 15, 1, "Thong tin chuyen bay");
	veHop(SecondX+35, FirstY, 7, 20, 15, 1, "Ma CB"); 
	veHop(SecondX+7+35, FirstY, 17, 20, 15, 1, "San bay den");
	veHop(SecondX+24+35, FirstY, 10, 20, 15, 1, "Gio");
	veHop(SecondX+34+35, FirstY, 13, 20, 15, 1, "Ngay");
	veHop(SecondX+47+35, FirstY, 7, 20, 15, 1, "So ve");
	veHop(SecondX+54+35, FirstY, 25, 20, 15, 1, "Ho ten cmnd");
	veHop(SecondX+35, FirstY+20+2, 59+17, 4 , 15, 1, "Thong bao"); 
	gotoxy(ThirdX+20, FirstY+21);
	cout << "Trang:    /   " ;
}
int xuLy1Dong_QuanLyVe (PTRCB First, int viTri, int trangSo, int coMau, int sl, int a[], string cmnd){ 
	if (sl == 0) return 0; 
	if (viTri+trangSo*15 == sl)
		return 0;
	if (coMau == 1)
		HighLight();
	else Normal();
	
	if  (a[viTri+trangSo*15] == -1) {
		gotoxy(x_chuyenBay, y_chuyenBay+viTri); 
	   	cout << setw(7-1) << setfill(char(32)) << " ";
	   	gotoxy(x_chuyenBay+7, y_chuyenBay+viTri);
	 	cout << setw(17-1) << setfill(char(32)) << " ";
	 	gotoxy(x_chuyenBay+24, y_chuyenBay+viTri);
		cout << setw(10-1) << setfill(char(32)) << " ";
		gotoxy(x_chuyenBay+34, y_chuyenBay+viTri);
		cout << setw(13-1) << setfill(char(32)) << " ";
	   	gotoxy(x_chuyenBay+47, y_chuyenBay+viTri);
	   	cout << setw(7-1) << setfill(char(32)) << " ";
		gotoxy(x_chuyenBay+54, y_chuyenBay+viTri);
		cout << setw(25-1) << setfill(char(32)) << " "; 
		gotoxy(x_chuyenBay+54, y_chuyenBay+viTri);
		cout<<" Khach da huy ve"; 
				
	} else {
		PTRCB p = nodepointer(First, a[viTri+trangSo*15]);
		gotoxy(x_chuyenBay, y_chuyenBay+viTri); 
	    cout<< " "<<p->data.maCB<<" ";
	   	gotoxy(x_chuyenBay+7, y_chuyenBay+viTri);
	 	cout<< " "<<p->data.sanBayDen<<" ";
	 	gotoxy(x_chuyenBay+24, y_chuyenBay+viTri);
		cout<<" "<< p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" ";
		gotoxy(x_chuyenBay+34, y_chuyenBay+viTri);
		cout<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam; 
	   	gotoxy(x_chuyenBay+47, y_chuyenBay+viTri);
	   	int soVe = laySoVe_CMND(p, cmnd);
		if (soVe != -1)
		{
			cout<<" "<< soVe+1<<" "; 
		 } 
		gotoxy(x_chuyenBay+54, y_chuyenBay+viTri);
		cout<<" "<<p->data.ve.danhSach[soVe].cmnd<<" "; // tam thoi in cmnd
	}
}
void duLieu_QuanLyVe (PTRCB First, int x, int y, int trangSo, int sl, int a[], string cmnd){
	if (sl == 0) return; 
	PTRCB p; 
	gotoxy(ThirdX-8+35, FirstY+21);
	cout << trangSo+1;
	int maxPage = sl/15;
	if (sl%15 != 0)
		maxPage++; 
	gotoxy(ThirdX-3+35, FirstY+21);
	cout << maxPage;
	int j=0;
			for(int i = 0+trangSo*maxRow; i < maxRow+trangSo*maxRow; i++){ 
			if (i == sl)
				break; 
			if (a[i] == -1) {
				gotoxy(x, y+j);
				cout << setw(7-1) << setfill(char(32)) << " ";
				gotoxy(x+7, y+j); // san bay 
		      	cout << setw(17-1) << setfill(char(32)) << " ";
		      	gotoxy(x+24, y+j); // gio 
		  	 	cout << setw(10-1) << setfill(char(32)) << " ";
		  	 	gotoxy(x+34, y+j); // ngay 
		  	 	cout << setw(13-1) << setfill(char(32)) << " ";
		  	 	gotoxy(x+47, y+j); // so ve 
		  	 	cout << setw(7-1) << setfill(char(32)) << " ";
				gotoxy(x+54, y+j); // ho ten khach 
				cout << setw(25-1) << setfill(char(32)) << " "; 
				gotoxy(x+54, y+j); // ho ten khach 
				cout<<" Khach da huy ve"; 
	       		j++;
			} else {
				p = nodepointer(First, a[i]); 
				if(p == NULL) {
				gotoxy(x_thongBao, y_thongBao); 
   				cout<<"\n   (Khong co chuyen bay nao trong danh sach)";
   				}
				if (j==maxRow)
					j=0;
				if  (p==NULL)
					break; 
	       		gotoxy(x, y+j);
	      		cout<< " "<<p->data.maCB<<" ";
	      		gotoxy(x+7, y+j);
	  	 		cout<< " "<<p->data.sanBayDen<<" ";
	  	 		gotoxy(x+24, y+j);
				cout<< " "<<p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" ";
				gotoxy(x+34, y+j);
				cout<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam; 
	   			gotoxy(x+47, y+j);
	   			int soVe = laySoVe_CMND(p, cmnd);
				if (soVe != -1)
				{
					cout<<" "<< soVe+1<<" "; 
				 } 
		 		gotoxy (x+54, y+j);
				cout<<" "<<cmnd<<" "; // tam thoi in cmnd
	       		p = p->next;
	       		j++;
       	}
	}	
}

//============Dat ve=======
void veMenu_CB_DatVe (){
	veHop(SecondX, FirstY, 34, 7, 15, 1, "Thong tin khach");
	veHop(SecondX, FirstY+8, 34, 4, 15, 0, "");
	veHop(SecondX, FirstY+13, 34, 10, 15, 1, "Thong tin chuyen bay");
	veHop(SecondX+35, FirstY, 7, 20, 15, 1, "Ma CB");
	veHop(SecondX+7+35, FirstY, 17, 20, 15, 1, "San bay den");
	veHop(SecondX+24+35, FirstY, 10, 20, 15, 1, "Gio");
	veHop(SecondX+34+35, FirstY, 13, 20, 15, 1, "Ngay");
	veHop(SecondX+47+35, FirstY, 15, 20, 15, 1, "Trang thai");
	veHop(SecondX+62+35, FirstY, 17, 20, 15, 1, "So hieu may bay");
	veHop(SecondX+35, FirstY+20+2, 59+17, 4 , 15, 1, "Thong bao"); 
//	gotoxy(ThirdX-15+30, FirstY+21);
//	cout << "Trang:    /   " ;
	gotoxy(ThirdX+20, FirstY+21);
	cout << "Trang:    /   " ;
}
void duLieu_CB_DatVe (PTRCB First, int x, int y, int trangSo,int soluong, int CB[] ){
	PTRCB p;
	gotoxy(ThirdX-8+35, FirstY+21);
	cout << trangSo+1;
   	if(p == NULL)
    printf("\n   (Khong co chuyen bay nao trong danh sach)");
	int j=0;
	for(int i = 0+trangSo*maxRow; i < maxRow+trangSo*maxRow; i++){ 
		if ( i == soluong ) break; 
		if (CB[i] == -1) {
			gotoxy (x, y+j); // ma so cb 
			cout << setw(7-1) << setfill(char(32)) << " ";
			gotoxy(x+7, y+j); // san bay 
	      	cout << setw(17-1) << setfill(char(32)) << " ";
	      	gotoxy(x+24, y+j); // gio 
	  	 	cout << setw(10-1) << setfill(char(32)) << " ";
	  	 	gotoxy(x+24+10, y+j); // gio 
	  	 	cout << setw(11) << setfill(char(32)) << " ";
	  	 	gotoxy(x+44+3, y+j); 
	  	 	cout<<" Da dat ve "; 
			gotoxy(x+59+3, y+j);
			cout << setw(17-1) << setfill(char(32)) << " "; 
			j++;
		 } else {
			p = nodepointer(First, CB[i]); 
			if (j==maxRow)
				j=0;
	       	gotoxy(x, y+j);
	      	cout<< " "<<p->data.maCB<<" ";
	      	gotoxy(x+7, y+j);
	  	 	cout<< " "<<p->data.sanBayDen<<" ";
	  	 	gotoxy(x+24, y+j);
			cout<< " "<<p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" ";
			gotoxy(x+24+10, y+j);
			cout<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam; 
	   		gotoxy(x+44+3, y+j);
	   		if (p->data.trangThai == 1) cout<<" Con ve "; 
			gotoxy(x+59+3, y+j);
		 	cout<< " "<<p->data.soHieuMB<<" ";
	       	p = p->next;
	       	j++;
	    	}
	}
} 
int xuLy1Dong_CB_DatVe (PTRCB First, int viTri, int trangSo, int coMau, int soluong, int CB[]){ // khop voi  veMenuChuyenBay (){
	if (viTri+trangSo*15 == soluong) 
		return 0;
	if (coMau == 1)
		HighLight();
	else Normal();
	if  (CB[viTri+trangSo*15] == -1) {
		gotoxy(SecondX+1+35, FirstY+3+viTri); 
	    cout << setw(7-1) << setfill(char(32)) << " ";
	   	gotoxy(SecondX+7+1+35, FirstY+3+viTri);
	 	cout << setw(17-1) << setfill(char(32)) << " ";
	 	gotoxy(SecondX+24+1+35, FirstY+3+viTri);
		cout << setw(10-1) << setfill(char(32)) << " ";
		gotoxy(SecondX+31+1+35+3, FirstY+3+viTri);
		cout << setw(11) << setfill(char(32)) << " "; 
	   	gotoxy(SecondX+44+1+35+3, FirstY+3+viTri);
		cout<<" Da dat ve "; 
		gotoxy(SecondX+59+1+35+3, FirstY+3+viTri);
	 	cout << setw(17-1) << setfill(char(32)) << " ";  
	} else {
		PTRCB p = nodepointer(First, CB[viTri+trangSo*15]);
		gotoxy(SecondX+1+35, FirstY+3+viTri); 
	    cout<< " "<<p->data.maCB<<" ";
	   	gotoxy(SecondX+7+1+35, FirstY+3+viTri);
	 	cout<< " "<<p->data.sanBayDen<<" ";
	 	gotoxy(SecondX+24+1+35, FirstY+3+viTri);
		cout<<" "<< p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" ";
		gotoxy(SecondX+31+1+35+3, FirstY+3+viTri);
		cout<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam; 
	   	gotoxy(SecondX+44+1+35+3, FirstY+3+viTri);
		if (p->data.trangThai == 1) cout<<" Con ve "; 
		gotoxy(SecondX+59+1+35+3, FirstY+3+viTri);
	 	cout<< " "<<p->data.soHieuMB<<" ";
 	}
} 
bool check_gheDat (PTRCB p, int i, string nhapSoGhe ) {
	
	if(i > p->data.ve.SoVeMax || i == 0){
			Normal();
			in_thong_bao_cb(9);
			gotoxy(x_chuyenBay+nhapSoGhe.length(), y_chuyenBay-2);
			cout << setw(30) << setfill(char(32)) << " "; 
			gotoxy(x_chuyenBay+nhapSoGhe.length(), y_chuyenBay-2);
			return false; 
	} else if (p->data.ve.danhSach[i-1].cmnd != "") {
			Normal();
			in_thong_bao_cb(13);
			gotoxy(x_chuyenBay+nhapSoGhe.length(), y_chuyenBay-2);
			cout << setw(30) << setfill(char(32)) << " "; 
			gotoxy(x_chuyenBay+nhapSoGhe.length(), y_chuyenBay-2);
			return false; 
	}  
	return true; 
} 
int Dat_Cho (PTRCB &First, int viTri, int trangSo, int sl, int a[], int soluong, int CB[] , string cmnd) { //Chon ghe 
		Normal();
		xoa_huong_dan();
 		in_huong_dan(1, 0);
		in_huong_dan(2, 1);
		in_huong_dan(3, 2);
		in_huong_dan(4, 5);
		in_huong_dan(5, 6);
		in_huong_dan(6, 9);
		gotoxy(x_thongBao, y_thongBao);
		cout << setw(50)<< setfill(char(32)) << " ";
		gotoxy(x_thongBao, y_thongBao);
		cout<<"Vui long nhap so ghe";
	if (CB[viTri+trangSo*15] == -1) {
		in_thong_bao_cb(5);
		return -1;
	} 
	veHop(x_chuyenBay-1,y_chuyenBay+1, 90, 14, 15, 1, "Danh sach ghe ngoi" );
	veHop(x_thongBao-1, y_thongBao-6, 90, 2, 15, 0, "");
		gotoxy (x_thongBao, y_thongBao-5);
		cout<<"   x: Ghe da duoc dat                So: Ghe trong";
	PTRCB p = nodepointer(First, CB[viTri+trangSo*15]);
	gotoxy (x_CB_DatVe, y_CB_DatVe);
	cout<< td_chuyen_bay[0]<<p->data.maCB;
	gotoxy (x_CB_DatVe, y_CB_DatVe+1);
	cout<< td_chuyen_bay[1]<<p->data.sanBayDen;
	gotoxy (x_CB_DatVe, y_CB_DatVe+2);
	cout<< td_chuyen_bay[2]<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam;
	gotoxy (x_CB_DatVe, y_CB_DatVe+3);
	cout<< td_chuyen_bay[3]<<p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut;
	gotoxy (x_CB_DatVe, y_CB_DatVe+4);
	cout<< td_chuyen_bay[4]<<p->data.trangThai;
	gotoxy (x_CB_DatVe, y_CB_DatVe+5);
	cout<< td_chuyen_bay[5]<<p->data.soHieuMB;
	int soChoNgoi = p->data.ve.SoVeMax;
	int so_hang =  soChoNgoi/20;  
	if (soChoNgoi%20 != 0) so_hang= so_hang + 1;  
	int cho=1; 
	string str = "";
	for (int j = 1; j <= so_hang; j++) {
		gotoxy (x_chuyenBay,y_chuyenBay+4+j);
		 for (int i=cho; i<=j*20;i++) {
		 	if (i > p->data.ve.SoVeMax) break; 
		 	if (str.compare(p->data.ve.danhSach[i-1].cmnd)==0) { 
				if (i<10) {
		 			cout<<"   "<<i;
		 			continue;
				 } 
		 		cout<<"  "<<i;
		 		continue;
			 }
			 else cout<<"   x";
		 	
		 }
		 cho = j*20+1;
	}  
	veHop(x_chuyenBay-1, y_chuyenBay-3, 50, 2, 15, 0, "");
	gotoxy (x_chuyenBay, y_chuyenBay-2); 
	string nhapSoGhe = "Nhap so ghe muon dat: ";  
	cout<<nhapSoGhe; 
	gotoxy(x_chuyenBay+nhapSoGhe.length(), y_chuyenBay-2);
	string soGhe;
	int i=0;
	char c;
	while (true)
	{
		while (kbhit())
		{
		c = GetKey();
		if(c>=48 && c<=57){
			gotoxy(x_chuyenBay+nhapSoGhe.length()+i, y_chuyenBay-2);
			cout<<c;
			soGhe += c;
			i++;
		}else if(c>=97 && c<=122 || c>=65 && c<= 90){
			Normal();
			in_thong_bao_cb(9);
			continue;
			}
		else if(c==BACKSPACE){
			if (i == 0)	continue;
			else 
			{
				--i;
				soGhe=soGhe.substr(0,i);
				cout << c << " " << c;
				continue;
			}
		}else if(c==ENTER){
			if (i==0){
				in_thong_bao_cb(3);
				Normal();
				continue;
			} else {
				int soGheKhachChon = stoi(soGhe);
				if (check_gheDat(p, soGheKhachChon, nhapSoGhe ) == true) {
					string s = "Xac nhan dat ve";
					int x = xac_nhan(FirstY+26, s);
					if(x==0) { 
						p->data.ve.danhSach[soGheKhachChon-1].cmnd = cmnd;
						p->data.ve.SoVeDaDat ++;
						sl++;
						a[sl] = CB[viTri+trangSo*15];
						cout<<a[sl]; 
						CB[viTri+trangSo*15] = -1; // set lai cai vi tri nay de khong the dat ve mot lan nua 
						xoa_xac_nhan(FirstY+24);
						xoabang(x_chuyenBay-1, y_chuyenBay-3,21, 91);
						xoabang(x_CB_DatVe, y_CB_DatVe,6,30);
						return -1; 
					} else if(x==1){
						xoa_xac_nhan(FirstY+24);
						continue; 
					}
				} else {
					Normal();
					in_thong_bao_cb(9);
					gotoxy(x_chuyenBay+nhapSoGhe.length(), y_chuyenBay-2);
					cout << setw(30) << setfill(char(32)) << " "; 
					gotoxy(x_chuyenBay+nhapSoGhe.length(), y_chuyenBay-2);
					soGhe = ""; 
				} 
			}
			
		} else if(c==ESC){
				string s = "Thoat se khong luu";
				int x = xac_nhan(FirstY+26, s);
				if(x==0) {
				gotoxy(x_thongBao, y_thongBao);
				cout << setw(50)<< setfill(char(32)) << " ";
				xoa_xac_nhan(FirstY+24);
				xoabang(x_chuyenBay-1, y_chuyenBay-3,22, 100);
				xoabang(x_CB_DatVe, y_CB_DatVe,6,30);
				return -1; 
				}
				else if(x==1){
					xoa_xac_nhan(FirstY+24);
					continue; 
				}
		}	
			
		}
	}
	     
}
bool check_viTri (int vitri, int sl, int a[]) {
	for (int i = 0; i<sl ; i++)
			{
				if (vitri == a[i] & a[i] > 0) {
					return false;
				}
			}
			return true;
}
string nhap_NoiDen () {
	string noiDen; 
	string NhapNoiDen = "Noi den: ";
	gotoxy (SecondX+1, FirstY+9);
	cout<<NhapNoiDen;
	gotoxy (SecondX+10, FirstY+9); 
	show_cur(1);
	int i=0;
	char c;
	while(1){
		c = GetKey();
		if(c==SPACE){
			in_thong_bao_cb(3); 
			Normal();
			continue;
		}if(c==ENTER){
			if (i==0){
				in_thong_bao_cb(3); 
				Normal();
				continue;
			}else
			{
				return noiDen;
			}
		}
		if(c==BACKSPACE){
			if (i == 0)	continue;
			else 
			{
				--i;
				noiDen=noiDen.substr(0,i);
				cout << c << " " << c;
				continue;
			}
		} if(c==ESC){
			break;
		}else if(c>=65 && c<= 90){ // lay chu in hoa 
			gotoxy(i+SecondX+10, FirstY+9);
			cout<<c;
			noiDen += c;
				i++;
		}else if(c>=97 && c<=122){//lay chu thuong 
			c-=32;
			noiDen += c;
			gotoxy(i+SecondX+10, FirstY+9);
			cout << c;       //    user= GV	
				i++;
		}
		
	}
	return noiDen;
} 
bool check_chuyenBay (PTRCB &First, int &sl, int a[], string cmnd) {
	
}
int Dat_Ve (PTRCB &First, int &sl, int a[], string cmnd) {	// dat 1 ve moi
		string NoiDen = nhap_NoiDen();
		int CB[100]; // mang luu lai vi tri cua chuyen bay con ve  
		int vitri = 0;
		int soluong = 0; 
		for (PTRCB p = First; p!=NULL; p=p->next) 
		{
			vitri++; 
			if ((NoiDen).compare(p->data.sanBayDen)==0) {
				if (p->data.trangThai == 1)
				{
					if (check_viTri(vitri, sl, a) == true) {
						CB[soluong]=vitri; // tinh theo 1,2,3,4... 
						soluong++;
					}
					else continue;
				}
			}
		}
		if (soluong == 0) {
			veMenu_CB_DatVe ();
			char ch;
			while (1) {
				gotoxy (x_thongBao, y_thongBao);
				cout<<"Khong tin thay chuyen bay phu hop. Nhan phim bat ki de thoat";
				ch = GetKey();
				xoabang(SecondX+10, FirstY+9, 1,33);
				xoabang(x_CB_DatVe, y_CB_DatVe,6,30);
				xoabang(x_chuyenBay-1, y_chuyenBay-3,29,95);
				return -1;
			}
		}		
	veMenu_CB_DatVe ();
	duLieu_CB_DatVe(First, x_chuyenBay, y_chuyenBay, 0, soluong, CB);
	int chon=0, trangSo=0;  
	int check=0;		
	int maxPage = soluong/15;
	if (soluong%15 != 0)
		maxPage++; 
	gotoxy(ThirdX-8+35, FirstY+21);
	cout << trangSo+1;
	gotoxy(ThirdX-3+35, FirstY+21);
	cout << maxPage;
	char kytu;
	int kiemtra;
	gotoxy(SecondX+1, FirstY+chon);
	xuLy1Dong_CB_DatVe(First, chon, trangSo, 1, soluong, CB); 
	do{
		kytu = GetKey();
		switch (kytu){
			case UP: if (chon+1>1){
              		xuLy1Dong_CB_DatVe(First, chon, trangSo, 0, soluong, CB); 
              		chon --;
              		xuLy1Dong_CB_DatVe(First, chon, trangSo, 1, soluong, CB); 
				}
				break;
			case DOWN: if (chon+1 <maxRow){
              		xuLy1Dong_CB_DatVe(First, chon, trangSo, 0, soluong, CB); 
              		chon ++;
              		if (xuLy1Dong_CB_DatVe(First, chon, trangSo, 1, soluong, CB) ==0){
              			chon--;
              			gotoxy(SecondX+1,FirstY+chon);
              			xuLy1Dong_CB_DatVe(First, chon, trangSo, 1, soluong, CB); 
					}
  			  	}
  			  	break;
  			case LEFT: if (trangSo+1>1){
  					xoaTrang_CB(x_chuyenBay, y_chuyenBay);
  					trangSo--;
  					chon=0;
  					duLieu_CB_DatVe(First, x_chuyenBay, y_chuyenBay, trangSo, soluong, CB);
					xuLy1Dong_CB_DatVe(First, chon, trangSo, 1, soluong, CB); 
  				}
  				break;
  			case RIGHT: if (trangSo+1<maxPage){
  					xoaTrang_CB(x_chuyenBay, y_chuyenBay);
  					trangSo++;
  					chon=0;
  					duLieu_CB_DatVe(First, x_chuyenBay, y_chuyenBay, trangSo, soluong, CB);
  					xuLy1Dong_CB_DatVe(First, chon, trangSo, 1, soluong, CB); 
  				}
  				break;
			case ENTER: {
				xoabang(x_chuyenBay-1, y_chuyenBay-3,22, 100);
				do {
						kiemtra = Dat_Cho (First, chon, trangSo, sl, a, soluong, CB, cmnd);
						if (kiemtra == -1)
						{
							break;
						 } 
					}while (1);
				veMenu_CB_DatVe ();
				duLieu_CB_DatVe(First, x_chuyenBay, y_chuyenBay, trangSo, soluong, CB);
				xuLy1Dong_CB_DatVe(First, chon, trangSo, 1, soluong, CB); 	
              	break;
            }
  			case ESC : 
			  {
			  	show_cur(0);
			  	xoabang(SecondX+10, FirstY+9, 1,33);
			  	xoabang(x_CB_DatVe, y_CB_DatVe,6,30);
			  	xoabang(x_chuyenBay-1, y_chuyenBay-3,30,95);
			  	return -1;
			  }
		}
		if (check ==1)
			break;
	}while (1);
	
}
//===========Huy ve===============
void Huy_ve(PTRCB &First, int viTri, int trangSo, int sl, int a[], string cmnd) {
	PTRCB p = nodepointer(First, a[viTri+trangSo*15]);
	Normal();
	int soVe = laySoVe_CMND(p, cmnd);
	string s = "Xac nhan huy ve";
	int x = xac_nhan(FirstY+26, s);
	if(x==0) {
		p->data.ve.SoVeDaDat - 1; // giam ve da dat len  
		p->data.ve.danhSach[soVe].cmnd = "";	
		a[viTri+trangSo*15] = -1; 				
		xoa_xac_nhan(FirstY+24);
		
		return; 
	}
	else if(x==1){
		xoa_xac_nhan(FirstY+24);
		return; 
	}
	
}  
//===========Quan li ve=========== 
string nhapCMND (NODEPTR &root){
	gotoxy(SecondX+1, FirstY+3);
	string temp;
	char c;
	cout << "Nhap so CCCD:";
	gotoxy(SecondX+15, FirstY+3);
	bool thoat=false;
	while(thoat == false){
		c = GetKey();
		switch(c){
			case BACKSPACE:{
				if(temp.length() > 0)
				{
					gotoxy(SecondX+15 + temp.length()-1, FirstY+3); cout << " ";
					gotoxy(SecondX+15 + temp.length()-1, FirstY+3);
					temp = temp.substr(0, temp.length()-1);
				}	
				break;
			}
			case ENTER:{
				if (temp.length()==12)
					thoat = true;
				break;
			}
			default:{
				if(c >= 48 && c <= 57) //Chi lay so
				{
					temp += c;
					cout << c;
				}
				break;
			}
		}
	}
	NODEPTR p;
	p = SearchTree(root, temp);
	if (p==NULL){
		int vt=0;
		string hten, phai;
		gotoxy(SecondX+1, FirstY+4);
		cout << "Ho va ten:";
		gotoxy(SecondX+1, FirstY+5);
		cout << "Gioi tinh:";
		gotoxy(SecondX+13, FirstY+4);
		while(1)
		{
			c = GetKey();
			switch (c)
			{
				case UP: if(vt + 1 > 1) //Dua con nhay len tren
				{
					vt--;
					if(vt == 0) gotoxy(SecondX+13 + hten.length(), FirstY+4 + vt);
					else if(vt == 1) gotoxy(SecondX+13 + phai.length(), FirstY+4 + vt);
				} break;
				case ENTER: if(vt + 1 < 2) //Xuong dong
				{
					vt++;
					if(vt == 0) gotoxy(SecondX+13 + hten.length(), FirstY+4 + vt);
					else if(vt == 1) gotoxy(SecondX+13 + phai.length(), FirstY+4 + vt);
				} break;
				case DOWN: if(vt + 1 < 3) //Xuong dong
				{
					vt++;
					if(vt == 0) gotoxy(SecondX+13 + hten.length(), FirstY+4 + vt);
					else if(vt == 1) gotoxy(SecondX+13 + phai.length(), FirstY+4 + vt);
				} break;
				
				case ESC: 
				{
					gotoxy(SecondX+1, FirstY+3);
					cout << setw(35) << setfill(char(32)) << " ";
					gotoxy(SecondX+1, FirstY+4);
					cout << setw(35) << setfill(char(32)) << " "; 
					gotoxy(SecondX+1, FirstY+5);
					cout << setw(35) << setfill(char(32)) << " ";
					return "";
				}
		
				case CtrlS: 
				{
					HanhKhach hk;
					hk.cmnd = temp;
					ChuanHoaString(hten);
					ChuanHoaString(phai);
					if(hten.compare("") == 0)
					{
						HighLight();
						gotoxy(SecondX+1, FirstY+6); cout << "Khong duoc de trong ho va ten";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+1, FirstY+7); cout << "                                   ";
						vt=0;
						gotoxy(SecondX+13 + hten.length(), FirstY+4 + vt);
						
					}
					else if(phai.compare("") == 0)
					{
						HighLight();
						gotoxy(SecondX+1, FirstY+6); cout << "Khong duoc de trong gioi tinh";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+1, FirstY+6); cout << "                                   ";
						vt=1;
						gotoxy(SecondX+13 + phai.length(), FirstY+4 + vt);
					}
					else if(phai.compare("Nam") != 0 && phai.compare("Nu") != 0)
					{
						HighLight();
						gotoxy(SecondX+1, FirstY+6); cout << "Gioi tinh chi nhan Nam hoac Nu";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+1, FirstY+6); cout << "                                   ";
						vt=1;
						gotoxy(SecondX+13 + phai.length(), FirstY+4 + vt);
					}
					else
					{
						int tach = hten.find_last_of(" ");
						hk.ho = hten.substr(0, tach);
						hk.ten = hten.substr(tach+1, hten.length());
						if (phai.compare("Nam")==0)
							hk.phai = 0;
						else if (phai.compare("Nu")==0)
							hk.phai = 1;
						Insert_nodeTree(root, hk.cmnd, hk);
						HighLight();
						gotoxy(SecondX+1, FirstY+6); cout << "Du lieu da duoc luu lai ";
						Sleep(2000);
						Normal();
						gotoxy(SecondX+1, FirstY+6); cout << "                        ";
						
						return hk.cmnd;			
					}
				}
				break;
				default: switch(vt)
				{
					case 0: //Vi tri con tro o phan Ho va ten
					{
						if (c==BACKSPACE){
							if(hten.length() > 0)
							{
								gotoxy(SecondX+13 + hten.length()-1, FirstY+4); cout << " ";
								gotoxy(SecondX+13 + hten.length()-1, FirstY+4);
								hten = hten.substr(0, hten.length()-1);
							}	
						}
						else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 32 ) //Lay chu cai in thuong, in hoa vs khoang trang
						{
							hten+=c;
							cout << c;
						}
						break;	
					} 
					case 1: //Vi tri con tro o phan Gioi tinh
					{
						if (c==BACKSPACE){
							if(phai.length() > 0)
							{
								gotoxy(SecondX+13 + phai.length()-1, FirstY+5); cout << " ";
								gotoxy(SecondX+13 + phai.length()-1, FirstY+5);
								phai = phai.substr(0, phai.length()-1);
							}	
						}
						else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) //Lay chu cai in thuong, in hoa
						{
							phai+=c;
							cout << c;
						}
						break;	
					} 
				}
			}
		}
	}else {
		gotoxy(SecondX+1, FirstY+4);
		cout << "Ho va ten:";
		gotoxy(SecondX+13, FirstY+4);
		cout << p->data.ho <<" "<< p->data.ten;
		gotoxy(SecondX+1, FirstY+5);
		cout << "Gioi tinh:";
		gotoxy(SecondX+13, FirstY+5);
		if  (p->data.phai==0)
			cout << "Nam";
		else if  (p->data.phai==1)
			cout << "Nu";
		return p->data.cmnd; 
	} return p->data.cmnd;
}
int QuanLyVe (PTRCB &First, NODEPTR &root) {
	Normal();
	in_huong_dan(1, 0);
	in_huong_dan(2, 1);
	in_huong_dan(3, 2);
	in_huong_dan(4, 5);
	in_huong_dan(5, 6);
	in_huong_dan(6, 8);
	gotoxy(x_thongBao, y_thongBao);
	cout << setw(50)<< setfill(char(32)) << " ";
	gotoxy (x_thongBao, y_thongBao);
	cout<<"Vui long nhap CCCD: Co 12 so, chi chua ki tu so.";
	veMenuQuanLyVe();
	string cmnd = nhapCMND(root);//"123456789123"
	gotoxy(x_thongBao, y_thongBao);
	cout << setw(50)<< setfill(char(32)) << " ";
	// danh sach ve da dat cua khach
		int a[100]; // mang luu lai vi tri cua chuyen bay co  
		int sl = 0; 
		int vt = 0;
		for (PTRCB p = First; p!=NULL; p=p->next) {
		vt++; 
		if (p->data.trangThai == 1 || p->data.trangThai == 2) {
			for (int i=0 ; i < p->data.ve.SoVeMax ; i++) {
					if (p->data.ve.danhSach[i].cmnd == cmnd) {
						a[sl]=vt;	// tinh theo 1, 2, 3,... 
						sl++;
					}
				}
			}
		}
	duLieu_QuanLyVe(First, x_chuyenBay, y_chuyenBay, 0, sl, a, cmnd) ;
	int chon=0, trangSo=0;  
	int check=0;		
	int maxPage = sl/15;
	if (sl%15 != 0)
		maxPage++; 
	gotoxy(ThirdX-8+35, FirstY+21);
	cout << trangSo+1;
	gotoxy(ThirdX-3+35, FirstY+21);
	cout << maxPage;
	char kytu;
	int kiemtra; 
	gotoxy(SecondX+1, FirstY+chon);
	xuLy1Dong_QuanLyVe(First, chon, trangSo, 1, sl, a, cmnd);
	do{
		kytu = GetKey();
		switch (kytu){
			case UP: if (chon+1>1){
              		xuLy1Dong_QuanLyVe(First, chon, trangSo, 0, sl, a, cmnd);
              		chon --;
              		xuLy1Dong_QuanLyVe(First, chon, trangSo, 1, sl, a, cmnd);
				}
				break;
			case DOWN: if (chon+1 <maxRow){
              		xuLy1Dong_QuanLyVe(First, chon, trangSo, 0 , sl, a, cmnd);
              		chon ++;
              		if (xuLy1Dong_QuanLyVe(First, chon, trangSo, 1, sl, a, cmnd)==0){
              			chon--;
              			gotoxy(SecondX+1,FirstY+chon);
              			xuLy1Dong_QuanLyVe(First, chon, trangSo, 1, sl, a, cmnd);
					}
  			  	}
  			  	break;
  			case LEFT: if (trangSo+1>1){
  					xoaTrang_CB(x_chuyenBay, y_chuyenBay);
  					trangSo--;
  					chon=0;
  					duLieu_QuanLyVe(First, x_chuyenBay, y_chuyenBay, 0, sl, a, cmnd) ;
					xuLy1Dong_QuanLyVe(First, chon, trangSo, 1, sl, a, cmnd);
  				}
  				break;
  			case RIGHT: if (trangSo+1<maxPage){
  					xoaTrang_CB(x_chuyenBay, y_chuyenBay);
  					trangSo++;
  					chon=0;
  					duLieu_QuanLyVe(First, x_chuyenBay, y_chuyenBay, 0, sl, a, cmnd) ;
  					xuLy1Dong_QuanLyVe(First, chon, trangSo, 1, sl, a, cmnd);
  				}
  				break;
  			case InSert:{ 
					xoabang(x_chuyenBay-1, y_chuyenBay-3,22,100);
					xoabang(SecondX+1, FirstY+16,7,32);
					while (1) {
						kiemtra = Dat_Ve(First, sl, a, cmnd);
						if (kiemtra == -1)
						{
							veMenuQuanLyVe();
			  				duLieu_QuanLyVe(First, x_chuyenBay, y_chuyenBay, 0, sl, a, cmnd) ;
			  				xuLy1Dong_QuanLyVe(First, chon, trangSo, 1, sl, a, cmnd);
							break;
						 } 
					}
			  	}break;
			case DEL: {
				Huy_ve(First,chon, trangSo, sl, a, cmnd); 
				duLieu_QuanLyVe(First, x_chuyenBay, y_chuyenBay, 0, sl, a, cmnd) ;
  				xuLy1Dong_QuanLyVe(First, chon, trangSo, 1, sl, a, cmnd);
				break;
			} 
			case ENTER: {
				if (sl != 0) {
					xoabang(SecondX+1, FirstY+16,7,32);
	              	xuat_1Ve(First, chon, trangSo,0, sl, a, cmnd);
	              	break;
              	} else break;
            }
  			case ESC : 
			  {
			  	xoa_huong_dan();
			  	xoabang(SecondX, FirstY,29,130);
			  	return -1;
			  }
		}
		if (check ==1)
			break;
	}while (1);
} 
//============= VE VA GHE TRONG (Cau e, f, g) ======================================================================================================== 
//Chuyen bay co chua ghe trong cua e, g
void xoaTrang_CB_DSVe (int x, int y) {
	Normal();
	for(int i = 0; i < maxRow; i++){
		gotoxy (x, y+i); // ma so cb 
		cout << setw(7-1) << setfill(char(32)) << " ";
		gotoxy(x+7, y+i); // san bay 
      	cout << setw(17-1) << setfill(char(32)) << " ";
      	gotoxy(x+24, y+i); // gio 
  	 	cout << setw(10-1) << setfill(char(32)) << " ";
  	 	gotoxy(x+34, y+i); // gio 
  	 	cout << setw(13-1) << setfill(char(32)) << " ";
  	 	gotoxy(x+47, y+i); 
  	 	cout << setw(15-1) << setfill(char(32)) << " ";
		gotoxy(x+59+3, y+i);
		cout << setw(17-1) << setfill(char(32)) << " "; 
		gotoxy (x+79, y+i);
		cout << setw(15-1) << setfill(char(32)) << " "; 
	}
}
void veMenu_CB_DSVe (){ // bang chuyen bay chuc nang 4 - co them mot cot la "So ve trong" 
	veHop(SecondX, FirstY, 34, 15, 15, 1, "Thong tin");
	veHop(SecondX+35, FirstY, 7, 20, 15, 1, "Ma CB"); 
	veHop(SecondX+7+35, FirstY, 17, 20, 15, 1, "San bay den");
	veHop(SecondX+24+35, FirstY, 10, 20, 15, 1, "Gio");
	veHop(SecondX+24+10+35, FirstY, 13, 20, 15, 1, "Ngay");
	veHop(SecondX+44+35+3, FirstY, 15, 20, 15, 1, "Trang thai");
	veHop(SecondX+59+35+3, FirstY, 17, 20, 15, 1, "So hieu may bay");
	veHop(SecondX+79+35, FirstY, 15, 20, 15, 1, "SO VE TRONG");
	veHop(SecondX+35, FirstY+20+2, 59+17, 4 , 15, 1, "Thong bao"); 
	gotoxy(ThirdX+20, FirstY+21);
	cout << "Trang:    /   " ;
}
int xuLy1Dong_CB_DSVe (PTRCB First, int viTri, int trangSo, int coMau, int soluong, int CB[]){ // in chuyen bay o chuc nang 4 
	if (viTri+trangSo*15 == soluong) 
		return 0;
	if (coMau == 1)
		HighLight();
	else Normal();
	PTRCB p = nodepointer(First, CB[viTri+trangSo*15]);
	gotoxy(SecondX+1+35, FirstY+3+viTri); 
    cout<< " "<<p->data.maCB<<" ";
   	gotoxy(SecondX+7+1+35, FirstY+3+viTri);
 	cout<< " "<<p->data.sanBayDen<<" ";
 	gotoxy(SecondX+24+1+35, FirstY+3+viTri);
	cout<<" "<< p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" ";
	gotoxy(SecondX+31+1+35+3, FirstY+3+viTri);
	cout<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam; 
   	gotoxy(SecondX+44+1+35+3, FirstY+3+viTri);
	if (p->data.trangThai == 1) cout<<" Con ve ";
	if (p->data.trangThai == 2) cout<<" Het ve "; 
	gotoxy(SecondX+59+1+35+3, FirstY+3+viTri);
 	cout<< " "<<p->data.soHieuMB<<" ";
 	gotoxy (SecondX+79+1+35, FirstY+3+viTri); 
 	cout<<" "<<p->data.ve.SoVeMax-p->data.ve.SoVeDaDat<<" "; 
 
}
void duLieu_CB_DSVe (PTRCB First, int x, int y, int trangSo, int soluong, int CB[]){
	PTRCB p;
	gotoxy(ThirdX-8+35, FirstY+21);
	cout << trangSo+1;
	int maxPage;
	maxPage = soluong/15;
	if (soluong%15 != 0)
		maxPage++;  
	gotoxy(ThirdX-3+35, FirstY+21);
	cout << maxPage;
	int j=0;
	for(int i = 0+trangSo*maxRow; i < maxRow+trangSo*maxRow; i++){ 
			p = nodepointer(First, CB[i]);
			if ( i == soluong ) break; 
			if (j==maxRow)
			j=0; 
		 	if  (p==NULL)
			break;
	       	gotoxy(x, y+j);
	      	cout<< " "<<p->data.maCB<<" ";
	      	gotoxy(x+7, y+j);
	  	 	cout<< " "<<p->data.sanBayDen<<" ";
	  	 	gotoxy(x+24, y+j);
			cout<< " "<<p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" ";
			gotoxy(x+24+10, y+j);
			cout<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam; 
	   		gotoxy(x+44+3, y+j);
	   		if (p->data.trangThai == 0) cout<<" Huy chuyen ";
			if (p->data.trangThai == 1) cout<<" Con ve ";
			if (p->data.trangThai == 2) cout<<" Het ve ";
			if (p->data.trangThai == 3) cout<<" Hoan tat "; 
			gotoxy(x+59+3, y+j);
		 	cout<< " "<<p->data.soHieuMB<<" ";
		 	gotoxy (x+79, y+j);
			cout<<" "<<p->data.ve.SoVeMax-p->data.ve.SoVeDaDat<<" "; 
	       	p = p->next;
	       	j++;
	}
}
//========e. In danh sach ve cua chuyen bay X========
void veMenuDSVe () {	// bang danh sach ve 
	veHop(SecondX, FirstY, 34, 15, 15, 1, "Thong tin");
	veHop(SecondX+35, FirstY+4, 5, 18, 15, 1, "STT"); 
	veHop(SecondX+5+35, FirstY+4, 10, 18, 15, 1, "SO VE");
	veHop(SecondX+15+35, FirstY+4, 15, 18, 15, 1, "SO CMND");
	veHop(SecondX+30+35, FirstY+4, 25, 18, 15, 1, "HO TEN");
	veHop(SecondX+55+35, FirstY+4, 10, 18, 15, 1, "PHAI");
	gotoxy(SecondX+40+35, FirstY+23);
	cout << "Trang:    /   " ;
	
 }
 void xoaTrang_DSVe (int x, int y) {
	Normal();
	for(int i = 0; i < maxRow; i++){
		gotoxy (x, y+i);  
		cout << setw(5-1) << setfill(char(32)) << " ";
		gotoxy(x+5, y+i); 
      	cout << setw(10-1) << setfill(char(32)) << " ";
      	gotoxy(x+15, y+i);  
  	 	cout << setw(15-1) << setfill(char(32)) << " ";
  	 	gotoxy(x+30, y+i); 
  	 	cout << setw(25-1) << setfill(char(32)) << " ";
  	 	gotoxy(x+55, y+i); 
  	 	cout << setw(10-1) << setfill(char(32)) << " ";
	}
}
void duLieu_DSVe (PTRCB p,int x, int y, int viTri, int trangSo, int coMau, NODEPTR root) { // in danh sach ve cua chuyen bay 
	Normal();
	gotoxy(SecondX+40+35+7, FirstY+23);
	cout << trangSo+1;
	int j=0;
	NODEPTR q = NULL;
	int ve[100]; 
	int dem =0; 
	for (int k = 0; k < p->data.ve.SoVeMax;  k++) {
		if (p->data.ve.danhSach[k].cmnd != "") {
			ve[dem] = k; // vi tri ghe dem tu 1, 2, 3, 4, 5 
			dem++;
		}
	}
	for(int i = 0+trangSo*maxRow; i < maxRow+trangSo*maxRow; i++){ 
			if (i >= p->data.ve.SoVeDaDat) return;
			if (i == dem ) return; 
			int vetam = ve[i]; 
			gotoxy(x, y+j);
		  	cout<< j+1; 
			gotoxy (x+5, y+j);
			cout <<  ve[i]+1;
			gotoxy (x+15, y+j);
			cout<< p->data.ve.danhSach[vetam].cmnd;
			q = SearchTree(root, p->data.ve.danhSach[vetam].cmnd);
			if (q!=NULL){
			gotoxy (x+30, y+j);
			cout<< q->data.ho + " " + q->data.ten;
			gotoxy (x+55, y+j);
			if (q->data.phai == 0)
				cout<< "Nam";
			else if (q->data.phai == 1)
				cout << "Nu";
			j++;
		} 
	} 
 }
// Nhan them o day 
void ketXuatHanhKhachTheoMaCB (ofstream &fout, PTRCB p, NODEPTR root){
	fout << "Danh sach hanh khach thuoc chuyen bay " << p->data.maCB << endl;
	fout << "Ngay gio khoi hanh: " << p->data.thoiGian.date.ngay << '/' << p->data.thoiGian.date.thang << '/'
										<< p->data.thoiGian.date.nam << " " << p->data.thoiGian.h.gio << ':'<< p->data.thoiGian.h.phut << " " << p->data.sanBayDen << endl;
	fout << "STT  " << "So ve " << "So CMND       " << "Ho ten              " << "Phai" << endl;
	int j=0;
	NODEPTR q = NULL;
	int ve[100]; 
	int dem =0; 
	for (int k = 0; k < p->data.ve.SoVeMax;  k++) {
		if (p->data.ve.danhSach[k].cmnd != "") {
			ve[dem] = k; // vi tri ghe dem tu 1, 2, 3, 4, 5 
			dem++;
		}
	}
	for(int i = 0; i < p->data.ve.SoVeDaDat; i++){ 
		if (i >= p->data.ve.SoVeDaDat) return;
		if (i == dem ) return; 
		int vetam = ve[i]; 
		fout<< j+1 << "     "; 
		fout <<  ve[i]+1 << "     ";
		fout<< p->data.ve.danhSach[vetam].cmnd<<" ";
		q = SearchTree(root, p->data.ve.danhSach[vetam].cmnd);
		if (q!=NULL){
			fout<< q->data.ho << " " << q->data.ten << "     ";
			if (q->data.phai == 0)
				fout<< "Nam";
			else if (q->data.phai == 1)
				fout << "Nu";
			fout <<endl;
		} 
	}
}
// Nhan them o day 
int xuat_DSVe_theoCB (PTRCB First,int x, int y, int viTri, int trangSo, int coMau, int soluong, int CB[], NODEPTR root) {
	PTRCB p = nodepointer(First, CB[viTri+trangSo*15]);
	char KyTu;
	gotoxy (x_chuyenBay, y_chuyenBay-2);
	cout<<"DANH SACH HANH KHACH THUOC CHUYEN BAY "<<p->data.maCB; 
	gotoxy (x_chuyenBay, y_chuyenBay-1);
	cout<<"Ngay gio khoi hanh: "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam<<" "<<p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" Noi den: "<<p->data.sanBayDen;
	if (p->data.ve.SoVeDaDat == 0) {  // nham phim bat ki de thoat 
		in_thong_bao_cb(12);
		do {
			KyTu = GetKey();
	  		xoabang(x_chuyenBay-1, y_chuyenBay-3,29,100);
	  		veMenu_CB_DSVe ();
			duLieu_CB_DSVe(First, x_chuyenBay, y_chuyenBay, 0, soluong, CB) ; 
			return -1;
			} while (1);
	} else {
	int maxPage = p->data.ve.SoVeDaDat/15;
	int trangSoDSVe = 0;
	if (p->data.ve.SoVeDaDat%15 != 0)
		maxPage++; 
	gotoxy(SecondX+40+35, FirstY+23); 
	cout << "Trang:    /   ";
	gotoxy(SecondX+40+35+7, FirstY+23); 
	cout << trangSoDSVe+1;
	gotoxy(SecondX+40+35+12, FirstY+23);
	cout << maxPage;
	duLieu_DSVe(p, x_chuyenBay, y_chuyenBay+4, viTri, trangSoDSVe, 0, root);
	do {
		KyTu = GetKey();
		switch (KyTu) {
  			case LEFT: if (trangSoDSVe+1>1){
					xoaTrang_DSVe (x_chuyenBay, y_chuyenBay+4);
  					trangSoDSVe--;
  					duLieu_DSVe(p, x_chuyenBay, y_chuyenBay+4, viTri, trangSoDSVe, 0, root);
  				}
  				break;
  			case RIGHT: if (trangSoDSVe+1<maxPage){
  					xoaTrang_DSVe (x_chuyenBay, y_chuyenBay+4);
					trangSoDSVe++;
  					duLieu_DSVe(p, x_chuyenBay, y_chuyenBay+4, viTri, trangSoDSVe, 0, root);
  				}
  				break;
  			case F1: {
  				ofstream fout;
				fout.open("HanhKhachTheoChuyenBay.txt", ios_base::out);
				ketXuatHanhKhachTheoMaCB (fout,p, root);
				fout.close();
				gotoxy(x_thongBao, y_thongBao);
				HighLight();
				cout << "Ket xuat thanh cong";
				Sleep(2000);
				Normal();
				gotoxy(x_thongBao, y_thongBao);
				cout << "                    ";
				break;
			  }
  			case ESC: {
  					xoabang(x_chuyenBay-1, y_chuyenBay-3,29,100);
  					veMenu_CB_DSVe ();
					duLieu_CB_DSVe(First, x_chuyenBay, y_chuyenBay, 0, soluong, CB) ; 
			  return -1;
				}
		}
	} while (1);
	}
 } 
int inDSVe (PTRCB First, NODEPTR root){ 
		Normal(); 
		in_huong_dan(1, 0);
		in_huong_dan(2, 1);
		in_huong_dan(3, 2);
		in_huong_dan(4, 8);
		in_huong_dan(5, 10); 
		int CB[100]; // mang luu lai vi tri cua chuyen bay con ve  
		int vitri = 0;
		int soluong = 0; 
		for (PTRCB p = First; p!=NULL; p=p->next) {
		vitri++; 
			if (p->data.trangThai == 1) {
					CB[soluong]=vitri; // tinh theo 1,2,3,4... 
					soluong++;
			}
		}
	veMenu_CB_DSVe ();
	duLieu_CB_DSVe(First, x_chuyenBay, y_chuyenBay, 0, soluong, CB) ;
	int chon=0, trangSo=0;  
	int check=0;
	int kiemTra=0;
	int temp = soluong; 			
	int maxPage = temp/15;
	if (temp%15 != 0)
		maxPage++;  
	gotoxy(ThirdX-8+35, FirstY+21);
	cout << trangSo+1;
	gotoxy(ThirdX-3+35, FirstY+21);
	cout << maxPage;
	char kytu;
	gotoxy(SecondX+1, FirstY+chon);
	xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB); 
	do{
		kytu = GetKey();
		switch (kytu){
			case UP: if (chon+1>1){
              		xuLy1Dong_CB_DSVe(First, chon, trangSo, 0, soluong, CB);
              		chon --;
              		xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB);
				}
				break;
			case DOWN: if (chon+1 < maxRow){
              		xuLy1Dong_CB_DSVe(First, chon, trangSo, 0, soluong, CB);
              		chon ++;
              		 
              		if (xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB) == 0){
              			chon--;
              			gotoxy(SecondX+1,FirstY+chon);
              			xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB);
					}
  			  	}
  			  	break;
  			case LEFT: if (trangSo+1>1){
  					xoaTrang_CB_DSVe(x_chuyenBay, y_chuyenBay);
  					trangSo--;
  					chon=0;
  					duLieu_CB_DSVe(First, x_chuyenBay, y_chuyenBay, trangSo, soluong, CB);
					xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB);
  				}
  				break;
  			case RIGHT: if (trangSo+1<maxPage){
  					xoaTrang_CB_DSVe(x_chuyenBay, y_chuyenBay);
  					trangSo++;
  					chon=0;
  					duLieu_CB_DSVe(First, x_chuyenBay, y_chuyenBay, trangSo, soluong, CB);
  					xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB);
  				}
  				break;
			case ENTER: {
				show_cur(0); 
				xoabang(x_chuyenBay-1, y_chuyenBay-3,29,100  );
				veMenuDSVe();
				do{
					kiemTra = xuat_DSVe_theoCB (First, x_chuyenBay, y_chuyenBay+4, chon, trangSo, 0, soluong, CB, root);
					if (kiemTra == -1)
					{
						break;
					}
				}while (1);
              	break;
            }
  			case ESC: 
			  {
			  		xoa_huong_dan(); 
			  		xoabang(SecondX, FirstY ,29,130);
			 		return -1;
				}
		}
		if (check ==1)
			break;
	}while (1);
}
//f. In danh sach ve theo ket qua tim kiem
void veTimChuyenBayConVe (){
	veHop (SecondX, FirstY, 30, 8, 15, 1, "Nhap thong tin tim kiem");
	gotoxy(SecondX+1, FirstY+3);
	cout << "Ngay khoi hanh:";
	gotoxy(SecondX+19, FirstY+3);
	cout << '/';
	gotoxy(SecondX+22, FirstY+3);
	cout << '/';
	gotoxy(SecondX+1, FirstY+4);
	cout << "Dia diem den:";
}
void veBangChuyenBayConVe (){
	veHop(SecondX+35, FirstY, 7, 20, 15, 1, "Ma CB"); 
	veHop(SecondX+7+35, FirstY, 17, 20, 15, 1, "San bay den");
	veHop(SecondX+24+35, FirstY, 10, 20, 15, 1, "Gio");
	veHop(SecondX+24+10+35, FirstY, 13, 20, 15, 1, "Ngay");
	veHop(SecondX+44+35+3, FirstY, 15, 20, 15, 1, "So ve trong");
	veHop(SecondX+59+35+3, FirstY, 17, 20, 15, 1, "So hieu may bay");
	veHop(SecondX+35, FirstY+20+2, 59+17, 4 , 15, 1, "Thong bao"); 
	gotoxy(ThirdX-15+30, FirstY+21);
	cout << "Trang:    /   " ;
}
void danhSachTheoDiaDiemVaThoiGian (PTRCB CB2, int x, int y, int trangSo){
	gotoxy(ThirdX-15+37, FirstY+21);
	cout << trangSo+1;
	PTRCB p;
	p=CB2;
	gotoxy(ThirdX-15+37, FirstY+21);
	cout << trangSo+1;
   	if(p == NULL)
    printf("\n   (Khong co chuyen bay nao trong danh sach)");
	int j=0;
	for(int i = 0+trangSo*maxRow; i < maxRow+trangSo*maxRow; i++){ 
		p = nodepointer(CB2, i+1);
		if (j==maxRow)
			j=0;
		if  (p==NULL)
			break; 
       	gotoxy(x, y+j);
      	cout<< " "<<p->data.maCB<<" ";
      	gotoxy(x+7, y+j);
  	 	cout<< " "<<p->data.sanBayDen<<" ";
  	 	gotoxy(x+24, y+j);
		cout<< " "<<p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut<<" ";
		gotoxy(x+24+10, y+j);
		cout<<" "<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam; 
   		gotoxy(x+44+3, y+j);
   		if (p->data.trangThai == 1)cout<<p->data.ve.SoVeMax-p->data.ve.SoVeDaDat;
		gotoxy(x+59+3, y+j);
	 	cout<< " "<<p->data.soHieuMB<<" ";
       	p = p->next;
       	j++;
	}
}
int TimKiemTheoDiaDiemVaThoiGian (PTRCB First , string chuoi[4], int x, int y)  {
	PTRCB p;
	PTRCB CB2= NULL;
	int j=0; 
	for (p = First; p!=NULL; p=p->next) {
		if ((stoi(chuoi[0]) == p->data.thoiGian.date.ngay) && (stoi(chuoi[1]) == p->data.thoiGian.date.thang)
			&& (stoi(chuoi[2]) == p->data.thoiGian.date.nam) && (chuoi[3].compare(p->data.sanBayDen) == 0)){
					Insert_First(CB2, p);
					j++;						
				}
		}
	if (j==0) {
		in_thong_bao_cb(6);
		gotoxy(x_thongBao, y_thongBao);
		cout<<"Nhan phim bat ki de thoat"; 
		char k;
		while(1) {
			k = GetKey();
			return -1;
		}
	}else{
		danhSachTheoDiaDiemVaThoiGian(CB2, x_chuyenBay, y_chuyenBay, 0);
		char kytu;			
		int maxPage = j/15;
		if (j%15 != 0)
			maxPage++; 
		int trangSo=0;
		gotoxy(ThirdX-15+37, FirstY+21);
		cout << trangSo+1;
		gotoxy(ThirdX-15+42, FirstY+21);
		cout << maxPage;
		do{
			kytu = GetKey();
			switch (kytu){
	  			case LEFT: if (trangSo+1>1){
	  					xoaTrang_CB(x_chuyenBay, y_chuyenBay);
	  					trangSo--;
	  					danhSachTheoDiaDiemVaThoiGian(CB2, x_chuyenBay, y_chuyenBay, trangSo);
	  				}
	  				break;
	  			case RIGHT: if (trangSo+1<maxPage){
	  					xoaTrang_CB(x_chuyenBay, y_chuyenBay);
	  					trangSo++;
	  					danhSachTheoDiaDiemVaThoiGian(CB2, x_chuyenBay, y_chuyenBay, trangSo);
	  				}
	  				break;
	  			case ESC: {
	  				return -1;
				  }
	  		}
		}while (1);
	}
}
void nhapChuyenBayConVe (PTRCB First){
	Normal(); 
		in_huong_dan(1, 0);
		in_huong_dan(2, 1);
		in_huong_dan(3, 2);
		in_huong_dan(4, 4); 
		
	show_cur (1); 
	veTimChuyenBayConVe();
	char kytu;
	string chuoiTG[4] = {"", "", "", ""};
	int vtX=0, vtY=0, check=0;
	gotoxy(SecondX+16, FirstY+3 + vtY);
	do{
		kytu = GetKey();
		switch (kytu){
			case UP: if(vtY + 1 > 1) //Dua con nhay len tren
			{
				vtY--;
				if(vtY == 0){
					vtX = 2;
					gotoxy(SecondX+16 + vtX*4+chuoiTG[2].length(), FirstY+3 + vtY);
						
				}
				else if(vtY == 1) gotoxy(SecondX+16, FirstY+3 + vtY);
			} break;
			case ENTER: if(vtY + 1 < 2) //Xuong dong
			{
				vtY++;
				if(vtY == 0){
					vtX = 2;
					gotoxy(SecondX+16 + vtX*4+chuoiTG[2].length(), FirstY+3 + vtY);
						
				}
				else if(vtY == 1) gotoxy(SecondX+16 , FirstY+3 + vtY);
			} break;
			case DOWN: if(vtY + 1 < 3) //Xuong dong
			{
				vtY++;
				if(vtY == 0){
					gotoxy(SecondX+16+chuoiTG[2].length(), FirstY+3 + vtY);
					vtX = 2;	
				} 
				else if(vtY == 1) gotoxy(SecondX+16+chuoiTG[3].length() , FirstY+3 + vtY);
			} break;
			case LEFT: if(vtY==0){
				if(vtX + 1 > 1){
					vtX--;
					if(vtX == 0) gotoxy(SecondX+16+chuoiTG[0].length() , FirstY+3 + vtY);
					else if(vtX == 1) gotoxy(SecondX+16 + vtX*4+chuoiTG[1].length(), FirstY+3 + vtY);
					else if(vtX == 2) gotoxy(SecondX+16 + vtX*4+chuoiTG[2].length(), FirstY+3 + vtY);
					break;
				}
				break;
			}else break;
			case RIGHT: if(vtY==0){
				if(vtX + 1 < 3){
					vtX++;
					if(vtX == 0) gotoxy(SecondX+16+chuoiTG[0].length() , FirstY+3 + vtY);
					else if(vtX == 1) gotoxy(SecondX+16 + vtX*4+chuoiTG[1].length(), FirstY+3 + vtY);
					else if(vtX == 2) gotoxy(SecondX+16 + vtX*4+chuoiTG[2].length(), FirstY+3 + vtY);
					break;
				}
				break;
			}else break;
			case CtrlF: {					
				veBangChuyenBayConVe();
				check = TimKiemTheoDiaDiemVaThoiGian(First, chuoiTG, x_chuyenBay, y_chuyenBay); 
				if (check==-1){
					xoaTrang_CB(x_chuyenBay, y_chuyenBay);
					vtY=1;
					gotoxy(SecondX+16+chuoiTG[3].length(), FirstY+3 + vtY);
					break;
				}
			}
			case ESC: {
				xoabang(SecondX-1,FirstY, 30, 130); 
				return; 
			} 
			default:
				switch (vtY){
					case 0: {
					if (vtX == 0){
						if (kytu==BACKSPACE){
							if(chuoiTG[0].length() > 0)
							{
								gotoxy(SecondX+16 + vtX*4 + chuoiTG[0].length()-1, FirstY+3+ vtY); cout << " ";
								gotoxy(SecondX+16 + vtX*4 + chuoiTG[0].length()-1, FirstY+3+ vtY);
								chuoiTG[0] = chuoiTG[0].substr(0, chuoiTG[0].length()-1);
							}	
						}else if((kytu >= 48 && kytu <= 57) && chuoiTG[0].length()<2) //Lay so
						{
							chuoiTG[0]+=kytu;
							cout << kytu;
						}
					}else if (vtX == 1){
						if (kytu==BACKSPACE){
							if(chuoiTG[1].length() > 0)
							{
								gotoxy(SecondX+16 + vtX*4 + chuoiTG[1].length()-1, FirstY+3+ vtY); cout << " ";
								gotoxy(SecondX+16 + vtX*4 + chuoiTG[1].length()-1, FirstY+3+ vtY);
								chuoiTG[1] = chuoiTG[1].substr(0, chuoiTG[1].length()-1);
							}	
						}else if((kytu >= 48 && kytu <= 57) && chuoiTG[1].length()<2) //Lay so
						{
							chuoiTG[1]+=kytu;
							cout << kytu;
						}
					}else if (vtX == 2){
						if (kytu==BACKSPACE){
							if(chuoiTG[2].length() > 0)
							{
								gotoxy(SecondX+16 + vtX*4 + chuoiTG[2].length()-1, FirstY+3+ vtY); cout << " ";
								gotoxy(SecondX+16 + vtX*4 + chuoiTG[2].length()-1, FirstY+3+ vtY);
								chuoiTG[2] = chuoiTG[2].substr(0, chuoiTG[2].length()-1);
							}	
						}else if((kytu >= 48 && kytu <= 57) && chuoiTG[2].length()<4) //Lay so
						{
							chuoiTG[2]+=kytu;
							cout << kytu;
						}
					}	
				}break;
					case 1: {
					if (kytu==BACKSPACE){
						if(chuoiTG[3].length() > 0)
						{
							gotoxy(SecondX+16 + chuoiTG[3].length()-1, FirstY+3+ vtY); cout << " ";
							gotoxy(SecondX+16 + chuoiTG[3].length()-1, FirstY+3+ vtY);
							chuoiTG[3] = chuoiTG[3].substr(0, chuoiTG[3].length()-1);
						}	
					}else if((kytu >= 65 && kytu <= 90) || kytu == 32)  // chu in hoa va dau cach 
					{
						chuoiTG[3]+=kytu;
						cout << kytu;
					} else if (kytu >= 97 && kytu <= 122) 	// chu thuong can chuan hoa 
					{
						kytu = kytu - 32;
						chuoiTG[3]+=kytu;
						cout << kytu;
					}
					
					break;
				}
			}
		}
	}while (1);
}
//g. In danh sach ghe con trong cua chuyen bay X
void xuat_DSVe_CBX (PTRCB First, int viTri, int trangSo, int soluong, int CB_g[]){
	PTRCB p = nodepointer(First, CB_g[viTri+trangSo*15]);
	gotoxy (x_chuyenBay-1, y_chuyenBay-2);
	cout<<"DANH SACH CAC VE CON TRONG CHUYEN BAY "<<p->data.maCB;
	veHop(x_chuyenBay-1,y_chuyenBay+1, 90, 15, 15, 1, "Danh sach ghe ngoi" );
	veHop (x_chuyenBay-1, y_chuyenBay+17, 90, 3, 15, 0, "");
	gotoxy (x_chuyenBay, y_chuyenBay+18);
	cout<<"     x : ve da duoc dat   "; 
	gotoxy (x_chuyenBay, y_chuyenBay+19);
	cout<<"     so: ve con trong     "; 
	gotoxy (SecondX+1, FirstY+3);
	cout<< td_chuyen_bay[0]<<p->data.maCB;
	gotoxy (SecondX+1, FirstY+4);
	cout<< td_chuyen_bay[1]<<p->data.sanBayDen;
	gotoxy (SecondX+1, FirstY+5);
	cout<< td_chuyen_bay[2]<<p->data.thoiGian.date.ngay<<"/"<<p->data.thoiGian.date.thang<<"/"<<p->data.thoiGian.date.nam;
	gotoxy (SecondX+1, FirstY+6);
	cout<< td_chuyen_bay[3]<<p->data.thoiGian.h.gio<<":"<<p->data.thoiGian.h.phut;
	gotoxy (SecondX+1, FirstY+7);
	cout<< td_chuyen_bay[4]<<p->data.trangThai;
	gotoxy (SecondX+1, FirstY+8);
	cout<< td_chuyen_bay[5]<<p->data.soHieuMB;
	gotoxy (SecondX+1, FirstY+9);
	cout<< td_chuyen_bay[6]<<p->data.ve.SoVeMax-p->data.ve.SoVeDaDat;
	int soChoNgoi = p->data.ve.SoVeMax; 
	int so_hang =  (p->data.ve.SoVeMax)/20; 
	if ((p->data.ve.SoVeMax)%20 != 0) {
		so_hang = so_hang+1; 
	}
	int cho=1; 
	char KyTu;
	string str = "";
	for (int j = 1; j <= so_hang; j++) {
		gotoxy (x_chuyenBay,y_chuyenBay+4+j);
		 for (int i=cho; i<=j*20;i++) {
		 	if (i > p->data.ve.SoVeMax) break;
		 	if (str.compare(p->data.ve.danhSach[i-1].cmnd)==0) {
				if (i<10) {
		 			cout<<"   "<<i;
		 			continue;
				 } 
		 		cout<<"  "<<i;
		 		continue;
			 }
			 else cout<<"   x";
		 	
		 }
		 cho = j*20+1;
	}
	do {
			KyTu = GetKey();
			if (KyTu == ESC) {
		  		xoabang(x_chuyenBay-1, y_chuyenBay-3,29,100);
		  		xoabang(SecondX, FirstY,10, 32);
		  		veMenu_CB_DSVe ();
				duLieu_CB_DSVe(First, x_chuyenBay, y_chuyenBay, 0, soluong, CB_g) ; 
				return;
			}
	} while (1);	
}
void inDSVe_theoCBX (PTRCB First) {
		in_huong_dan(1, 0);
		in_huong_dan(2, 1);
		in_huong_dan(3, 2);
		in_huong_dan(4, 8);
		int CB_g[100]; // mang luu lai vi tri cua chuyen bay con ve  
		int vitri = 0;
		int soluong = 0; 
		for (PTRCB p = First; p!=NULL; p=p->next) {
		vitri++; 
			if (p->data.trangThai == 1) {
					CB_g[soluong]=vitri; // tinh theo 1,2,3,4... 
					soluong++;
			}
		}
	veMenu_CB_DSVe ();
	duLieu_CB_DSVe(First, x_chuyenBay, y_chuyenBay, 0, soluong, CB_g) ;
	int chon=0, trangSo=0;  
	int check=0;
	int kiemTra=0;
	int temp = soluong; 			
	int maxPage = temp/15;
	if (temp%15 != 0)
		maxPage++;  
	gotoxy(ThirdX-8+35, FirstY+21);
	cout << trangSo+1;
	gotoxy(ThirdX-3+35, FirstY+21);
	cout << maxPage;
	char kytu;
	gotoxy(SecondX+1, FirstY+chon);
	xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB_g); 
	do{
		kytu = GetKey();
		switch (kytu){
			case UP: if (chon+1>1){
              		xuLy1Dong_CB_DSVe(First, chon, trangSo, 0, soluong, CB_g);
              		chon --;
              		xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB_g);
				}
				break;
			case DOWN: if (chon+1 <maxRow){
              		xuLy1Dong_CB_DSVe(First, chon, trangSo, 0, soluong, CB_g);
              		chon ++;
              		if (xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB_g)==0){
              			chon--;
              			gotoxy(SecondX+1,FirstY+chon);
              			xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB_g);
					}
  			  	}
  			  	break;
  			case LEFT: if (trangSo+1>1){
  					xoaTrang_CB_DSVe(x_chuyenBay, y_chuyenBay);
  					trangSo--;
  					chon=0;
  					duLieu_CB_DSVe(First, x_chuyenBay, y_chuyenBay, trangSo, soluong, CB_g);
					xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB_g);
  				}
  				break;
  			case RIGHT: if (trangSo+1<maxPage){
  					xoaTrang_CB_DSVe(x_chuyenBay, y_chuyenBay);
  					trangSo++;
  					chon=0;
  					duLieu_CB_DSVe(First, x_chuyenBay, y_chuyenBay, trangSo, soluong, CB_g);
  					xuLy1Dong_CB_DSVe(First, chon, trangSo, 1, soluong, CB_g);
  				}
  				break;
			case ENTER: {
				show_cur(0); 
				xoabang(x_chuyenBay-1, y_chuyenBay-3,29,100  );
				xuat_DSVe_CBX (First, chon, trangSo, soluong, CB_g);
              	break;
            }
  			case ESC: 
			  {
			  		xoa_huong_dan();
			  		xoabang(x_chuyenBay-1, y_chuyenBay-3,29,100);
			  		xoabang(SecondX, FirstY,25,40);
			 		return;
				}
		}
	}while (1);		
} 

int khoiDong (DanhSachMB &danhSachMB, PTRCB &First, NODEPTR &root){
	resizeConsole(1300,700);
	SetColor(10);
	//Tieu de to
	gotoxy(30, 0); cout << "                 ###                    #                                 #  #";
	gotoxy(30, 1); cout << "                   #                   #                                 # ##";
	gotoxy(30, 2); cout << " ####   #    #   ###   ##    #   #   #   #    ####  #    # #    # #   # ##### ##    #   #####    ###  #   #";
	gotoxy(30, 3); cout << "# #  #  #    #  #   #  # #   #   #   #   #   #    # #    # #    # #   # #     # #   #   #    #  #   # #   #";   
	gotoxy(30, 4); cout << "#  ###  #    #  #####  #  #  #   #    # #    #      ###### #    #  # #  ##### #  #  #   ######  #####  # #";
	gotoxy(30, 5); cout << "#    #  #    # #     # #   # #   #     #     #    # #    # #    #   #   #     #   # #   #    # #     #  #";
	gotoxy(30, 6); cout << " #### ## ####  #     # #    ##   ##### #      ####  #    #  ####    #   ##### #    ##   #####  #     #  #";
	
	SetColor(9);
	gotoxy(145, 5); cout << "Ha Huu Nhan - N18DCCN136";
	gotoxy(145, 6); cout << "Le Thi Thu Huong - N18DCCN088";
	veHop(0, 7, 175, 0, 15, 0, "");
	int maxPage = danhSachMB.n/15;
	if (danhSachMB.n%15 != 0)
		maxPage++;
	int luaChon = 0, thoat=0;
	char kytu;								
	do{
		luaChon = menuNgoai(mnNgoai);
		
		switch(luaChon){
			case 1:{
				veMenuMayBay();
				do{
					resetMenuMayBay(SecondX+ 50,FirstY);
					duLieuMayBay(danhSachMB, SecondX + 50, FirstY,0, maxPage);
					thoat = menuMayBay (danhSachMB, First);
					if (thoat == -1)
					{
						xoabang(SecondX+50, FirstY, 22, 70);
						break;
					}
				}while (1);
			}
			break;
			case 2:{
				do{
					thoat = QuanLyChuyenBay(First, danhSachMB);
					if (thoat == -1)
					{
						break;
					}
				}while (1);	
			}
			break;
			case 3:{
				do{
					thoat = QuanLyVe(First, root);
					if (thoat == -1)
					{
						break;
					}
				}while (1);	
			}
			break;
			case 4: {
				do{	
				thoat =  inDSVe(First, root); 
					if (thoat == -1)
					{
						break;
					}
				}while (1);	
			} break; 
			case 5: {
				nhapChuyenBayConVe(First);
				break; 
			}
			case 6: {	
				inDSVe_theoCBX(First); 
				break;
			}
			case 7:{
				thuHoiMayBay(danhSachMB);
				clearlist(First);
				return 0;
			}
		}
	}while(1);
}
