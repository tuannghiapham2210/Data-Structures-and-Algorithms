//coded by Pham Tuan Nghia (25021912)
//QH-2025-I/CQ-I-CS2 (UET - VNU)

#include <iostream>
#include <string>
#include <stdexcept>

//-------------------- SINGLY LINKED LIST --------------------
template<typename T>
class SinglyLinkedList{
    private:
        struct Node{
            T data;
            Node* next;

            //constructor for a node:
            Node(const T& val): data(val), next(nullptr) {}
        };

        Node* head; //pointing to the first node
        Node* tail; //pointing to the last node
        int count; //size

    public:
        //constructor for SinglyLinkedList (creating an empty list)
        SinglyLinkedList(){
            head = nullptr;
            tail = nullptr;
            count = 0;
        }

        //destructor
        ~SinglyLinkedList(){
            while (head != nullptr){
                Node* nextNode = head -> next;
                delete head;
                head = nextNode; 
            }
            //optional
            tail = nullptr;
            count = 0;
        }

        //check if the list is empty
        bool isEmpty() const{
            return head == nullptr;
        }

        //getting the size of the list in O(1)
        int size() const{
            return count;
        }

        //adding a new node to the beginning of the list
        void pushFront(const T& val){
            Node* newNode = new Node(val);

            if (isEmpty()){
                head = newNode;
                tail = newNode;
            } else{
                newNode -> next = head;
                head = newNode;
            }

            ++count;
        }

        //adding a new node to the end of the list
        void pushBack(const T& val){
            Node* newNode = new Node(val);

            if (isEmpty()){
                head = newNode;
                tail = newNode;
            } else{
                tail -> next = newNode;
                tail = newNode;
            }

            ++count;
        }

        //removing from the start (returning the value eliminated)
        //should throw underflow_error if the list is empty
        T popFront(){
            if (isEmpty()){
                throw std::underflow_error("list is empty, can't popFront");
            } 
            
            Node* temp = head;
            T data = head -> data;

            head = temp -> next;
            delete temp;

            --count;

            if (count == 0){
                tail = nullptr;
            }

            return data;
        }

        //removing the last element (returning the value of the eradicated node)
        //should throw underflow_error if the list is empty
        T popBack(){
            if (isEmpty()){
                throw std::underflow_error("list is empty, can't popBack");
            }

            //edge case (the same logic as popFront so we call popFront)
            if (count == 1){
                return popFront();
            }

            //general case
            Node* temp = head;
            while (temp -> next != tail){
                temp = temp -> next;
            }

            T data = tail -> data;
            delete tail;

            tail = temp;
            tail -> next = nullptr;

            --count;
            return data;
        }

        //returning the first element without deleting it
        //should throw underflow_error if the list is empty
        T& front(){
            if (isEmpty()){
                throw std::underflow_error("list is empty, can't get front");
            }
            return head -> data;
        }

        //returning the last element without deleting it
        //should throw underflow_error if the list is empty
        T& back(){
            if (isEmpty()){
                throw std::underflow_error("list is empty, can't get back");
            }
            return tail -> data;
        }

        //inserting a value at a particular position (0-based index)
        //should throw out_of_range if the position is invalid
        void insert(int position, const T& val){
            if (position < 0 || position > count){
                throw std::out_of_range("position out of range, can't insert");
            }
            if (position == 0){
                pushFront(val);
                return;
            }
            if (position == count){
                pushBack(val);
                return;
            }

            Node* prev = head;
            for (int i = 0; i < position - 1; i++){
                prev = prev -> next;
            }

            Node* newNode = new Node(val);
            newNode -> next = prev -> next;
            prev -> next = newNode;

            ++count;
        }

        //removing a value at a specified position (0-based index)
        //should throw out_of_range if the position is not valid
        void remove(int position){
            if (position < 0 || position >= count){
                throw std::out_of_range("position out of range, can't remove");
            }
            if (position == 0){
                popFront();
                return;
            }
            if (position == count - 1){
                popBack();
                return;
            }

            Node* prev = head;
            for (int i = 0; i < position - 1; i++){
                prev = prev -> next;
            }

            Node* toRemove = prev -> next;
            prev -> next = toRemove -> next;

            delete toRemove;

            --count;
        }

        //finds the first occurence of a value and returns its position (0-based index)
        //returns -1 if not found
        int find(const T& val) const{
            Node* temp = head;
            int index = 0;

            while (temp != nullptr){
                if (temp -> data == val){
                    return index;
                }
                index++;
                temp = temp -> next;
            }

            return -1;
        }

        //printing out all the elements WITHOUT modifying
        //format: [element1, element2, ...., elementN]
        void display() const{
            Node* temp = head;
            std::cout << "[";
            while (temp != nullptr){
                std::cout << temp -> data;
                if (temp -> next != nullptr){
                    std::cout << ", ";
                }
                temp = temp -> next;
            }
            std::cout << "]" << std::endl;
        }
};


//-------------------- DOUBLY LINKED LIST --------------------
template <typename T>
class DoublyLinkedList{
    private:
        struct Node{
            T data;
            Node* next;
            Node* prev;

            //constructor for a node
            Node(T val): data(val), next(nullptr), prev(nullptr) {}
        };

        Node* head; //pointer to the first node
        Node* tail; //pointer to the last node
        int count;

    public:
        //constructor for DoublyLinkedList (creating an empty list)
        DoublyLinkedList(){
            head = nullptr;
            tail = nullptr;
            count = 0;
        }

        //destructor for DoublyLinkedList
        ~DoublyLinkedList(){
            while (head != nullptr){
                Node* nextNode = head -> next;
                delete head;
                head = nextNode;
            }
            //optional
            tail = nullptr;
            count = 0;
        }

        //function to check if the list is empty
        bool isEmpty() const{
            return count == 0;
        }

        //returns the size of the list
        int size() const{
            return count;
        }

        //adds an element to the front of the list (prepend)
        void pushFront(const T& val){
            Node* newNode = new Node(val);
            if (isEmpty()){
                head = newNode;
                tail = newNode;
                ++count;
                return;
            }

            newNode -> next = head;
            head -> prev = newNode;
            head = newNode;

            ++count;
        }

        //adds an element to the end of the list (append)
        void pushBack(const T& val){
            Node* newNode = new Node(val);
            if (isEmpty()){
                pushFront(val);
                return;
            }

            tail -> next = newNode;
            newNode -> prev = tail;
            tail = newNode;

            ++count;
        }

        //removes and returns the first element of the list
        //should throw underflow_error if the list is empty
        T popFront(){
            if (isEmpty()){
                throw std::underflow_error("list is empty, can't popFront");
            }

            T data = head -> data;
            Node* temp = head;
            head = temp -> next;

            if (head == nullptr){
                tail = nullptr;
            } else{
                head -> prev = nullptr;
            }

            delete temp;
            --count;

            return data;
        }

        //removes and returns the last element of the list
        //should throw underflow_error if the list is empty
        T popBack(){
            if (isEmpty()){
                throw std::underflow_error("list is empty, can't popBack");
            }

            T data = tail -> data;
            Node* temp = tail;
            tail = temp -> prev;

            if (tail == nullptr){
                head = nullptr;
            } else{
                tail -> next = nullptr;
            }
            
            delete temp;
            --count;

            return data;

        }

        //returns the first element of the list
        //should throw underflow_error if the list is empty
        T& front(){
            if (isEmpty()){
                throw std::underflow_error("list is empty, can't get front");
            }
            return head -> data;
        }

        //returns the last element of the list
        //should throw underflow_error if the list is empty
        T& back(){
            if (isEmpty()){
                throw std::underflow_error("list is empty, can't get back");
            }
            return tail -> data;
        }

        //inserts a value at a specified position (0-based index)
        //should throw out_of_range exception if the position is invalid
        void insert(int position, const T& val){
            if (position < 0 || position > count){
                throw std::out_of_range("position out of range, can't insert");
            }
            else if (position == 0){
                pushFront(val);
                return;
            }
            else if (position == count){
                pushBack(val);
                return;
            }
            
            Node* prevNode = head;
            for (int i = 0; i < position - 1; i++){
                prevNode = prevNode -> next;
            }
            
            Node* newNode = new Node(val);
            Node* nextNode = prevNode -> next;

            //wiring
            nextNode -> prev = newNode;
            newNode -> next = nextNode;

            prevNode -> next = newNode;
            newNode -> prev = prevNode;

            ++count;
        }

        //removes a value at a specified position (0-based index)
        //should throw out_of_range exception if the position is not valid
        void remove(int position){
            if (position < 0 || position >= count){
                throw std::out_of_range("position out of range, can't remove");
            }
            else if (position == 0){
                popFront();
                return;
            }
            else if (position == count - 1){
                popBack();
                return;
            }
            
            Node* prevNode = head;
            for(int i = 0; i < position - 1; i++){
                prevNode = prevNode -> next;
            }

            Node* toRemove = prevNode -> next;
            Node* successor = toRemove -> next;

            prevNode -> next = successor;
            successor -> prev = prevNode;

            delete toRemove;
            --count;

        }

        //finds and returns the first occurence of a value in the list (0-based index)
        //returns -1 if not found
        //keeps the list intact (not tampered with)
        int find(const T& val) const{
            Node* temp = head;
            int index = 0;
            while(temp != nullptr){
                if (temp -> data == val){
                    return index;
                }
                ++index;
                temp = temp -> next;
            }
            return -1;
        }

        //printing out all the elements WITHOUT modifying (forward order)
        //format: [element1, element2, ...., elementN]
        void displayForward() const{
            std::cout << "[";
            Node* temp = head;
            while (temp != nullptr){
                std::cout << temp -> data;
                if (temp -> next != nullptr){
                    std::cout << ", ";
                }
                temp = temp -> next;
            }
            std::cout << "]";
        }

        //printing out all the elements WITHOUT modifying (backward order)
        //format: [element1, element2, ...., elementN]
        void displayBackward() const{
            std::cout << "[";
            Node* temp = tail;
            while (temp != nullptr){
                std::cout << temp -> data;
                if (temp -> prev != nullptr){
                    std::cout << ", ";
                }
                temp = temp -> prev;
            }
            std::cout << "]";
        }

};

//-------------------- TESTING FUNCTIONS FOR SINGLYLINKEDLIST AND DOUBLYLINKEDLIST --------------------
//NOTE: THESE 2 TESTING FUNCTIONS BELOW WERE GENERATED USING GEMINI PRO (FOR THE PURPOSE OF VALIDATING THE FUNCTIONALITIES OF MY CODE ONLY), EVERYTHING ABOVE WERE CODED "MANUALLY" BY ME

void testSinglyLinkedList() {
    SinglyLinkedList<int> list;

    // --- TEST 1: Initialization & Empty State ---
    if (!list.isEmpty()) throw std::runtime_error("TEST FAILED: New list should be empty.");
    if (list.size() != 0) throw std::runtime_error("TEST FAILED: New list size should be 0.");

    // --- TEST 2: Pushing Elements ---
    list.pushBack(10);  // [10]
    list.pushBack(20);  // [10, 20]
    list.pushFront(5);  // [5, 10, 20]
    
    if (list.size() != 3) throw std::runtime_error("TEST FAILED: Size should be 3 after pushes.");
    if (list.front() != 5) throw std::runtime_error("TEST FAILED: Front should be 5.");
    if (list.back() != 20) throw std::runtime_error("TEST FAILED: Back should be 20.");

    // --- TEST 3: Access by Reference ---
    list.front() = 99; // [99, 10, 20]
    if (list.front() != 99) throw std::runtime_error("TEST FAILED: Failed to modify data via reference.");

    // --- TEST 4: Popping ---
    int val = list.popBack(); // [99, 10] (Returns 20)
    if (val != 20) throw std::runtime_error("TEST FAILED: popBack returned wrong value.");
    if (list.size() != 2) throw std::runtime_error("TEST FAILED: Size update after popBack is wrong.");

    val = list.popFront(); // [10] (Returns 99)
    if (val != 99) throw std::runtime_error("TEST FAILED: popFront returned wrong value.");
    if (list.size() != 1) throw std::runtime_error("TEST FAILED: Size update after popFront is wrong.");

    // --- TEST 5: Insert & Remove (Middle Operations) ---
    list.pushBack(30); // [10, 30]
    list.pushBack(50); // [10, 30, 50]
    
    // Insert at index 1 -> [10, 20, 30, 50]
    list.insert(1, 20); 
    if (list.size() != 4) throw std::runtime_error("TEST FAILED: Size wrong after insertion.");
    if (list.find(20) != 1) throw std::runtime_error("TEST FAILED: Inserted value not found at correct index.");

    // Remove at index 2 (Value 30) -> [10, 20, 50]
    list.remove(2);
    if (list.size() != 3) throw std::runtime_error("TEST FAILED: Size wrong after removal.");
    if (list.find(30) != -1) throw std::runtime_error("TEST FAILED: Removed value still found in list.");
    if (list.back() != 50) throw std::runtime_error("TEST FAILED: Tail broken after middle removal.");

    // --- TEST 6: Find ---
    if (list.find(10) != 0) throw std::runtime_error("TEST FAILED: Find(10) should return 0.");
    if (list.find(50) != 2) throw std::runtime_error("TEST FAILED: Find(50) should return 2.");
    if (list.find(999) != -1) throw std::runtime_error("TEST FAILED: Find(non-existent) should return -1.");

    // --- TEST 7: Clear the List ---
    while (!list.isEmpty()) {
        list.popFront();
    }
    if (list.size() != 0) throw std::runtime_error("TEST FAILED: List not empty after popping all.");

    // --- TEST 8: Exception Handling (Crucial!) ---
    bool exceptionCaught = false;
    
    // 8a. Pop from empty
    try {
        list.popFront();
    } catch (const std::underflow_error&) {
        exceptionCaught = true;
    }
    if (!exceptionCaught) throw std::runtime_error("TEST FAILED: popFront on empty list did not throw underflow_error.");

    // 8b. Insert out of bounds
    exceptionCaught = false;
    try {
        list.insert(100, 5); // Invalid index
    } catch (const std::out_of_range&) {
        exceptionCaught = true;
    }
    if (!exceptionCaught) throw std::runtime_error("TEST FAILED: insert out of bounds did not throw out_of_range.");

    // 8c. Remove out of bounds
    exceptionCaught = false;
    try {
        list.remove(0); // Empty list, index 0 is invalid for remove
    } catch (const std::out_of_range&) {
        exceptionCaught = true;
    }
    if (!exceptionCaught) throw std::runtime_error("TEST FAILED: remove out of bounds did not throw out_of_range.");

    // --- SUCCESS ---
    std::cout << "SinglyLinkedList Worked" << std::endl;
}

void testDoublyLinkedList() {
    std::cout << "========== TESTING DOUBLY LINKED LIST ==========" << std::endl;
    DoublyLinkedList<int> list;

    // --- TEST 1: Initialization ---
    if (!list.isEmpty()) throw std::runtime_error("FAILED: New list should be empty.");

    // --- TEST 2: PushFront & PushBack ---
    list.pushBack(20);  // [20]
    list.pushBack(30);  // [20, 30]
    list.pushFront(10); // [10, 20, 30]

    // Check size and ends
    if (list.size() != 3) throw std::runtime_error("FAILED: Size is wrong after pushes.");
    if (list.front() != 10) throw std::runtime_error("FAILED: Front is wrong.");
    if (list.back() != 30) throw std::runtime_error("FAILED: Back is wrong.");

    // --- TEST 3: Find (The One We Almost Forgot!) ---
    if (list.find(10) != 0) throw std::runtime_error("FAILED: Find(10) should be index 0.");
    if (list.find(20) != 1) throw std::runtime_error("FAILED: Find(20) should be index 1.");
    if (list.find(999) != -1) throw std::runtime_error("FAILED: Find(999) should be -1.");

    // --- TEST 4: Structural Integrity ---
    // Insert middle: [10, 15, 20, 30]
    list.insert(1, 15); 
    
    // Verify by popping from BACK (checks 'prev' pointers)
    if (list.popBack() != 30) throw std::runtime_error("FAILED: popBack (1) wrong.");
    if (list.popBack() != 20) throw std::runtime_error("FAILED: popBack (2) wrong.");
    if (list.popBack() != 15) throw std::runtime_error("FAILED: popBack (3) wrong. Insert wiring might be broken.");
    if (list.popBack() != 10) throw std::runtime_error("FAILED: popBack (4) wrong.");

    if (!list.isEmpty()) throw std::runtime_error("FAILED: List should be empty after popping all.");

    // --- TEST 5: Remove (Middle) ---
    list.pushBack(100);
    list.pushBack(200);
    list.pushBack(300); // [100, 200, 300]
    
    list.remove(1); // Remove 200 -> [100, 300]
    
    if (list.size() != 2) throw std::runtime_error("FAILED: Size wrong after remove.");
    if (list.find(200) != -1) throw std::runtime_error("FAILED: Removed item 200 still found!");
    
    // Verify backward link: 300 -> prev should be 100.
    if (list.popBack() != 300) throw std::runtime_error("FAILED: popBack after remove failed.");
    if (list.popBack() != 100) throw std::runtime_error("FAILED: The 'prev' link was not repaired after remove!");

    // --- TEST 6: Edge Cases ---
    try {
        list.popFront(); // Empty now
        throw std::runtime_error("FAILED: popFront on empty did not throw.");
    } catch (const std::underflow_error&) {}

    try {
        list.remove(0);
        throw std::runtime_error("FAILED: remove on empty did not throw.");
    } catch (const std::out_of_range&) {}
    
    std::cout << "DoublyLinkedList Worked" << std::endl;
}

int main() {
    testSinglyLinkedList();
    testDoublyLinkedList();
    return 0;
}