#include <iostream>
#define MAX_PRODUCTS 100
#define MAX_CUSTOMERS 100

using namespace std;

// Lưu thông tin sản phẩm
struct Product {
    string name;
    float price;
};

// Lưu thông tin khách hàng
struct Customer {
    string name;
    Product* products[MAX_PRODUCTS];
    int quantities[MAX_PRODUCTS];
    int numProducts;
    double amount;
};

// Tạo node
struct Node {
    Customer* customer;
    Node* next;
};

// Khởi tạo hàng đợi
struct Queue {
    Node* front;
    Node* rear;
    int size;
};

Customer* processedCustomers[MAX_CUSTOMERS]; // lưu trữ thông tin khách hàng đã thanh toán
int processedCount = 0;

double totalRevenue = 0.0; // tổng tiền thu được sau phiên làm việc
int productACount = 0; // đếm số sản phẩm A đã bán

void initQueue(Queue& q) {
    q.front = q.rear = nullptr;
    q.size = 0;
}

// Kiểm tra hàng đợi rỗng
int isEmpty(Queue* q) {
    return q->front == nullptr;
}

// Kiểm tra hàng đợi đầy
int isFull(Queue* q) {
    return q->size >= MAX_CUSTOMERS;
}

// Thêm khách hàng vào hàng đợi
void enqueue(Queue& q, Customer* customer) {
    if (isFull(&q)) {
        cout << "Hang doi day, ko the them khach hang moi!" << endl;
        return;
    }
    Node* new_node = new Node{customer, nullptr};
    if (q.rear == nullptr) {
        q.front = q.rear = new_node;
    } else {
        q.rear->next = new_node;
        q.rear = new_node;
    }
    q.size++;
}

// Loại bỏ khách hàng đã thanh toán
Customer* dequeue(Queue& q) {
    if (isEmpty(&q)) {
        cout << "Hang doi trong!" << endl;
        return nullptr;
    }
    Node* temp = q.front;
    Customer* customer = q.front->customer;
    q.front = q.front->next;
    if (q.front == nullptr) {
        q.rear = nullptr;
    }
    delete temp;
    q.size--;

    if (processedCount < MAX_CUSTOMERS) {
        processedCustomers[processedCount++] = customer;
    }

    return customer;
}

// Tính toán hóa đơn
void calculateAmount(Customer* customer) {
    customer->amount = 0;
    for (int i = 0; i < customer->numProducts; i++) {
        Product* product = customer->products[i];
        int quantity = customer->quantities[i];
        double cost = product->price * quantity;
        customer->amount += cost;

        // Cộng vào tổng doanh thu
        totalRevenue += cost;

        // Kiểm tra và đếm số lượng sản phẩm A
        if (product->name == "A") {
            productACount += quantity;
        }

        
    }

}

// In hóa đơn
void printProcessedCustomers() {
    if (processedCount == 0) {
        cout << "Khong co khach hang nao da thanh toan!" << endl;
        return;
    }
    cout << "Danh sach khach hang da thanh toan:" << endl;
    for (int i = 0; i < processedCount; i++) {
        Customer* customer = processedCustomers[i];
        cout << i + 1 << ". " << customer->name << endl;
        for (int j = 0; j < customer->numProducts; j++) {
            Product* product = customer->products[j];
            int quantity = customer->quantities[j];
            double cost = product->price * quantity;
            cout << "  San pham: " << product->name
                 << " \t So luong: " << quantity
                 << " \t Gia: " << cost << " nghin dong" << endl;
        }
            cout << endl;
        cout << "  Tong tien: " << customer->amount << " nghin dong" << endl;
        cout << endl;
    }
}

int main() {
    Product products[MAX_PRODUCTS] = {
        {"A", 20.5},
        {"B", 10},
        {"C", 15},
        {"D", 4.7},
        {"E", 100},
        {"F", 500}
    };

    Queue q;
    initQueue(q);

    Customer customer1 = {"Hoa Hoa", {}, {}, 0, 0};
    customer1.products[0] = &products[0];
    customer1.quantities[0] = 2;
    customer1.products[1] = &products[2]; 
    customer1.quantities[1] = 5;
    customer1.products[2] = &products[5]; 
    customer1.quantities[2] = 1;
    customer1.numProducts = 3;

    Customer customer2 = {"Bao Bao", {}, {}, 0, 0};
    customer2.products[0] = &products[1]; 
    customer2.quantities[0] = 20;
    customer2.products[1] = &products[4]; 
    customer2.quantities[1] = 3;
    customer2.numProducts = 2;

    Customer customer3 = {"Map Map", {}, {}, 0, 0};
    customer3.products[0] = &products[0];
    customer3.quantities[0] = 2;
    customer3.products[1] = &products[2]; 
    customer3.quantities[1] = 5;
    customer3.numProducts = 2;
    
    Customer customer4 = {"Mi Mi", {}, {}, 0, 0};
    customer4.products[0] = &products[0];
    customer4.quantities[0] = 20;
    customer4.products[1] = &products[3]; 
    customer4.quantities[1] = 5;
    customer4.numProducts = 2;
    
    enqueue(q, &customer1);
    enqueue(q, &customer2);
    enqueue(q, &customer3);
    enqueue(q, &customer4);

    Customer* processedCustomer;
    while ((processedCustomer = dequeue(q)) != nullptr) {
        calculateAmount(processedCustomer);
    }

    printProcessedCustomers();
    
    cout << "\nTong ket cuoi phien: " << endl;
    cout << "Tong so tien ma thu ngan thu duoc: " << totalRevenue << " nghin dong" << endl;
    cout << "So san pham A da ban: " << productACount << endl;

    return 0;
}
