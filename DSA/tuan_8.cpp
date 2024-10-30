#include <iostream>
using namespace std;

struct DT {
    double *a;
    int n;    
};

// Hàm nhập đa thức
void nhapDT(DT &f) {
    cout << "Nhap bac cua da thuc: ";
    cin >> f.n;
    f.a = new double[f.n + 1]; 

    for (int i = 0; i <= f.n; i++) {
        cout << "Nhap he so cho x^" << i << ": ";
        double coeff;
        cin >> coeff;

        if (coeff != 0) {
            f.a[i] = coeff;
        } else {
            f.a[i] = 0;
        }
    }
}

// Hàm in đa thức
void inDT(const DT &f) {
    cout << "f(x) = ";
    bool firstTerm = true;

    for (int i = f.n; i >= 0; i--) {
        if (f.a[i] != 0) {
            if (!firstTerm) cout << " + ";
            cout << f.a[i];
            if (i > 0) cout << "x^" << i;
            firstTerm = false;
        }
    }
    if (firstTerm) cout << "0";
    cout << endl;
}

int main() {
    DT f, g;

 
    nhapDT(f);
    nhapDT(g);
    
    cout << "Da thuc f(x): ";
    inDT(f);

    cout << "Da thuc g(x): ";
    inDT(g);

    delete[] f.a;
    delete[] g.a;

    return 0;
}
