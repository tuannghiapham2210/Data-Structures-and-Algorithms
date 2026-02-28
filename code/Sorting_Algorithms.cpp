#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1000001;

int arr[MAX];

void heapify(int arr[], int n, int i){
    //assume that the parent node is the biggest
    int largest = i;
    //left child
    int l = 2 * i + 1;
    //right child
    int r = 2 * i + 2;

    if (r < n && arr[r] > arr[largest]){
        largest = r;
    }
    if (l < n && arr[l] > arr[largest]){
        largest = l;
    }

    if (largest != i){
        //swap the largest child with the parent
        swap(arr[largest], arr[i]);

        //recursively modifying the subtrees
        heapify(arr, n , largest);
    }
}

void heapSort(int arr[], int n){
    //building a max heap (heapifying all the non-leaf nodes)
    int non_leaf = n / 2 - 1;
    for (int i = non_leaf; i >=0; i--){
        heapify(arr, n, i);
    }

    //after creating a max heap, repeatedly swapping the root with the last element in the array
    for(int i = n - 1; i > 0; i--){
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

//lomuto partition
int partition(int arr[], int l, int r){
    int pivot = arr[r];
    int pointer = l - 1;
    for (int i = l; i < r; i++){
        if(arr[i] <= pivot){
            pointer++; swap(arr[i], arr[pointer]);
        }
    }
    pointer++; swap(arr[r], arr[pointer]);
    return pointer;
}

void quickSort(int arr[], int l, int r){
    if (r > l){
        int q = partition(arr, l, r);
        quickSort(arr, l, q - 1);
        quickSort(arr, q + 1, r);
    }
}


void merge(int arr[], int l, int m, int r){
    //copying the first half to vector x
    vector<int> x(arr + l, arr + m + 1);
    //copying the second half to vector y
    vector<int> y(arr + m + 1, arr + r + 1);
    //using 3 pointers
    int i = 0; int j = 0; int k = l;
    while(i < x.size() && j < y.size()){
        if(x[i] <= y[j]){
            arr[k] = x[i];
            k++; i++;
        }
        else{
            arr[k] = y[j];
            k++; j++;
        }
    }
    while(i < x.size()){
        arr[k] = x[i];
        k++; i++;
    }
    while(j < y.size()){
        arr[k] = y[j];
        k++; j++;
    }
}


void mergeSort(int arr[], int l, int r){
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0 ; i < n; i++) cin >> arr[i];
    mergeSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    return 0;
}