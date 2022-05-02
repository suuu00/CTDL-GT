#pragma once
//#include "huonglib.h"// 
//#ifndef _NGAY_GIO_h
//#define _NGAY_GIO_h
//#include "CauTruc.h" 

int Thang31[] = { 1,3,5,7,8,10,12 };//7
int Thang30[] = { 4,6,9,11 };//4
bool Thang30Ngay(int thang) {
    bool tmp = false;
    for (int i = 0; i < 4; i++) {
        if (thang = Thang30[i])tmp = true;
    }
    if (tmp)return true;
    return false;
}
bool Thang31Ngay(int thang) {
    bool tmp = false;
    for (int i = 0; i < 7; i++) {
        if (thang = Thang31[i])tmp = true;
    }
    if (tmp)return true;
    return false;
}
bool NgayHopLe(Date date) {
   
    if (date.thang < 1 || date.thang>12)return false;
    if (date.ngay < 1 || date.ngay>31)return false;
    if (date.nam % 4 == 0) {
        if (date.thang == 2 && date.ngay > 29)return false;
    }
    else {
        if (date.thang == 2 && date.ngay > 28)return false;
    }
    for (int i = 0; i < 4; i++) {
        if (Thang30[i] == date.thang && date.ngay > 30)return false;
    }
    return true;
}
bool GioHopLe(Hour h) {
    if (h.gio < 0 || h.gio>24)return false;
    if (h.phut < 0 || h.phut>59)return false;
    return true;
}
void NhapNgay(Date &date) {
    do {
        cin >> date.ngay >> date.thang >> date.nam;
        if (!NgayHopLe(date))cout << "Ngay thang nam khong hop le,yeu cau nhap lai: ";
    } while (!NgayHopLe(date));
}
void NhapGio(Hour& h) {
    do {
        cin >> h.gio >> h.phut;
        if (!GioHopLe(h))cout << "Gio phut khong hop le,yeu cau nhap lai: ";
    } while (!GioHopLe(h));
}
Date NgayHienTai() {
    Date date;
    time_t baygio = time(0);
    tm* ltm = localtime(&baygio);
    date.nam = 1900 + ltm->tm_year;
    date.thang = 1 + ltm->tm_mon;
    date.ngay = ltm->tm_mday;
    return date;
}

Hour GioHienTai() {
    Hour h;
    time_t baygio = time(0);
    tm* ltm = localtime(&baygio);
    h.gio = ltm->tm_hour;
    h.phut = ltm->tm_min;
    return h;
}
bool SoSanhNgay(Date d1, Date d_ht )
{	
	if(d1.nam<d_ht.nam) return false;
	else if(d1.nam>d_ht.nam)return true;
	else if(d1.nam=d_ht.nam)
	{
		if(d1.thang<d_ht.thang) return false;
		else if(d1.thang>d_ht.thang) return true;
		else if(d1.thang=d_ht.thang)
		{
			if(d1.ngay<d_ht.ngay) return false;
			else if(d1.ngay>d_ht.ngay) return true; // lap chuyen bay moi cach 1 ngay so voi ngay hien tai
		}
	}
}
bool SoSanhGio(Hour h1, Hour h_ht )
{
	if(h1.gio<h_ht.gio) return false;
	else if(h1.gio>h_ht.gio) return true;
	else if(h1.gio=h_ht.gio)
	{
		if(h1.phut<h_ht.phut) return false;
		else if(h1.phut>=h_ht.phut) return true;
	}
}
bool check_Date (Date n_date)
{
	Date v = NgayHienTai(); 
	if (NgayHopLe(n_date) == false)  {
		 return false;		
	}
	if (SoSanhNgay(n_date, v) == false) {
		return false;
	}
	return true;
}
bool check_h (Hour n_hour)
{
	Hour v = GioHienTai();
	if (GioHopLe(n_hour)==false) {
		return false;
	}
	if (SoSanhGio(n_hour, v)==false) {
		return false;
	}
	return true;
}

