#include<iostream>
#include<string>
using namespace std;
struct FileD {
	string name; //Ten file
	long size; //Kich thuoc file
	string date; //Ngay tao file
	FileD* next;
};
struct Filelist {
	FileD* head = NULL; 
};

//Tao nut moi
FileD* taonode(string ten, long kichThuoc, string ngay_tao) {
	FileD* newfile = new FileD; 
	newfile->name = ten;
	newfile->size = kichThuoc;
	newfile->date = ngay_tao;
	newfile->next = NULL;
	return newfile;
}

//Sao chep file - sap xep theo thu tu ngay thang nam
void copy_file(Filelist* &list, string ten, long kichThuoc, string ngay_tao) {
	FileD* newfile = taonode(ten, kichThuoc, ngay_tao);
	FileD* p = list->head;
	while (p && p->next && p->next->size <= kichThuoc) {
		p = p->next;
	}
	if (p) { //Kiem tra xem p co o dau hay khong
		newfile->next = p->next;
		p->next = newfile;
	}
	else {
		newfile -> next = NULL;
		list->head = newfile;
	}
}

//Ham tinh tong kich thuoc cac file
long sum_size(Filelist& list) {
	long tong_size = 0;
	FileD* p = list.head;
	while (p) {
		tong_size += p->size;
		p = p->next;
	}	
	return tong_size;
}

//Ham xoa file co kich thuoc nho nhat
void xoa_file_min(Filelist& list) {
	FileD* minPrev = NULL, * minNode = list.head, * prev = NULL, * cur = list.head; //minNode: gan min la nut dau tien, minPrev: nut lien truoc nut min

	while (cur) {
		if (cur->size < minNode->size) { 
			minNode = cur; //Gan min la nut hien tai neu nut hien tai co size < size cua minNode
			minPrev = prev; 
		}
		prev = cur; //Dich chuyen 1 nut
		cur = cur->next; //Chuyen toi nut tiep theo
	}

	if (minPrev) { //Kiem tra xem nut min co phai NULL hay khong
		minPrev->next = minNode->next; //Loai bo minNode - nut co size nho nhat 
	}
	else { //minPrev la NULL -> minNode la nut o dau
		list.head = minNode->next; //Cap nhat lai nut dau
	}
	delete minNode;	
}

//Sao luu cac file vao USB <= 32GB
void sao_luu(Filelist& list, long USB_size = 32 * 1024 * 1024) { //Mac dinh quy ve KB
	while (sum_size(list) > USB_size) {
		xoa_file_min(list);
	}
}

//Ham in danh sach cac file
void print_file(Filelist& list) {
	FileD* p = list.head;
	while (p) {
		cout << "File: " << p->name << ". Size: " << p->size << ". Date: " << p->date << endl;
		p = p->next;
	}
}
int main() {
	Filelist* fD = new Filelist;

	//Sao chep file
	copy_file(fD, "filesomot.docx", 1863, "2024-05-23");
	copy_file(fD, "filesohai.docx", 1240, "2024-11-12");
	copy_file(fD, "filesoba.docx", 186300000, "2024-07-02"); //>32GB: se khong in ra gi

	//Danh sach file
	cout << "Danh sach file sau khi them:\n";
	print_file(*fD);

	//Tong kich thuoc cac file
	cout << "Tong kich thuoc cac file la: " << sum_size(*fD) << "KB" << endl;

	//Sao luu vao file USB 32GB
	sao_luu(*fD);

	cout << "Danh sach file sau khi sao luu la:\n";
	print_file(*fD);
	return 0;
}
