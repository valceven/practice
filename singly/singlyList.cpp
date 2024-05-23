#include <iostream>
#include "node.h"
using namespace std;


class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void insert(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    void print() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void insertionSort() {
        if (head == nullptr || head->next == nullptr) return;

        Node* sorted = nullptr;
        Node* current = head;

        while (current != nullptr) {
            Node* nextNode = current->next;
            if (sorted == nullptr || sorted->data >= current->data) {
                current->next = sorted;
                sorted = current;
            } else {
                Node* temp = sorted;
                while (temp->next != nullptr && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = nextNode;
        }
        head = sorted;
    }

    // Selection Sort
    void selectionSort() {
        if (head == nullptr || head->next == nullptr) return;

        Node* current = head;
        while (current != nullptr) {
            Node* minNode = current;
            Node* temp = current->next;
            while (temp != nullptr) {
                if (temp->data < minNode->data) {
                    minNode = temp;
                }
                temp = temp->next;
            }
            swap(current->data, minNode->data);
            current = current->next;
        }
    }

    // Bubble Sort
    void bubbleSort() {
        if (head == nullptr || head->next == nullptr) return;

        bool swapped;
        Node* last = nullptr;
        do {
            swapped = false;
            Node* current = head;
            while (current->next != last) {
                if (current->data > current->next->data) {
                    swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
            last = current;
        } while (swapped);
    }
};

int main() {
    SinglyLinkedList list;

    list.insert(5);
    list.insert(2);
    list.insert(7);
    list.insert(3);
    list.insert(1);

    cout << "Original List: ";
    list.print();

    list.insertionSort();
    cout << "List after Insertion Sort: ";
    list.print();

    list.selectionSort();
    cout << "List after Selection Sort: ";
    list.print();

    list.bubbleSort();
    cout << "List after Bubble Sort: ";
    list.print();

    return 0;
}
