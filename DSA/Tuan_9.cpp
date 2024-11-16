/*Bai 1*/
#include<iostream>
#include<string>
using namespace std;
struct FolderD {
	string name; //Ten file
	long size; //Kich thuoc file
	string date; //Ngay tao file
	FolderD* next;
};
struct Filelist {
	FolderD* head = NULL; 
};

//Tao nut moi
FolderD* taonode(string ten, long kichThuoc, string ngay_tao) {
	FolderD* newfile = new FolderD; 
	newfile->name = ten;
	newfile->size = kichThuoc;
	newfile->date = ngay_tao;
	newfile->next = NULL;
	return newfile;
}

//Sao chep file - sap xep theo thu tu ngay thang nam
void copy_file(Filelist* &list, string ten, long kichThuoc, string ngay_tao) {
	FolderD* newfile = taonode(ten, kichThuoc, ngay_tao);
	FolderD* p = list->head;
	while (p && p->next && p->next->date <= ngay_tao) {
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
	FolderD* p = list.head;
	while (p) {
		tong_size += p->size;
		p = p->next;
	}	
	return tong_size;
}

//Ham xoa file co kich thuoc nho nhat
void xoa_file_min(Filelist& list) {
	FolderD* minPrev = NULL, * minNode = list.head, * prev = NULL, * cur = list.head; //minNode: gan min la nut dau tien, minPrev: nut lien truoc nut min

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
	FolderD* p = list.head;
	while (p) {
		cout << "File: " << p->name << ". Size: " << p->size << ". Date: " << p->date << endl;
		p = p->next;
	}
}
int main() {
	Filelist* fD = new Filelist;

	//Sao chep file
	copy_file(fD, "firstfile.docx", 1863, "2024-03-04");
	copy_file(fD, "secondfile.docx", 1240, "2024-11-09");
	copy_file(fD, "thirdfile.docx", 186300000, "2024-07-24"); //>32GB: se khong in ra gi

	//Danh sach file
	cout << "Danh sach file sau khi them:\n";
	print_file(*fD);

	//Tong kich thuoc cac file
	cout << "Tong kich thuoc: " << sum_size(*fD) << "KB" << endl;

	//Sao luu vao file USB 32GB
	sao_luu(*fD);

	cout << "Danh sach file sau khi sao luu la:\n";
	print_file(*fD);
	return 0;
}

//-------------------------------------------------------------------------------//

/*Bai 2*/
#include<iostream>
#include<string>
using namespace std;
struct tieng_Viet {
	string word;
	int dem;
	tieng_Viet* next;
};
struct sentences {
	tieng_Viet* head = NULL;
};
//Tao nut moi
tieng_Viet* taoNode(string w) {
	tieng_Viet* newword = new tieng_Viet;
	newword->word = w;
	newword->dem = 1;
	newword->next = NULL;
	return newword;
}
//Them tu vao cau
void them_tu(tieng_Viet*& head, string w) {
	tieng_Viet* newword = taoNode(w);
	if (head == NULL) { //Chua co nut nao
		head = newword;
	}
	else {
		tieng_Viet* p = head;
		while (p->next != NULL) { //De them tu vao cuoi cau
			p = p->next;
		}
		p->next = newword;
	}
}
//Tim tu xuat hien nhieu nhat
void find_max_app(tieng_Viet* head) {
	int maxCount = 1;
	string tuxuathiennhieunhat = "";
	tieng_Viet* p = head;
	while (p) {
		tieng_Viet* q = p->next;
		while (q) {
			if (p->word == q->word && p != q) {
				p->dem += 1;
				q->dem = -1; //De khong dem lai
			}
			q = q->next;
		}
		if (maxCount < p->dem) {
			maxCount = p->dem;
			tuxuathiennhieunhat = p->word;
		}
		p = p->next;
	}
	p = head;
	while (p) {
		if (p->dem == maxCount) {
			cout << p->word << "\n";
		} 
		p = p->next;
	}
}
//Xoa tu lay
void delete_words(tieng_Viet*& head){
	tieng_Viet* current = head;
	while (current && current->next) { //Kiem tra tu lay
		if (current->word == current->next->word) { //La tu lay
			tieng_Viet* p = current->next;
			current->next = current->next->next;
			delete p;
		}
		else { //Khong la tu lay
			current = current->next; //Chuyen toi nut tiep theo
		}
	}
}
//Dem so tu trong cau
int dem_tu_vung(tieng_Viet* head) {
	int count = 0;
	tieng_Viet* current = head;
	while (current) {
		count++;
		current = current->next;
	}
	return count;
}
//In cau hoan chinh
void print_sentence(sentences& w) {
	tieng_Viet* p = w.head;
	while (p) {
		cout << p->word << " ";
		p = p->next;
	}
}
int main() {
	sentences cau;

	them_tu(cau.head, "do");
	them_tu(cau.head, "cam");
	them_tu(cau.head, "vang");
	them_tu(cau.head, "vang");
	them_tu(cau.head, "tim");
	them_tu(cau.head, "hong");
	them_tu(cau.head, "xanh");
	them_tu(cau.head, "xanh");
	them_tu(cau.head, "den");

	cout << "Cau hoan chinh sau khi nhap la: ";
	print_sentence(cau);

	cout << "\nTong so tu: " << dem_tu_vung(cau.head) << endl;
	cout << "Tu xuat hien nhieu nhat la: \n";
		find_max_app(cau.head);
	
	delete_words(cau.head);
	cout << "Sau khi loai bo tu lay: ";
	print_sentence(cau);

	return 0;
}	