#include <iostream>
#include <string>
using namespace std;

// Đồ thị số 2

// Danh sách kề

// Định nghĩa node
struct Node {
    string name;    // Tên đỉnh
    Node* next;     // Con trỏ tới đỉnh tiếp theo

    // Cấu trúc từng node
    Node(string name) {
        this->name = name;
        this->next = nullptr;  // Khởi tạo con trỏ ban đầu là nullptr
    }
};

struct Edge {
    Node* node;       // Mỗi cạnh là một node
    Edge* next;       // Con trỏ tới cạnh kề với nó

    // Định nghĩa cạnh với node đã cho
    Edge(Node* node) {
        this->node = node;   
        this->next = nullptr;  // Ban đầu con trỏ next là nullptr
    }
};

// Lưu trữ danh sách các cạnh của các đỉnh
Edge* head[10000] = {nullptr}; 

// Thêm cạnh
void addEdge(int u, string name) {
    Node* newNode = new Node(name);   // Tạo Node mới
    Edge* newEdge = new Edge(newNode);  // Tạo Edge mới từ Node

    // Thêm vào danh sách kề của đỉnh
    newEdge->next = head[u];
    head[u] = newEdge;
}

// Hiển thị danh sách kề của đồ thị
void displayAdjacencyList(int n) {
    for (int i = 1; i <= n; i++) {
        cout << "V[" << i << "]: ";
        Edge* temp = head[i];
        if (temp == nullptr) {
            cout << "Khong co dinh ke" << endl;
        } else {
            while (temp != nullptr) {
                cout << temp->node->name;
                if (temp->next != nullptr) {
                    cout << ", ";
                }
                temp = temp->next;
            }
            cout << endl;
        }
    }
}

int main () {
    // Ma trận kề
    int n = 7, m = 11;
    int a[n+1][n+1] = {0};  // Đặt giá trị mặc định là 0 (vì không có cạnh)

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        a[x][y] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    
}

//Danh sách kề

    // Khởi tạo đồ thị
    addEdge(1, "b");
    addEdge(1, "c");
    addEdge(1, "d");
    addEdge(2, "e");
    addEdge(4, "e");
    addEdge(4, "f");
    addEdge(5, "c");
    addEdge(5, "f");
    addEdge(5, "g");
    addEdge(7, "b");
    addEdge(7, "f");

    // Hiển thị danh sách kề
    displayAdjacencyList(n);

    return 0;

}
