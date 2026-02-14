#include <bits/stdc++.h>

using namespace std;

struct Node{
    int data;
    Node* next;
    Node(int val){  //constructor
        data = val;
        next = nullptr;
    }
};

Node* head; // global variable, can be accessed everywhere

void insert(int x){ // inserting the number x into the linked list (appending)
    Node* temp = new Node(x);
    if (head == nullptr){ //if the list is empty
        head = temp;
        return;
    }
    Node* scout = head;
    while (scout -> next != nullptr){
        scout = scout -> next;
    }
    scout -> next = temp;
} // done reading

void insert2(int x){ // inserting the number x into the linked list (prepending)
    Node* temp = new Node(x);
    temp -> next = head;
    head = temp;
} // done reading

void insert3(int x, int n){ //inserting a node at nth position (starts at 0)
    Node* temp = new Node(x);
    if (n == 0){
        temp -> next = head;
        head = temp;
        return;
    }
    Node* scout = head;
    for (int i = 0; i < n - 1; i++){
        if (scout == nullptr){
            cout << "index out of range" << endl;
            delete temp;
            return;
        }
        scout = scout -> next;
    }
    if (scout == nullptr){
        cout << "index out of range" << endl;
        delete temp;
        return;
    }
    temp -> next = scout -> next;
    scout -> next = temp;
} // done reading at 10:43pm

void deleteNode(int x){
    Node* temp = head;
    if (temp == nullptr){ //if the list is empty
        return;
    }
    if (temp -> data == x){ //if you wanna delete the head
        head = temp -> next;
        delete temp;
        return;
    }
    Node* pre = nullptr;
    while(temp != nullptr && temp -> data != x){
        pre = temp;
        temp = temp -> next;
    }
    if (temp == nullptr){
        cout << "value not found!" << endl;
        return;
    }
    pre -> next = temp -> next;
    delete temp;
} // done reading

void ReverseIteration(){  //reversing the list using iteration (coded again at 10:16pm)
    Node* curr = head;
    Node* prev = nullptr;
    Node* next;
    while (curr != nullptr){
        next = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

void ReverseRecursion(Node* p){ //reversing the list using recursion (coded again at 7:57pm)
    if (p == nullptr){
        return;
    }
    if (p -> next == nullptr){
        head = p;
        return;
    }
    ReverseRecursion(p -> next);
    p -> next -> next = p;
    p -> next = nullptr;
}

void printIteration(){ // printing all the values of all the nodes in the list (iteration) (coded again at 10:27pm)
    Node* temp = head;
    while (temp != nullptr){
        cout << temp -> data << " ";
        temp = temp -> next;
    }
    cout << endl;
}

void printRecursion(Node* head){ //recursively printing all the values in a list (coded again at 10:24pm)
    if (head == nullptr){
        cout << endl;
        return;
    }
    cout << head -> data << " ";
    printRecursion(head -> next);
}

void ReversePrint(Node* head){ //printing in reverse (coded again at 10:34pm)
    if (head == nullptr){
        return;
    }
    ReversePrint(head -> next);
    cout << head -> data << " ";
}

int main(){
    head = nullptr;
    cout << "how many numbers?: ";
    int n; cin >> n;
    for (int i = 0 ; i < n; i++){
        cout << "enter the number: ";
        int x; cin >> x;
        cout << "enter the position: ";
        int pos; cin >> pos;
        insert3(x, pos);
    }
    printIteration();
    return 0;
}