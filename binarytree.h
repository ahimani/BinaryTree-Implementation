#include "cmpt_error.h"
#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// In the specification of the methods for BST, these variables are used:
//
// - n is the number of nodes in the BST
// - h is the height of the BST
// - T refers to the tree immediately before a method is called
// - T' refers to the tree immediately after the method is finished
//
///////////////////////////////////////////////////////////////////////////////

class BST {
private:
    // Node of the binary tree
    struct Node {
        string value;
        Node* left;
        Node* right;
    };
    Node* head;
    
    // Creat a Stack class to implement BST methods iteratively
    class Stack {
    private:
        struct nodeStack {
            Node* data;
            nodeStack* next;
            nodeStack* previous;
        };
        nodeStack* top; 
        nodeStack* bottom;
        
    public:
        // stackSize tracks the size of the stack at any point
        int stackSize;  
        
        // Pre-condition:
        //    none
        // Post-condition:
        //    Creates a new empty Stack
        // Constraints:
        //    O(1) performance
        Stack()
        : top(nullptr), bottom(nullptr), stackSize(0)
        {}
        
        // Pre-condition:
        //    none
        // Post-condition:
        //    Pushes newNode onto the Stack
        //    top->data = newNode
        // Constraints:
        //    O(1) performance
        void push(Node* newNode) {
            nodeStack* new_nodeStack = new nodeStack;
            
            // Push a binary Node onto it
            new_nodeStack->data = newNode;      
            new_nodeStack->previous = top;
            
            // If new_nodeStack is the first node, set bottom to new_nodeStack
            if(stackSize == 0) bottom = new_nodeStack;
            else top->next = new_nodeStack;
            new_nodeStack->next = bottom;
            top = new_nodeStack;
            stackSize++;
            return;
        }
        
        // Pre-condition:
        //    none
        // Post-condition:
        //    Pops the top node from the stack
        // Constraints:
        //    O(1) performance
        void pop() {
            nodeStack* headNode = top;
            top = top->previous;
            delete headNode;
            stackSize--;
            return;
        }

        // Pre-condition:
        //    none
        // Post-condition:
        //    Pops the bottom node from the stack
        // Constraints:
        //    O(1) performance
        void pop_bottom() {
            nodeStack* tailNode = bottom;
            bottom = bottom->next;
            delete tailNode;
            stackSize--;
            return;
        }
        
        // Pre-condition:
        //    none
        // Post-condition:
        //    Returns the top Node* from the stack
        // Constraints:
        //    O(1) performance
        Node* peek() {
            return top->data;
        }
        
        // Pre-condition:
        //    none
        // Post-condition:
        //    Returns the bottom Node* from the stack
        // Constraints:
        //    O(1) performance
        Node* peek_bottom() {
            return bottom->data;
        }
        
        // Pre-condition:
        //    none
        // Post-condition:
        //    Returns true if Stack is empty, false otherwise
        // Constraints:
        //    O(1) performance
        bool isEmpty() {
            return top == nullptr;
        }
    }; // class Stack
    
public:
    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new empty BST
    // Constraints:
    //    O(1) performance
    BST()
    : head(nullptr)
    {}

    // Pre-condition:
    //    none
    // Post-condition:
    //    deletes all the nodes in this BST
    // Constraints:
    //    O(n) performance
    ~BST() {
        if(head != nullptr) {
        
            Stack treeStack1;
            Stack treeStack2;
            treeStack1.push(head);
            Node* P = head;
            Node* temp = nullptr;
            
            // Store the nodes in reverse post_order in the treeStack2
            while(!treeStack1.isEmpty()) {
                P = treeStack1.peek();
                treeStack1.pop();
                treeStack2.push(P);
                if(P->left != nullptr) treeStack1.push(P->left);
                if(P->right != nullptr) treeStack1.push(P->right);
            }
            
            // Delete the nodes in post_order using treeStack2
            while(!treeStack2.isEmpty()) {
                P = treeStack2.peek();
                treeStack2.pop();
                temp = P;
                delete temp;
            }
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the number of string in this tree (i.e. n)
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    int size() const {
        if(head == nullptr) {
            return 0;
        }
        Stack treeStack;
        int nodes = 0;
        treeStack.push(head);
        Node* P = head;
        while(!treeStack.isEmpty()) {
            P = treeStack.peek();
            treeStack.pop();
            nodes++;
            if(P->right != nullptr) treeStack.push(P->right);
            if(P->left != nullptr) treeStack.push(P->left);
        }
        return nodes;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the height of this tree
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    // Note:
    //    The height of a BST is the number of links in the longest
    //    root-to-leaf path in the tree. An empty tree is height 0,
    //    and a tree with a single node is also height 0.
    int height() const {
        if(head == nullptr) return 0;
        int maxHeight = 0;
        Stack treeStack;
        treeStack.push(head);
        int count = 0;
        Node* P = nullptr;
        while(!treeStack.isEmpty()) {
            count = treeStack.stackSize;
            if(count == 0) {
                break;
            }
            else {
                maxHeight++;
            }    
            while(count != 0) {
                P = treeStack.peek_bottom();
                treeStack.pop_bottom();
                if(P->left != nullptr) {
                    treeStack.push(P->left);
                }
                if(P->right != nullptr) {
                    treeStack.push(P->right);
                }
                count--;
            }
        }
        return maxHeight-1;
    }
    
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true if s is in this tree, and false otherwise
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    bool contains(const string& s) const {
        Node* curr = head;
        while(curr != nullptr) {
            if(s < curr->value) {
                if(curr->left == nullptr) {
                    return false;
                }
                curr = curr->left;
            }
            else if(s > curr->value) {
                if(curr->right == nullptr) {
                    return false;
                }
                curr = curr->right;
            }
            else {
                return true;
            }
        }
        return false;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    T'.contains(s)
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    // Note:
    //    If s is already in T, then insert(s) does nothing.
    void insert(const string& s) {
        Node* curr = head;
        while(curr != nullptr) {
            
            // Case 1: s will be inserted in the left subtree, s < curr->value
            if(s < curr->value) {
                if(curr->left == nullptr) {
                    curr->left = new Node;
                    curr->left->value = s;
                    curr->left->left = nullptr;
                    curr->left->right = nullptr;
                    return;
                }
                curr = curr->left;
            }
            
            // Case 2: s will be inserted in the right subtree, s > curr->value
            else if(s > curr->value) {
                if(curr->right == nullptr) {
                    curr->right = new Node;
                    curr->right->value = s;
                    curr->right->left = nullptr;
                    curr->right->right = nullptr;
                    return;
                }
                curr = curr->right;
            }
            
            // Case 3: s already exists in the tree
            else {
                return;
            }
        }
        
        //Case 4: s will inserted as head
        head = new Node;
        head->value = s;
        head->left = nullptr;
        head->right = nullptr;
        return;
        // T'.contains(s);
    }
    
    // Pre-condition:
    //    none
    // Post-condition:
    //    !T'.contains(s)
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    // Note:
    //    If s is not in T, then remove(s) does nothing.
    void remove(const string& s) {
        if(head == nullptr) {
            cmpt::error("head is null");
            return;
        }
        Node* curr = head;
        Node* prev = curr;
        bool left = true;
        while(curr->left != nullptr || curr->right != nullptr) {
            
            // Case 1: s is in the left subtree
            if(s < curr->value) {
                if(curr->left == nullptr) {
                    return;
                }
                left = true; 
                prev = curr;
                curr = curr->left;
            }
            
            // Case 2: s is in the right subtree
            else if(s > curr->value) {
                if(curr->right == nullptr) {
                    
                    return;
                }
                left = false; 
                prev = curr;
                curr = curr->right;
            }
            
            // Case 3: s is equal to the curr->value
            else {
                
                // Case 3a: curr Node has 1 child, curr->left == nullptr
                if(curr->left == nullptr) {
                    if(curr == head) {
                        head = head->right;
                        delete curr;
                        return;
                    }
                    if(left == true) {
                        
                        prev->left = curr->right;
                    }
                    else {
                        
                        prev->right = curr->right;
                    }
                    delete curr;
                    return;
                }
                
                // Case 3b: curr Node has 1 child, curr->right == nullptr
                else if(curr->right == nullptr) {
                    if(curr == head) {
                        head = head->left;
                        delete curr;
                        return;
                    }
                    if(left == true) prev->left = curr->left;
                    else if(left != true) prev->right = curr->left;
                    delete curr;
                    return;
                }
                
                // Case 3c: curr Node has two children, 
                //          curr->left != nullptr && curr->right != nullptr
                else {
                    Node* traverse = curr->left;
                    while(traverse->right != nullptr) {
                        prev = traverse;
                        traverse = traverse->right;
                    }
                    if(traverse == curr->left) {
                        curr->left = nullptr;
                    }
                    else prev->right = traverse->left;
                    curr->value = traverse->value;
                    delete traverse;
                    return;
                }
            }
        }
        
        // Case 4: curr Node is a leaf, 
        //         curr->left == nullptr && curr->right == nullptr
        if(s != curr->value) return;
        if(curr == head) head = nullptr;
        if(left == true) prev->left = nullptr;
        else if(left == false) prev->right = nullptr; 
        delete curr;
        return;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in pre-order order
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_preorder() const {
        if(head == nullptr) {
            return;
        }
        Stack treeStack;
        treeStack.push(head);
        Node* P = head;
        while(!treeStack.isEmpty()) {
            P = treeStack.peek();
            treeStack.pop();
            cout << P->value << " ";
            if(P->right != nullptr) treeStack.push(P->right);
            if(P->left != nullptr) treeStack.push(P->left);
        }
        return;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in in-order order
    //    (i.e. alphabetical order)
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_inorder() const {
        Stack treeStack;
        Node* curr = head;
        Node* P = curr;
        while(curr != nullptr || !treeStack.isEmpty()) {
            while(curr != nullptr) {
                treeStack.push(curr);
                curr = curr->left;
            }
            if(curr == nullptr && !treeStack.isEmpty()) {
                P = treeStack.peek();
                treeStack.pop();
                cout << P->value << " ";
                curr = P->right;
            }
        }
        return;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in post-order order
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_postorder() const {
        if(head == nullptr) {
            return;
        }
        Stack treeStack1;
        Stack treeStack2;
        treeStack1.push(head);
        Node* P = head;
        while(!treeStack1.isEmpty()) {
            P = treeStack1.peek();
            treeStack1.pop();
            treeStack2.push(P);
            if(P->left != nullptr) treeStack1.push(P->left);
            if(P->right != nullptr) treeStack1.push(P->right);
        }
        while(!treeStack2.isEmpty()) {
            P = treeStack2.peek();
            treeStack2.pop();
            cout << P->value << " ";
        }
        return;
    }
    
}; // class BST