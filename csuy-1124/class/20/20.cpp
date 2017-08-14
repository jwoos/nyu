#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    Node (int data = 0, Node* next = nullptr) : data(data), next(next) {}

    int data;

    Node* next;
};

void listDisplay(Node* head) {
    Node* p = head;
    while (p != nullptr) {
        cout << p -> data << ' ';
        p = p -> next;
    }
    cout << endl;
}

int listSize(Node* head) {
    Node* p = head;
    int counter = 0;
    while (p != nullptr) {
        counter++;
        p = p -> next;
    }
    
    return counter;
}

Node* listFindEnd(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* p = head;
    while (p -> next != nullptr) {
        p = p -> next;
    }
    return p;
}

void listAddToEnd(Node* head, int data) {
    Node* theEnd = listFindEnd(head);
    theEnd -> next = new Node(data);
}

int main() {
    // linked list
    Node* list = nullptr;
    list = new Node(17);
    listAddToEnd(list, 42);
}