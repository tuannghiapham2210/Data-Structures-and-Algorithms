#include <iostream>

int main(){
    int n;
    std::cout << "How many numbers?: ";
    std::cin >> n;

    int *ptr = new int[n];

    for (int i = 0; i < n; i++){
        std::cout << "Enter a number: ";
        int x;
        std::cin >> x;
        ptr[i] = x;
    }

    for (int i = 0; i < n; i++){
        std::cout << ptr[i] << " ";
    }
    std::cout << std::endl; 
    
    return 0;
}