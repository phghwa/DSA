#include <iostream>

using namespace std;

// Định nghĩa node
struct Node {
    int value;     // Giá trị của node
    Node* left;    // Con trái
    Node* right;   // Con phải
    int height;    // Chiều cao của node

    Node(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
};

// Kiểm tra cây rỗng
bool isEmpty(Node* root) {
    return root == nullptr;
}

// Lấy chiều cao của node
int height(Node* node) {
    return node ? node->height : 0;
}

// Lấy chỉ số cân bằng của node
int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Cây lệch trái -> xoay phải
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Cây lệch phải -> xoay trái
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Thêm node
Node* insert(Node* node, int value) {
    if (node == NULL)
        return new Node(value);

    // Nếu nhỏ hơn cha, thêm vào bên phải
    if (value < node->value)
        node->left = insert(node->left, value);

    // Nếu lớn hơn cha, thêm vào bên trái
    else if (value > node->value)
        node->right = insert(node->right, value);

    // Nếu trùng với cha, thêm vào bên trái
    else {
        node->left = insert(node->left, value);
    }

    // Cập nhật chiều cao của node hiện tại
    node->height = 1 + max(height(node->left), height(node->right));

    // Lấy chỉ số cân bằng
    int balance = getBalance(node);

    // Xoay đơn
    if (balance > 1 && value < node->left->value)
        return rightRotate(node);

    // Xoay đơn
    if (balance < -1 && value > node->right->value)
        return leftRotate(node);

    // Xoay kép
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Xoay kép
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Ko bị mất cân bằng -> ko cần xoay
}

// Duyệt trước (Pre order)
void preOrder(Node* root) {
    if (root) {
        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int values[] = {17, 23, 201, 93, 67, 83, 13, 23, 10, 191, 84, 58};

    for (int value : values) {
        root = insert(root, value);
    }

    cout << "Duyet cay AVL da xay dung theo kieu tien to: \n";
    preOrder(root);

    return 0;
}
