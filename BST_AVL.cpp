//coded by Pham Tuan Nghia (25021912)
//QH-2025-I/CQ-I-CS2 (UET - VNU)

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <queue>

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
                    Node* sucessor = findMin(node -> right);
                    node -> data = sucessor -> data;
                    removeRec(node -> right, sucessor -> data);
                }
            }
        }

        //helper function for recursive inorder traversal
        void inorderRec(Node* node){
            if (node == nullptr){
                return;
            }

            inorderRec(node -> left);

            std::cout << node -> data << " ";
            
            inorderRec(node -> right);
        }

        //helper function to recursively demolish the tree (Post-order)
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
                if (temp -> data == val){
                    return true;
                }
                else if (temp -> data < val){
                    temp = temp -> right;
                }
                else{
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

int main(){
    testBST();
    return 0;
}