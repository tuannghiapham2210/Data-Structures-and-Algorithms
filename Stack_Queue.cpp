//coded by Pham Tuan Nghia (25021912)
//QH-2025-I/CQ-I-CS2 (UET - VNU)

#include <iostream>
#include <stdexcept>

//-------------------- ARRAY-BASED STACK --------------------
class ArrayStack {
    private:
        int* array;
        int capacity;
        int top; //tracks the index of the top element

    public:
        //constructor: initializes an array with a given size, sets top to -1 (Empty) 
        ArrayStack(int size = 100) {
            array = new int[size];
            capacity = size;
            top = -1;
        }

        //destructor: free the dynamically allocated memory
        ~ArrayStack() {
            delete[] array;
        }

        //returns true if the stack is empty, false otherwise
        bool isEmpty() const {
            return top == -1;
        }

        //returns true if the stack is full, false otherwise
        bool isFull() const {
            return top == capacity - 1;
        }

        //adds a value to the top of the stack
        //should throw overflow_error if the stack is full
        void push(int val) {
            if (isFull()){
                throw std::overflow_error("stack is full, can't push");
            }
            ++top;
            array[top] = val;
        }

        //removes and returns the top element
        //should throw underflow_error if the stack is empty
        int pop(){
            if (isEmpty()){
                throw std::underflow_error("stack is empty, can't pop");
            }
            int val = array[top];
            --top;
            return val;
        }

        //returns the top element without removing it
        //should throw underflow_error if the stack is empty
        int peek() const{
            if (isEmpty()){
                throw std::underflow_error("stack is empty, can't peek");
            }
            return array[top];
        }

        //returns the size of the stack (without modifying it)
        int size() const{
            return top + 1;
        }

};

//-------------------- ARRAY-BASED QUEUE --------------------
class ArrayQueue {
    private:
        int* array;
        int capacity;
        int front; //index of the front element
        int rear;  //index of the rear element
        int count; //number of items currently in the queue

    public:
        //constructor
        ArrayQueue(int size = 100) {
            array = new int[size];
            capacity = size;
            front = 0;
            rear = -1;
            count = 0;
        }

        //destructor
        ~ArrayQueue() {
            delete[] array;
        }

        //returns true if the queue is empty, false otherwise
        bool isEmpty() const{
            return count == 0;
        }

        //returns true if the queue is full, false otherwise
        bool isFull() const{
            return count == capacity;
        }

        //returns the number of elements in the queue
        int size() const{
            return count;
        }

        //adds a value to the end of the queue
        //should throw overflow_error if the queue is full
        //uses circular array concept with modulo (%)
        void enqueue(int val){
            if (isFull()){
                throw std::overflow_error("queue is full, can't enqueue");
            }
            rear = (rear + 1) % capacity;
            array[rear] = val;

            ++count;
        }

        //removes and returns the front element
        //should throw underflow_error if the queue is empty
        //uses circular array concept with modulo (%)
        int dequeue(){
            if (isEmpty()){
                throw std::underflow_error("queue is empty, can't dequeue");
            }
            
            int val = array[front];
            front = (front + 1) % capacity;
            
            --count;
            return val;
        }

        //returns the front element but keeps it intact
        //should throw underflow_error if the list is empty
        int peek()const{
            if (isEmpty()){
                throw std::underflow_error("queue is empty, can't peek");
            }
            return array[front];
        }
};

//-------------------- LINKED LIST-BASED STACK --------------------
class LinkedListStack {
    private:
        struct Node{
            int data;
            Node* next;

            //constructor for a Node
            Node(int val): data(val), next(nullptr) {}
        };

        //no need capacity because the capacity depends on your ram
        Node* top; //points to the top of the stack
        int count; //keeps track of the size

    public:
        //constructor: initialize the top to nullptr and count to 0
        LinkedListStack(){
            top = nullptr; 
            count = 0;
        }

        //destructor: eradicates all the dynamically allocated nodes
        ~LinkedListStack(){
            while (top != nullptr){
                Node* temp = top -> next;
                delete top;
                top = temp;
            }
        }

        //returns true if the stack is empty, false otherwise
        bool isEmpty() const{
            return count == 0;
        }

        //returns the number of elements in the stack
        int size() const{
            return count;
        }

        //adds a new value to the top of the stack
        //create a new node and make it the new top
        void push(int val){
            Node* newNode = new Node(val);
            newNode -> next = top;
            top = newNode;
            
            ++count;
        }

        //eliminates and returns the top element
        //should throw underflow_error if the stack is empty
        int pop(){
            if (isEmpty()){
                throw std::underflow_error("stack is empty, can't pop");
            }

            int val = top -> data;
            Node* temp = top;
            top = temp -> next;

            delete temp;
            --count;

            return val;
        }

        //returns the top element while keeping it intact
        //should throw underflow_error if the stack is empty
        int peek() const{
            if (isEmpty()){
                throw std::underflow_error("stack is empty, can't peek");
            }

            return top -> data;
        }
};

//-------------------- LINKED LIST-BASED QUEUE --------------------
class LinkedListQueue{
    private:
        struct Node{
            int data;
            Node* next;

            //constructor for a node:
            Node(int val): data(val), next(nullptr) {}
        };

        //no capacity cuz it can grow till your ram runs out
        Node* front;
        Node* rear;
        int count;
        
    public:
        //constructor:
        LinkedListQueue(){
            front = nullptr; //initial empty state
            rear = nullptr;
            count = 0;
        }

        //destructor
        ~LinkedListQueue(){
            while (front != nullptr){
                Node* temp = front -> next;
                delete front;
                front = temp;
            }
        }

        //returns true if the queue is empty, false otherwise
        bool isEmpty() const{
            return count == 0;
        }

        //returns the number of elements in the queue
        int size() const{
            return count;
        }

        //Adds a value to the end of the queue
        //special case: if the queue is empty, both front and rear point to the new node 
        void enqueue(int val){
            Node* newNode = new Node(val);
            if (isEmpty()){
                front = newNode;
                rear = newNode;

                ++count;
                return;
            }

            rear -> next = newNode;
            rear = newNode;
            ++count;
        }

        //removes and returns the front element
        //should throw underflow_error if the queue is vacant
        int dequeue(){
            if (isEmpty()){
                throw std::underflow_error("queue is empty, can't dequeue");
            }
            
            int val = front -> data;
            Node* temp = front;
            front = temp -> next;

            if (front == nullptr){
                rear = nullptr;
            }

            delete temp;
            --count;

            return val;
        }

        //returns the front element while keeping it unspoiled
        //should throw underflow_error if the queue is vacant
        int peek() const{
            if (isEmpty()){
                throw std::underflow_error("queue is empty, can't peek");
            }
            return front -> data;
        }
};

//-------------------- TESTING FUNCTIONS FOR STACKS AND QUEUES (BOTH ARRAY-BASED AND LINKEDLIST-BASED) --------------------
//NOTE: THESE 4 TESTING FUNCTIONS BELOW WERE GENERATED USING GEMINI PRO (FOR THE PURPOSE OF VALIDATING THE FUNCTIONALITIES OF MY CODE ONLY), EVERYTHING ABOVE WERE CODED "MANUALLY" BY ME

void testArrayStack() {
    std::cout << "========== TESTING ARRAY STACK ==========" << std::endl;
    ArrayStack stack(5); // Small capacity to test overflow

    // Test 1: Empty state
    if (!stack.isEmpty()) throw std::runtime_error("FAILED: New stack should be empty.");
    if (stack.size() != 0) throw std::runtime_error("FAILED: New stack size should be 0.");

    // Test 2: Pushing
    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    if (stack.size() != 3) throw std::runtime_error("FAILED: Size should be 3.");
    if (stack.peek() != 30) throw std::runtime_error("FAILED: Top should be 30.");

    // Test 3: Popping
    if (stack.pop() != 30) throw std::runtime_error("FAILED: Popped value should be 30.");
    if (stack.pop() != 20) throw std::runtime_error("FAILED: Popped value should be 20.");
    if (stack.size() != 1) throw std::runtime_error("FAILED: Size should be 1 after pops.");

    // Test 4: Overflow
    stack.push(40);
    stack.push(50);
    stack.push(60);
    stack.push(70); // Stack is now full (5 items: 10, 40, 50, 60, 70)
    
    if (!stack.isFull()) throw std::runtime_error("FAILED: Stack should be full.");
    
    try {
        stack.push(80);
        throw std::runtime_error("FAILED: Push on full stack did not throw.");
    } catch (const std::overflow_error&) {}

    std::cout << "ArrayStack Worked!" << std::endl;
}

void testArrayQueue() {
    std::cout << "========== TESTING ARRAY QUEUE ==========" << std::endl;
    ArrayQueue queue(3); // Tiny capacity to force wrap-around easily

    // Test 1: Fill it up
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    
    if (queue.size() != 3) throw std::runtime_error("FAILED: Size should be 3.");
    if (!queue.isFull()) throw std::runtime_error("FAILED: Queue should be full.");

    // Test 2: Dequeue to make space (moves 'front' forward to index 2)
    if (queue.dequeue() != 10) throw std::runtime_error("FAILED: Dequeue should return 10.");
    if (queue.dequeue() != 20) throw std::runtime_error("FAILED: Dequeue should return 20.");
    
    if (queue.size() != 1) throw std::runtime_error("FAILED: Size should be 1.");

    // Test 3: THE CIRCULAR TEST (The magic moment)
    // Currently: front is at index 2, rear is at index 2.
    // If we enqueue now, rear MUST wrap around to index 0.
    queue.enqueue(40); // Should wrap to index 0
    queue.enqueue(50); // Should wrap to index 1
    
    if (queue.size() != 3) throw std::runtime_error("FAILED: Size should be 3 after wrap.");
    if (queue.peek() != 30) throw std::runtime_error("FAILED: Peek should be 30.");

    // Test 4: Empty it out to verify the wrap order
    if (queue.dequeue() != 30) throw std::runtime_error("FAILED: Dequeue should return 30.");
    if (queue.dequeue() != 40) throw std::runtime_error("FAILED: Dequeue should return 40 (wrapped item).");
    if (queue.dequeue() != 50) throw std::runtime_error("FAILED: Dequeue should return 50 (wrapped item).");
    
    if (!queue.isEmpty()) throw std::runtime_error("FAILED: Queue should be empty now.");

    std::cout << "ArrayQueue Worked! Circular math is flawless." << std::endl;
}

void testLinkedListStack() {
    std::cout << "========== TESTING LINKED LIST STACK ==========" << std::endl;
    LinkedListStack stack;

    // Test 1: Empty state
    if (!stack.isEmpty()) throw std::runtime_error("FAILED: New stack should be empty.");
    if (stack.size() != 0) throw std::runtime_error("FAILED: New stack size should be 0.");

    // Test 2: Pushing elements (Building the chain)
    stack.push(10);
    stack.push(20);
    stack.push(30); // Stack from top down: [30] -> [20] -> [10]

    if (stack.size() != 3) throw std::runtime_error("FAILED: Size should be 3.");
    if (stack.peek() != 30) throw std::runtime_error("FAILED: Peek should return 30.");

    // Test 3: Popping elements (LIFO check & Memory check)
    if (stack.pop() != 30) throw std::runtime_error("FAILED: First pop should be 30.");
    if (stack.peek() != 20) throw std::runtime_error("FAILED: Peek after pop should be 20.");
    if (stack.pop() != 20) throw std::runtime_error("FAILED: Second pop should be 20.");
    
    if (stack.size() != 1) throw std::runtime_error("FAILED: Size should be 1.");

    if (stack.pop() != 10) throw std::runtime_error("FAILED: Third pop should be 10.");
    
    if (!stack.isEmpty()) throw std::runtime_error("FAILED: Stack should be empty after popping all.");

    // Test 4: Exception Handling (Underflow)
    try {
        stack.pop();
        throw std::runtime_error("FAILED: Pop on empty stack did not throw.");
    } catch (const std::underflow_error&) {}

    try {
        stack.peek();
        throw std::runtime_error("FAILED: Peek on empty stack did not throw.");
    } catch (const std::underflow_error&) {}

    // Test 5: The Destructor Trap
    stack.push(100);
    stack.push(200);
    // We are intentionally leaving 200 and 100 in the stack.
    // When this function ends, the 'stack' object goes out of scope.
    // If your destructor (~LinkedListStack) is broken, your program will either
    // memory leak (silent failure) or crash right here!

    std::cout << "LinkedListStack Worked! Pointer logic and Destructor are solid." << std::endl;
}

void testLinkedListQueue() {
    std::cout << "========== TESTING LINKED LIST QUEUE ==========" << std::endl;
    LinkedListQueue queue;

    if (!queue.isEmpty()) throw std::runtime_error("FAILED: New queue should be empty.");

    // Test 1: Enqueue
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    if (queue.size() != 3) throw std::runtime_error("FAILED: Size should be 3.");
    if (queue.peek() != 10) throw std::runtime_error("FAILED: Peek should be 10.");

    // Test 2: Dequeue
    if (queue.dequeue() != 10) throw std::runtime_error("FAILED: Dequeue 1 should be 10.");
    if (queue.dequeue() != 20) throw std::runtime_error("FAILED: Dequeue 2 should be 20.");
    if (queue.dequeue() != 30) throw std::runtime_error("FAILED: Dequeue 3 should be 30.");

    if (!queue.isEmpty()) throw std::runtime_error("FAILED: Queue should be empty.");

    // Test 3: The Rear Pointer Trap (If you failed to set rear=nullptr, this breaks!)
    queue.enqueue(100);
    if (queue.peek() != 100) throw std::runtime_error("FAILED: Rear pointer wasn't repaired after emptying.");
    if (queue.dequeue() != 100) throw std::runtime_error("FAILED: Final dequeue failed.");

    std::cout << "LinkedListQueue Worked! The Final Boss is defeated!" << std::endl;
}

int main(){
    testArrayStack();
    testArrayQueue();
    testLinkedListStack();
    testLinkedListQueue();
    return 0;
}