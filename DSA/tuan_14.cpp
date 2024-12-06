#include <iostream>
#include <string>
using namespace std;

// Định nghĩa node
struct Node {
    string value; // Giá trị của node
    Node* left; // Con trái
    Node* right; // Con phải

    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Kiểm tra cây rỗng
bool isEmpty(Node* root) {
    return root == nullptr;
}

// Hàm khởi tạo
Node* buildTree() {
    // Tạo các node cho biểu thức: (a*5 - b*c^6/d) + (h-f)*e^(1/2)
    Node* root = new Node("+");

    // Xây nhánh trái: (a*5 - b*c^6/d)
    Node* left = new Node("-");
    left->left = new Node("*");
    left->left->left = new Node("a");
    left->left->right = new Node("5");

    left->right = new Node("/");
    left->right->left = new Node("*");
    left->right->left->left = new Node("b");
    left->right->left->right = new Node("^");
    left->right->left->right->left = new Node("c");
    left->right->left->right->right = new Node("6");
    left->right->right = new Node("d");

    // Xây nhánh phải: (h-f)*e^(1/2)
    Node* right = new Node("*");
    right->left = new Node("-");
    right->left->left = new Node("h");
    right->left->right = new Node("f");

    right->right = new Node("^");
    right->right->left = new Node("e");
    right->right->right = new Node("1/2");

    // Gán nhánh trái và phải cho gốc
    root->left = left;
    root->right = right;

    return root;
}

// Duyệt giữa (In order)
void inOrder(Node* root) {
    if (root) {
        if (root->left || root->right) cout << "("; // Thêm dấu ngoặc nếu là toán tử
        inOrder(root->left);
        cout << root->value;
        inOrder(root->right);
        if (root->left || root->right) cout << ")";
    }
}

// Duyệt sau (Post order)
void postOrder(Node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->value << " ";
    }
}

// Duyệt trước (Pre order)
void preOrder(Node* root) {
    if (root) {
        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Thêm một node vào cây
void insertNode(Node*& root, string value) {
    if (!root) {
        root = new Node(value);
    } else {
        // Chèn vào nhánh trái nếu trống
        if (!root->left) {
            root->left = new Node(value);
        } else if (!root->right) {
            root->right = new Node(value);
        } else {
            // Nếu cả hai nhánh đều đầy, chèn đệ quy vào nhánh trái
            insertNode(root->left, value);
        }
    }
}

int main() {
    // Dựng cây biểu thức
    Node* root = buildTree();

    // In biểu thức theo kiểu trung tố
    cout << "Trung to: ";
    inOrder(root);
    cout << endl << endl;

    // In biểu thức theo kiểu hậu tố
    cout << "Hau to: ";
    postOrder(root);
    cout << endl << endl;

    // In biểu thức theo kiểu tiền tố
    cout << "Tien to: ";
    preOrder(root);
    cout << endl;

    return 0;
}
