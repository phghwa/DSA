#include <iostream>
using namespace std;

#define SIZE 51 // 1920->1970
struct Population {
    int year;  
    int data;  
};
// cac nam co cung so nguoi sinh ra
void find_years_with_same_data(struct Population population[], int size) {
    cout << "cac nam co cung so nguoi sinh ra:\n";
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (population[i].data == population[j].data) {
                cout << population[i].year << ", " << population[i].data << "\t" << population[j].year << ", " << population[j].data << endl;
            }
        }
    }
}
// Tim min max va in ra ket qua
void find_years_min_max_data(struct Population population[], int size) {
    int min_data = population[0].data;
    int max_data = population[0].data;
    // tim min va max
    for (int i = 1; i < size; i++) {
        if (population[i].data < min_data) {
            min_data = population[i].data;
        }
        if (population[i].data > max_data) {
            max_data = population[i].data;
        }
    }
    // In ra kqua max
    cout << "cac nam co so nguoi max:\t"<< max_data << endl;
    for (int i = 0; i < size; i++) {
        if (population[i].data == max_data) {
            cout << population[i].year << ", " << population[i].data << endl;
        }
    }
    // In ra kqua min
    cout << "cac nam co so nguoi min:\t"<< min_data << endl;
    for (int i = 0; i < size; i++) {
        if (population[i].data == min_data) {
            cout << population[i].year << ", " << population[i].data << endl;
        }
    }
}
int main() {
    struct Population population[SIZE] = {
        {1920, 19}, {1921, 77}, {1922, 40}, {1923, 90}, {1924, 2}, {1925, 25}, 
        {1926, 54}, {1927, 17}, {1928, 79}, {1929, 6}, {1930, 44}, {1931, 24}, 
        {1932, 14}, {1933, 4}, {1934, 95}, {1935, 47}, {1936, 66}, {1937, 48}, 
        {1938, 23}, {1939, 98}, {1940, 15}, {1941, 86}, {1942, 25}, {1943, 50}, 
        {1944, 9}, {1945, 29}, {1946, 64}, {1947, 3}, {1948, 67}, {1949, 4}, 
        {1950, 90}, {1951, 81}, {1952, 74}, {1953, 34}, {1954, 98}, {1955, 13}, 
        {1956, 87}, {1957, 96}, {1958, 56}, {1959, 90}, {1960, 49}, {1961, 85}, 
        {1962, 94}, {1963, 66}, {1964, 19}, {1965, 95}, {1966, 47}, {1967, 42}, 
        {1968, 65}, {1969, 87}, {1970, 11}
    };
// In ra ket qua
    find_years_with_same_data(population, SIZE);
    find_years_min_max_data(population, SIZE);
    return 0;
}