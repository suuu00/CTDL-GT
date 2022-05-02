int timMayBayTrongChuyenBay(PTRCB First, string soHieu)
{
   PTRCB p;
   p = First;
   if(p == NULL){
   		printf("\n   (Khong co chuyen bay nao trong danh sach)");
   		return 0;
   }
      
   while(p != NULL)
   {
      	if (soHieu.compare(p->data.soHieuMB)==0)
      		return 1;
       	p = p->next;
   }
   return 0;
}

void Insert_nodeTree (NODEPTR &p, string x, HanhKhach info)
{ 
	if(p == NULL)    // nút p hi?n t?i s? là nút lá
	{	
	    p = new nodeHanhKhach;
	    p->data.cmnd = x;      p->data = info;
	    p->left = NULL;     p->right = NULL;  
	}
	else if (x.compare(p->data.cmnd) == 0)	cout << "So cmnd bi trung";
	else if(x.compare(p->data.cmnd) < 0 ) Insert_nodeTree(p->left, x, info);

	else if(x.compare(p->data.cmnd) > 0 ) Insert_nodeTree(p->right, x, info);
}
void Create_Tree(NODEPTR &root)
{ 
  	string khoa;
	HanhKhach noidung;
  	do
  	{ 
	  	printf("Nhap CMND:");
        cin >> khoa;
        if (khoa.compare("")!=0)
    	{
         	printf("Nhap ho:");
        	cin >> noidung.ho;
        	printf("Nhap ten:");
        	cin >> noidung.ten;
        	printf("Nhap gioi tinh:");
        	cin >> noidung.phai;
         	Insert_nodeTree(root, khoa, noidung);
     	}
   	} while (khoa.compare("")!=0); 
}
void Inorder(NODEPTR p)
{ 
	if(p != NULL)    
  	{	 
	  	Inorder(p->left);
      	cout << p->data.cmnd << " " <<  p->data.ho << " " << p->data.ten << " " << p->data.phai << endl;
      	Inorder(p->right);
   	}
}
int CountNode(NODEPTR root) {
   	if( root == NULL)
		return 0;
   	else
		return 1 + CountNode(root->left) + CountNode(root->right);
}
void Intrav(NODEPTR root, ofstream &fout)
{  
	const int STACKSIZE = 500;
	NODEPTR Stack[STACKSIZE];
	NODEPTR p=root;
	int sp=-1;	 // Khoi tao Stack rong
	do
	{ 
		while (p != NULL){	 
			Stack[++sp]= p;
		 	p= p->left;
	    }
	    if (sp != -1){	 
			p=Stack[sp--];
			fout << p->data.cmnd << '|' << p->data.ho << '|' << p->data.ten << '|';
			if (p->data.phai==0)
				fout << "Nam";
			else if(p->data.phai==1)
				fout << "Nu";
			fout << endl;
			p=p->right;
	    }
	    else break;
	}while (1);
}

NODEPTR SearchTree (NODEPTR root, string x)
{
   	NODEPTR p;
	p = root;
	while (p != NULL && p->data.cmnd.compare(x) != 0){
		if(x.compare(p->data.cmnd) < 0)
	    	p = p->left;
		else
			p = p->right;
	}
	return p; 
}
