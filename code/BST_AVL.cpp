//coded by Pham Tuan Nghia (25021912)
//QH-2025-I/CQ-I-CS2 (UET - VNU)

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <queue>
#include <string>

//-------------------- BINARY SEARCH TREE --------------------
class BST{
    private:
        struct Node{
            int data;
            Node* left;
            Node* right;

            //constructor for a Node:
            Node(int val): data(val), left(nullptr), right(nullptr){}
        };

        Node* root;

        //implememting private helper functions

        //recursive helper function for insert function
        void insertRec(Node*& node, int val){
            if (node == nullptr){
                node = new Node(val);
                return;
            }
            if (val > node -> data){
                insertRec(node -> right, val);
            }
            else if (val < node -> data){
                insertRec(node -> left, val);
            }
        }

        //helper function to find the smallest node in a given subtree
        Node* findMin(Node* node){
            if (node == nullptr){
                return nullptr;
            } //in case the tree is empty    

            while (node -> left != nullptr){
                node = node -> left;
            }

            return node;
        }

        //recursive helper function for remove function
        void removeRec(Node*& node, int val){
            if (node == nullptr){
                return;
            }
            if (val > node -> data){
                removeRec(node -> right, val);
            }
            else if (val < node -> data){
                removeRec(node -> left, val);
            }
            else{
                if (node -> left == nullptr){
                    Node* temp = node -> right;
                    delete node;
                    node = temp;
                }
                else if (node -> right == nullptr){
                    Node* temp = node -> left;
                    delete node;
                    node = temp;
                }
                else{
                    Node* successor = findMin(node -> right);
                    node -> data = successor -> data;
                    removeRec(node -> right, successor -> data);
                }
            }
        }

        //helper function for recursive inorder traversal (in-order)
        void inorderRec(Node* node){
            if (node == nullptr){
                return;
            }

            inorderRec(node -> left);

            std::cout << node -> data << " ";

            inorderRec(node -> right);
        }

        //helper function to recursively demolish the tree (post-order)
        void clearRec(Node* node){
            if (node == nullptr){
                return;
            }

            clearRec(node -> left);

            clearRec(node -> right);

            delete node;
        }

    public:
        //constructor for the BST (empty tree initially)
        BST(): root(nullptr) {}

        //destructor for the BST (automatically called when the BST object is out of scope)
        ~BST() {
            clearRec(root);
        }

        //public API for insertion
        void insert(int val){
            insertRec(root, val);
        }

        //public API for searching
        bool search(int val){
            Node* temp = root;

            while (temp != nullptr){
                if (val == temp -> data){
                    return true;
                }
                else if (val > temp -> data){
                    temp = temp -> right;
                }
                else if (val < temp -> data){
                    temp = temp -> left;
                }
            }

            return false;
        }

        //public API for remove function
        void remove(int val){
            removeRec(root, val);
        }

        //public API for printing the tree (ascending order)
        void inorder(){
            inorderRec(root);
            std::cout << std::endl;
        }
};


//-------------------- AVL TREE --------------------
class AVLTree{
    private:
        struct Node{
            int data;
            Node* left;
            Node* right;
            int height;

            //constructor for a node:
            Node(int val): data(val), left(nullptr), right(nullptr), height(1) {}
        };

        Node* root;

        //helper function to safely get the height of a node
        int height(Node* node){
            if (node == nullptr){
                return 0;
            }
            return node -> height;
        }

        int getBalance(Node* node){
            if (node == nullptr){
                return 0;
            }
            return height(node -> left) - height(node -> right);
        }
        
        //right rotate (to fix left-heavy tree) O(1)
        Node* rightRotate(Node* y){
            Node* x = y -> left;
            Node* T2 = x -> right;

            x -> right = y;
            y -> left = T2;

            y -> height = 1 + std::max(height(y -> left), height(y -> right));
            x -> height = 1 + std::max(height(x -> left), height(x -> right));

            return x;
        }

        //left rotate (to fix right-heavy tree) O(1)
        Node* leftRotate(Node* x){
            Node* y = x -> right;
            Node* T2 = y -> left;

            y -> left = x;
            x -> right = T2;

            x -> height = 1 + std::max(height(x -> left), height(x -> right));
            y -> height = 1 + std::max(height(y -> left), height(y -> right));

            return y;
        }

        Node* insertRec(Node* node, int val){
            if (node == nullptr){
                return new Node(val);
            }
            if (val > node -> data){
                node -> right = insertRec(node -> right, val);
            }
            else if(val < node -> data){
                node -> left = insertRec(node -> left, val);
            }
            
            node -> height = 1 + std::max(height(node -> left), height(node -> right));

            int balanceFac = getBalance(node);

            //case 1: Left Left  (/)
            if (balanceFac > 1 && val < node -> data){
                return rightRotate(node);
            }
            //case 2: Right Right (\)
            else if (balanceFac < -1 && val > node -> data){
                return leftRotate(node);
            }
            //case 3: Left Right (<)
            else if (balanceFac > 1 && val > node -> data){
                node -> left = leftRotate(node -> left);
                return rightRotate(node);
            }
            //case 4: Right left (>)
            else if (balanceFac < -1 && val < node -> data){
                node -> right = rightRotate(node -> right);
                return leftRotate(node);
            }

            return node;
        }

        void inorderRec(Node* node){
            if (node == nullptr){
                return;
            }

            inorderRec(node -> left);

            std::cout << node -> data << " ";

            inorderRec(node -> right);
        }

        void clearRec(Node* node){
            if (node == nullptr){
                return;
            }

            clearRec(node -> left);

            clearRec(node -> right);

            delete node;
        }

    public:
        //constructor for an AVL tree (automatically called when an object is instantiated)
        AVLTree(): root(nullptr) {}

        //destructor for an AVL tree (automatically called when an object is out of scope)
        ~AVLTree(){
            clearRec(root);
        }

        void insert(int val){
            root = insertRec(root, val);
        }

        void inorder(){
            inorderRec(root);
            std::cout << std::endl;
        }

        bool isBalanced(){
            int balanceFac = getBalance(root);
            return balanceFac < 1;
        }

        int getTreeHeight(){
            return height(root);
        }

};

//-------------------- TESTING FUNCTIONS FOR BST AND AVL --------------------
//NOTE: THESE 2 TESTING FUNCTIONS BELOW WERE GENERATED USING GEMINI PRO (FOR THE PURPOSE OF VALIDATING THE FUNCTIONALITIES OF MY CODE ONLY), EVERYTHING ABOVE WERE CODED "MANUALLY" BY ME

void runBSTAssertions() {
    BST tree;

    // Test Empty Tree
    if (tree.search(10)) {
        throw std::runtime_error("Error: Found a value in an empty tree!");
    }

    // Test Insertions
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Test Search Logic
    if (!tree.search(50) || !tree.search(20) || !tree.search(80)) {
        throw std::runtime_error("Error: Could not find values that were successfully inserted!");
    }
    if (tree.search(99)) {
        throw std::runtime_error("Error: Found a ghost value (99) that was never inserted!");
    }

    // Test Deletion - Case 1: Leaf Node
    tree.remove(20); 
    if (tree.search(20)) {
        throw std::runtime_error("Error: Failed to delete Case 1 (Leaf Node: 20)!");
    }

    // Test Deletion - Case 2: Node with 1 child
    tree.remove(30); 
    if (tree.search(30)) {
        throw std::runtime_error("Error: Failed to delete Case 2 (Node with 1 child: 30)!");
    }
    if (!tree.search(40)) {
        throw std::runtime_error("Error: Case 2 deletion broke the chain and lost the child (40)!");
    }

    // Test Deletion - Case 3: Node with 2 children
    tree.remove(50); 
    if (tree.search(50)) {
        throw std::runtime_error("Error: Failed to delete Case 3 (Node with 2 children: 50)!");
    }
    
    // Verify structural integrity
    if (!tree.search(60) || !tree.search(70) || !tree.search(80) || !tree.search(40)) {
        throw std::runtime_error("Error: Case 3 deletion corrupted the remaining tree structure!");
    }

    // If it survives to this line, the logic is flawless
    std::cout << "BST works\n";
    std::cout << "Final remaining elements (should be 40 60 70 80): ";
    tree.inorder(); 
}

// 2. THE MANAGER: Safely executes the engine and catches catastrophic failures
void testBST() {
    try {
        runBSTAssertions(); // Attempt to run the heavy logic
    } 
    catch (const std::exception& e) {
        // If runBSTAssertions() threw an error, execution immediately jumps here
        std::cerr << "\nTEST FAILED: " << e.what() << "\n";
    }
}

// 1. THE AVL ENGINE
void runAVLAssertions() {
    AVLTree avl;

    // We intentionally insert 7 fully sorted numbers
    for (int i = 10; i <= 70; i += 10) {
        avl.insert(i);
    }

    // THE ULTIMATE CHECK: Did it become a linked list (height 7) or a balanced tree (height 3)?
    int actualHeight = avl.getTreeHeight();
    
    if (actualHeight != 3) {
        // If the rotations failed, the height will be wrong. Throw a massive error.
        throw std::runtime_error("AVL Rotations Failed! Expected height 3, but got height " + std::to_string(actualHeight));
    }

    // If execution reaches here, the math is flawless.
    std::cout << "\nAVL works flawlessly. It survived the sorted-data stress test!\n";
    std::cout << "Inorder traversal (should still be perfectly sorted: 10 to 70): ";
    avl.inorder();
}

// 2. THE AVL MANAGER
void testAVL() {
    try {
        runAVLAssertions();
    } 
    catch (const std::exception& e) {
        std::cerr << "\nAVL TEST FAILED: " << e.what() << "\n";
    }
}

int main() {
    std::cout << "--- Starting Data Structure Diagnostics ---\n";
    
    testBST();
    testAVL();
    
    std::cout << "--- Diagnostics Complete ---\n";
    return 0;
}