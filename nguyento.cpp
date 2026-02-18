#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>

using namespace std;

//hàm kiểm tra số nguyên tố
bool is_prime(int n){
    if(n < 2){
        return false;
    }
    for (int i = 2; i*i <= n; i ++){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

const int MAX = 1000001;

int check[MAX];

//sàng nguyên tố eratosthenes
void sieve(){
    // ban đầu, coi tất cả các số là số nguyên tố
    for(int i = 0; i <= MAX; i++){
        check[i] = 1;
    }
    //loại thủ công 0 và 1
    check[0] = check[1] = 0;
    // duyệt từ 2 cho đến căn bậc 2 của MAX
    for(int i = 2; i*i <= MAX; i++){
        //nếu số đó là số nguyên tố
        if(check[i]){
            //loại bỏ tất cả các bội của nó (bắt đầu từ bình phương)
            for(int j = i*i; j <= MAX; j += i){
                check[j] = 0;
            }
        }
    }
}

//phân tích một số dưới dạng tích của các thừa số nguyên tố
void thua_so(int n){
    //nếu n không phải là số nguyên tố, thì thừa số nguyên tố của nó chắc chắn nằm trong đoạn từ [2, căn n]
    for(int i = 2; i*i <= n; i++){
        while(n % i == 0){
            cout << i << " ";
            n /= i;
        }
    }
    if (n != 1){
        cout << n << endl;
    }
}

//liệt kê các thừa số nguyên tố của một số (mỗi thừa số chỉ liệt kê 1 lần)
void liet_ke_thua_so(int n){
    for (int i = 2; i*i <= n; i++){
        bool check = false;
        while(n % i == 0){
            check = true;
            n /= i;
        }
        if (check){
            cout << i << " ";
        }
    }
    if (n != 1){
        cout << n << endl;
    }
}

//thừa số nguyên tố được liệt kê kèm theo số mũ
void liet_ke_thua_so_theo_mu(int n){
    for(int i = 2; i*i <= n; i++){
        int cnt = 0;
        while(n % i == 0){
            cnt++;
            n /= i;
        }
        if(cnt != 0){
            cout << i << "(" << cnt << ")" << " ";
        }
    }
    if(n != 1){
        cout << n << "(" << 1 << ")" << endl;
    }
}

void thua_so4(int n){
    for(int i = 2; i*i <= n; i++){
        while(n % i == 0){  
            n /= i;
            if (n != 1){
                cout << i << "x";
            }
            else{
                cout << i << endl;
            }
        }
    }
    if(n != 1){
        cout << n << endl;
    }
}

void thua_so5(int n){   
    cout << n << " =" << " ";
    for(int i = 2; i <= n; i++){
        int cnt =  0;
        while(n % i == 0){
            cnt++;
            n /= i;
        }
        if(cnt != 0 && n != 1){
            cout << i << "^" << cnt << " " << "*" << " ";
        }
        else if (cnt != 0 & n == 1){
            cout << i << "^" << cnt << endl;
        }
    }
}

int divisor_counter(int n){
    int cnt = 0;
    for (int i = 1; i*i <= n; i++){
        if(n % i == 0){
            if(i != n / i){
                cnt+=2;
            }
            else{
                cnt++;
            }
        }
    }
    return cnt;
}

int sum_of_divisors(int n){
    int s = 0;
    for(int i = 1; i*i <= n; i++){
        if (n % i == 0){
            if(n / i == i){
                s += i;
            }
            else{
                s += (i + n / i);
            }
        }
    }
    return s;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    for(int i = 0; i < t; i++){      
        int n; cin >> n;
        cout << sum_of_divisors(n) << endl;
    }
}