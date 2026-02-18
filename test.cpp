#include <iostream>

void modify(int &val){
    val = 9;
}

int& display(int &val){
    return val;
}

int main(){
    int val = 10;
    display(val) = 100;
    std::cout << val;
    return 0;
}