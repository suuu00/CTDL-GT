void saveMayBay (DanhSachMB &danhSachMB) //Luu mang tuyen tinh con tro -> Danh sach dau Sach
{
	ofstream fout;
	fout.open("DSMB.txt", ios_base::out);
	fout << danhSachMB.n << endl;
	for (int i = 0; i < danhSachMB.n; i++)
	{
		fout << danhSachMB.nodes[i]->soHieuMB << '|'
		     << danhSachMB.nodes[i]->loaiMB << '|'
		     << danhSachMB.nodes[i]->soCho << endl;
	}
	fout.close();
} 
void GhiFileChuyenBay (PTRCB &First)
{
	PTRCB p; 
	ofstream fout;
	fout.open("DSChuyenBay.txt", ios_base::out);
	p=First; 
	string str = "";
	for (p = First; p!=NULL; p=p->next)
	{
		fout<< p->data.maCB<<endl;
		fout<< p->data.sanBayDen<<endl;
		fout<< p->data.thoiGian.h.gio<<" "<< p->data.thoiGian.h.phut<<" "<< p->data.thoiGian.date.ngay<<" "<<p->data.thoiGian.date.thang<<" "<< p->data.thoiGian.date.nam<<endl; 
		fout<< p->data.trangThai<<endl;	 
	    fout<< p->data.soHieuMB<<endl;
		fout<< p->data.ve.SoVeMax<<" "<< p->data.ve.SoVeDaDat<<" "; 
		for (int i=0; i<p->data.ve.SoVeMax; i++) {
			if (str.compare(p->data.ve.danhSach[i].cmnd) != 0) {
				fout << i+1 <<","<<p->data.ve.danhSach[i].cmnd<<",";
			}
		}
	    if (p->next != NULL) fout<<endl;  
	}
	fout.close(); 
}
void saveHanhKhach(NODEPTR root) //Ghi file HanhKhach.txt
{
	string temp;
	ofstream fout;
	int n=0;
	fout.open("HanhKhach.txt", ios_base::out);
	n = CountNode(root);
	fout << n << endl;
	Intrav(root, fout);
	fout.close();
}
 
