
void loadMayBay(DanhSachMB &danhSachMB) //Doc file DauSach.txt
{
	string temp;
	ifstream fin;
	fin.open("DSMB.txt", ios_base::in);
	if (fin == NULL)
		cout << "Khong the mo file";
	fin >> danhSachMB.n;
	getline(fin, temp);
	for(int i = 0; i < danhSachMB.n; i++)
	{
		danhSachMB.nodes[i] = new MayBay;
		getline(fin, temp,'|');
		danhSachMB.nodes[i]->soHieuMB = temp;
		getline(fin, temp,'|');
		danhSachMB.nodes[i]->loaiMB = temp;
		fin >> danhSachMB.nodes[i]->soCho;
		getline(fin, temp);
	}
	fin.close();
}
// doc file DSChuyenBay.txt
void doc_thoigian (ifstream &fin, PTRCB p)  
{
	string temp;
	fin >> p->data.thoiGian.h.gio; 
	fin >> p->data.thoiGian.h.phut;
	fin >> p->data.thoiGian.date.ngay;
	fin >> p->data.thoiGian.date.thang;
	fin >> p->data.thoiGian.date.nam;
	getline (fin, temp); 
	
 } 
 void doc_danhSachVe (ifstream &fin, PTRCB p) 
 {
 	string temp;
 	char tam; 
	int so; 
	fin >>p->data.ve.SoVeMax;
	fin >> p->data.ve.SoVeDaDat; 
	p->data.ve.danhSach = new Ve[p->data.ve.SoVeMax];
	if(p->data.ve.SoVeDaDat != 0)
	{	
		for(int i=0; i<p->data.ve.SoVeDaDat;i++)
			{	int a;
				fin>>a;
				fin >> tam; 
				getline(fin, p->data.ve.danhSach[a-1].cmnd, ','); // dang sai can chinh sua 	
			}
	} 
	getline (fin, temp); 
 } 
  void LoadChuyenBay (PTRCB &First)
{
		string temp;
		char tam; 
		PTRCB Last ;
		PTRCB p ;
		p = new nodeCB;  
		ifstream fin;
		fin.open("DSChuyenBay.txt", ios_base::in);
		while(!fin.eof()) 
		{           
			getline (fin, p->data.maCB); 
	 		getline (fin, p->data.sanBayDen);
	 		doc_thoigian(fin, p);
	 		fin >> p->data.trangThai;//nay chi lay so chu khong lay enter 
	 		getline(fin, temp); // lay enter xuong dong 
			getline (fin, p->data.soHieuMB);
			doc_danhSachVe(fin, p);
			if (First==NULL)		
				First=p;
			else
				Last->next = p;
			Last=p;
			p = new nodeCB;
		}
   		fin.close(); 
}
void LoadHanhKhach(NODEPTR &root) //Doc file HanhKhach.txt
{
	string temp;
	ifstream fin;
	int n=0;
	fin.open("HanhKhach.txt", ios_base::in);
	if (fin == NULL)
		cout << "Khong the mo file Hanh Khach";
	HanhKhach info;
	fin >> n;
	getline(fin, temp);
	for (int i=0; i<n; i++){
		getline(fin, temp,'|');								
		info.cmnd = temp;
		getline(fin, temp,'|');
		info.ho = temp;
		getline(fin, temp,'|');
		info.ten = temp;
		fin >> temp;
		if (temp.compare("Nam")==0)
			info.phai = 0;
		else if (temp.compare("Nu")==0)
			info.phai = 1;
		getline(fin, temp);
		Insert_nodeTree(root, info.cmnd, info);
	}
	fin.close();
	
}

