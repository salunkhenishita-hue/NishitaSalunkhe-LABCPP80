#include <iostream>

// Define the structural blueprint of a single node
struct Node {
    int data;
    Node* next;

    // Constructor to easily create new nodes
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head; // Points to the first node in the list

public:
    // Constructor
    LinkedList() : head(nullptr) {}

    // Destructor to clean up memory and prevent leaks
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        std::cout << "[Memory Cleared]\n";
    }

    // 1. Insert at the front (O(1) time complexity)
    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // 2. Append to the back (O(N) time complexity)
    void append(int val) {
        Node* newNode = new Node(val);
        
        // If the list is empty, make this the head
        if (head == nullptr) {
            head = newNode;
            return;
        }

        // Traverse to the last node
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // 3. Delete a node by its value
    void deleteValue(int val) {
        if (head == nullptr) return;

        // Case A: The node to delete is the head node
        if (head->data == val) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Case B: The node is somewhere down the line
        Node* current = head;
        while (current->next != nullptr && current->next->data != val) {
            current = current->next;
        }

        // If found, skip it and free memory
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    // 4. Reverse the list in-place (Classic Interview Problem)
    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;

        while (current != nullptr) {
            nextNode = current->next; // Save the rest of the list
            current->next = prev;     // Reverse the current node's pointer
            prev = current;           // Move prev up to the current node
            current = nextNode;       // Move current up to the next node
        }
        head = prev; // Update head to point to the new front
    }

    // Print the entire list format
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr\n";
    }
};

int main() {
    LinkedList list;

    std::cout << "--- Building the List ---\n";
    list.append(10);
    list.append(20);
    list.append(30);
    list.insertAtHead(5);
    list.display(); // Expected: 5 -> 10 -> 20 -> 30 -> nullptr

    std::cout << "\n--- Deleting Node 20 ---\n";
    list.deleteValue(20);
    list.display(); // Expected: 5 -> 10 -> 30 -> nullptr

    std::cout << "\n--- Reversing the List ---\n";
    list.reverse();
    list.display(); // Expected: 30 -> 10 -> 5 -> nullptr

    std::cout << "\n--- Exiting Main ---\n";
    return 0;
}
