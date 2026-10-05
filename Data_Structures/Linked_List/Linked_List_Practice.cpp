#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

void printList(Node* head) {
    Node* current = head;

    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
}

void insertAtBeginning(Node* &head) {
    Node* newNode = new Node(5);
    newNode->next = head;
    head = newNode;
}

void insertAtEnd(Node* &head) {
    Node* newNode = new Node(40);

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;

    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
    newNode->next = nullptr;
}

void insertAtPosition(Node* &head, int position) {
    if (position < 0) {
        return;
    }

    Node* newNode = new Node(15);

    if (position == 0) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;

    for (int i = 0; i < position - 1 && current->next != nullptr; i ++) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void deleteFromBeginning(Node* &head) {
    if (head == nullptr) {
        return;
    }

    head = head->next;
}

void deleteFromEnd(Node* &head) {
    if (head == nullptr) {
        return;
    }

    if (head->next == nullptr) {
        head = nullptr;
        return;
    }

    Node* current = head;

    while (current->next->next != nullptr) {
        current = current->next;
    }

    current->next = nullptr;
}

void deleteFromPosition(Node* &head, int position) {
    if (head == nullptr) {
        return;
    }

    if (position < 0) {
        return;
    }

    if (position == 0) {
        deleteFromBeginning(head);
        return;
    }

    Node* current = head;

    for (int i = 0; i < position - 1 && current->next != nullptr; i ++) {
        current = current->next;
    }

    current->next = current->next->next;
}

int main() {
    // Node creation
    Node* head = new Node(10);
    Node* second = new Node(20);
    Node* third = new Node(30);

    // Node Linking
    head->next = second;
    second->next = third;

    // Insert the new node at beginning of the linked list
    insertAtBeginning(head);

    // Insert the new node at the end of the linked list
    insertAtEnd(head);

    // Insert at a specific position
    insertAtPosition(head, 2);

    // Delete from beginning
    deleteFromBeginning(head);

    // Delete from end
    deleteFromEnd(head);

    // Delete from a specific position
    deleteFromPosition(head, 1);

    // Printing the linked list
    printList(head);

    return 0;
}