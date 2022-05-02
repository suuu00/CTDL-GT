#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;



int Empty(ListMB &ds)
{     return ds.n==0 ;
}

int Full(ListMB ds)
{ 
return ds.n==MAXMB ;
}

int Insert_item(ListMB &ds, int i, MayBay *info)
{  
	int j; 
	if (i < 0 || i > ds.n || Full(ds))
		return 0;
	for(j = ds.n -1; j >= i; j--){
		ds.nodes[j+1] = ds.nodes[j];	
	}
	ds.nodes[i] = new MayBay;
	*ds.nodes[i] = *info;
	ds.n ++;
	return 1;
}
int Delete_item (ListMB &ds, int i)
{
	int j;
	if(i < 0 || i >= ds.n || ds.n==0) return 0;
	for(j = i+1;  j< ds.n ; j++)
		ds.nodes[j-1] = ds.nodes[j];
	ds.n--;
	return 1; 
}
void thuHoiMayBay (ListMB &ds){
	for(int i = 0; i < ds.n; i++)
		delete ds.nodes[i];
}

int CheckTrungMaMayBay(ListMB &ds, string info)
{
	for ( int i =0 ; i <ds.n ; i++)
  	    if ((ds.nodes[i]->soHieuMB).compare(info)==0) return i; 
	return -1;
}

