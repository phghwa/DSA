/*
Bài 1: 
Yêu cầu bài toán: Nhập vào n đối tượng có màu đỏ (red), trắng (white) và xanh (blue), sắp xếp theo trật tự như sau: các đối tượng cùng mầu nằm kế tiếp nhau và theo thứ tự đỏ, trắng, xanh.
Input {xanh, đỏ, xanh, đỏ, đỏ, trắng, đỏ, xanh, trắng}
Output {đỏ, đỏ, đỏ, đỏ, trắng, trắng, xanh, xanh, xanh}
Gợi ý:
Có thể mã hóa các mầu bằng các số nguyên 0, 1, 2 để biểu diễn lần lượt mầu đỏ, trắng và xanh tương ứng.
Chú ý: Không sử dụng các thư viện hàm sắp xếp có sẵn để giải quyết bài toán trên khi cài đặt chương trình */

#include<iostream>
using namespace std;
//Hàm phân đoạn
void Partition(int A[], int first, int last) {
    if (first >= last) return;
    int c = A[first];

    int i = first + 1, j = last;
    while (i <= j) {
        while (A[i] <= c && i <= j) i++;
        while (A[j] > c && i <= j) j--;
        if (i < j) swap(A[i], A[j]);
    }
    swap(A[first], A[j]);
    Partition(A, first, j - 1);
    Partition(A, j + 1, last);
}
//Sắp xếp chèn
void quickSort(int A[], int N) {
    Partition(A, 0, N - 1);
}

int main() {
    string colors[] = {"xanh", "do", "xanh", "do", "do", "trang", "do", "xanh", "trang"};
    int size = sizeof(colors) / sizeof(colors[0]);
    int nums[size];

    // Chuyển đổi màu sắc thành các số nguyên tương ứng
    for (int i = 0; i < size; i++) {
        if (colors[i] == "do") nums[i] = 0;
        else if (colors[i] == "trang") nums[i] = 1;
        else nums[i] = 2;
    }

    quickSort(nums, size);

    // Chuyển đổi ngược lại các số nguyên thành màu sắc
    for (int i = 0; i < size; i++) {
        if (nums[i] == 0) cout << "do ";
        else if (nums[i] == 1) cout << "trang ";
        else cout << "xanh ";
    }
    
    return 0;
}

/*
Bài 2: Thiết kế giải thuật và cài đặt để tạo ra một mảng số nửa nguyên tố (Blum) nhỏ hơn một số N cho trước và thực hiện hai yêu cầu sau
- Tìm ra tất cả các cặp số Blum có tổng cũng là một số Blum nhỏ hơn N
- Kiểm tra xem một số Blum M có tồn tại trong dãy số Blum được tạo ra hay không. */

#include<iostream>
using namespace std;
int Boom(int a) {
	int re = 0;
	if (a < 6) {
		re = -1;
	}
	else {
		int A[1000];
		int m = 0;
		while (a % 2 == 0) {
			ar[m] = 2;
			a /= 2;
			m += 1;
		}
		for (int i = 3; i * i <= a; i += 2) {
			while (a % i == 0) {
				A[m] = i;
				a /= i;
				m += 1;
			}
		}
		if (a > 2) {
			A[m] = a;
			m += 1;
		}
		if (m == 2) {
			for (int i = 0; i < m; i++) {
				if (A[0] != A[1]) {
					re = 0;
				}
				else {
					re = -1;
				}
			}
		}
		else {
			re = -2;
		}
	}
	return re;
}
void checkBlum(int arr[], int l, int b) {
	int count = 0;
	
	for (int i = 0; i < l; i++) {
		for (int j = i + 1; j < l; j++) {
			int sum = arr[i] + arr[j];
			if (sum < b) {
				if (Boom(arr[i]) == 0 && Boom(arr[j]) == 0) {
					if (Boom(sum) == 0) {
						cout << "(" << arr[i] << ", " << arr[j] << ") ";
						count += 1;
					}
				}
			}
		}
	}
	if (count == 0) {
		cout << "Khong co cap so thoa man";
	}
}

int main() {
	int N, M;
	cin >> N >> M;
	int mang[1000];
	int bien = 0;
	cout << "Day cac so Blum nho hon " << N << " la: " << endl;
	for (int k = 6; k < N; k++) {
		if (Boom(k) == 0) {
			mang[bien] = k;
			bien += 1;
		}
	}
	for (int k = 0; k < bien; k++) {
		cout << mang[k] << " ";
	}
	cout << "\nCac cap so Blum co tong la 1 so Blum nho hon " << N << " la: " << endl;
	checkBlum(mang, bien, N);
	int j;
	for (j = 0; j < bien; j++) {
		if (mang[j] == M) {
			cout << "\nSo Blum M co ton tai trong day" << endl;
			break;
		}
	}
	if (j == bien) {
		cout << "\nKhong ton tai so Blum M trong day" << endl;
	}
	return 0;
}