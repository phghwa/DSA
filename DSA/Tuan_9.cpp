/*Bai 1*/
#include <iostream>
#include <string>
using namespace std;

struct FolderD {
    string name;   // Tên file
    long size;     // Kích thước file
    string date;   // Ngày tạo file
    FolderD* next; // Con trỏ tới file tiếp theo
};

struct Filelist {
    FolderD* head = nullptr; 
};

const long USB_MAX_SIZE = 32 * 1024 * 1024; // Kích thước USB mặc định: 32GB

// Tạo nút mới
FolderD* taonode(const string& ten, long kichThuoc, const string& ngay) {
    FolderD* newfile = new FolderD;
    newfile->name = ten;
    newfile->size = kichThuoc;
    newfile->date = ngay;
    newfile->next = nullptr;
    return newfile;
}

// So sánh ngày (format YYYY-MM-DD)
bool compare_date(const string& date1, const string& date2) {
    return date1 <= date2;
}

// Sao chép file - Sắp xếp theo thứ tự ngày tháng năm
void copy_file(Filelist* list, const string& ten, long kichThuoc, const string& ngay) {
    FolderD* newfile = taonode(ten, kichThuoc, ngay);
    if (!list->head || compare_date(ngay, list->head->date)) {
        newfile->next = list->head; // Thêm vào đầu
        list->head = newfile;
    } else {
        FolderD* p = list->head;
        while (p->next && compare_date(p->next->date, ngay)) {
            p = p->next;
        }
        newfile->next = p->next; // Chèn vào giữa hoặc cuối
        p->next = newfile;
    }
}

// Hàm tính tổng kích thước các file
long sum_size(const Filelist& list) {
    long tong_size = 0;
    FolderD* p = list.head;
    while (p) {
        tong_size += p->size;
        p = p->next;
    }
    return tong_size;
}

// Hàm xóa file có kích thước nhỏ nhất
void delet_min(Filelist& list) {
    if (!list.head) return; // Danh sách rỗng

    FolderD* minPrev = nullptr;
    FolderD* minNode = list.head;
    FolderD* prev = nullptr;
    FolderD* cur = list.head;

    while (cur) {
        if (cur->size < minNode->size) {
            minNode = cur;
            minPrev = prev;
        }
        prev = cur;
        cur = cur->next;
    }

    if (minPrev) {
        minPrev->next = minNode->next; // Loại bỏ minNode
    } else {
        list.head = minNode->next; // MinNode là đầu danh sách
    }
    delete minNode;
}

// Sao lưu các file vào USB <= 32GB
void paste(Filelist& list, long USB_size = USB_MAX_SIZE) {
    while (sum_size(list) > USB_size) {
        cout << "Tong kich thuoc hien tai: " << sum_size(list) << " KB. Xoa file nho nhat!" << endl;
        delet_min(list);
        if (!list.head) { // Nếu danh sách rỗng, thoát vòng lặp
            cout << "Khong ton tai file. Khong the sao luu them!" << endl;
            break;
        }
    }
}

// Hàm in danh sách các file
void print_file(const Filelist& list) {
    FolderD* p = list.head;
    if (!p) {
        cout << "Danh sach file trong." << endl;
        return;
    }

    while (p) {
        cout << "- File: " << p->name 
             << "\t Size: " << p->size << " KB" 
             << "\t Date: " << p->date << endl;
        p = p->next;
    }
    cout << endl;
}

int main() {
    Filelist* fD = new Filelist;

    // Sao chép file
    copy_file(fD, "firstfile.docx", 18700000, "2024-03-04");
    copy_file(fD, "secondfile.docx", 24000000, "2024-11-09");
    copy_file(fD, "thirdfile.docx", 1968000, "2024-07-24");

    // In danh sách file sau khi thêm
    cout << "Danh sach file sau khi them:" << endl;
    print_file(*fD);

    // In tổng kích thước các file
    cout << "Tong kich thuoc cac file: " << sum_size(*fD) << " KB" << endl;

    // Sao lưu file vào USB 32GB
    paste(*fD);

    // In danh sách file sau khi sao lưu
    cout << "Danh sach file sau khi sao luu:" << endl;
    print_file(*fD);
    return 0;
}


//-------------------------------------------------------------------------------//

/*Bai 2*/
#include<iostream>
#include<string>
using namespace std;
struct tu {
	string word;
	int dem;
	tu* next;
};
struct sentences {
	tu* head = NULL;
};
//Tao nut moi
tu* taoNode(string w) {
	tu* newword = new tu;
	newword->word = w;
	newword->dem = 1;
	newword->next = NULL;
	return newword;
}
//Them tu vao cau
void addWord(tu*& head, string w) {
	tu* newword = taoNode(w);
	if (head == NULL) { //Chua co nut nao
		head = newword;
	}
	else {
		tu* p = head;
		while (p->next != NULL) { //De them tu vao cuoi cau
			p = p->next;
		}
		p->next = newword;
	}
}
//Tim tu xuat hien nhieu nhat
void find_max_app(tu* head) {
	int maxCount = 1;
	string tuxuathiennhieunhat = "";
	tu* p = head;
	while (p) {
		tu* q = p->next;
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
void delete_words(tu*& head){
	tu* current = head;
	while (current && current->next) { //Kiem tra tu lay
		if (current->word == current->next->word) { //La tu lay
			tu* p = current->next;
			current->next = current->next->next;
			delete p;
		}
		else { //Khong la tu lay
			current = current->next; //Chuyen toi nut tiep theo
		}
	}
}
//Dem so tu trong cau
int count(tu* head) {
	int count = 0;
	tu* current = head;
	while (current) {
		count++;
		current = current->next;
	}
	return count;
}
//In cau hoan chinh
void print_sentence(sentences& w) {
	tu* p = w.head;
	while (p) {
		cout << p->word << " ";
		p = p->next;
	}
}

//Dem so tu trong cau
int dem(tu* head) {
    int dem = 0;
    tu* current = head;
    while (current) {
        dem++;
        current = current->next;
    }
    return dem;
}

int main() {
	sentences cau;

	addWord(cau.head, "do");
	addWord(cau.head, "cam");
	addWord(cau.head, "vang");
	addWord(cau.head, "vang");
	addWord(cau.head, "tim");
	addWord(cau.head, "hong");
	addWord(cau.head, "xanh");
	addWord(cau.head, "xanh");
	addWord(cau.head, "den");

	cout << "Cau sau khi nhap la: ";
	print_sentence(cau);

	cout << "\nTong so tu: " << count(cau.head) << endl;
	cout << "Tu xuat hien nhieu nhat la: \n";
		find_max_app(cau.head);
	
	delete_words(cau.head);
	cout << "Sau khi loai bo tu lay: ";
	print_sentence(cau);

	cout << "\nTong so tu vung: " << dem(cau.head) << endl;
	return 0;
}	