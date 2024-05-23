#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class ArrayList {
private:
    T* arr;
    int capacity;
    int currentSize;

public:
    ArrayList() {
        capacity = 10; // Initial capacity
        arr = new T[capacity];
        currentSize = 0;
    }

    ~ArrayList() {
        delete[] arr;
    }

    // Insert an element into the ArrayList
    void insert(const T& val) {
        if (currentSize == capacity) {
            capacity *= 2; // Double the capacity if needed
            T* newArr = new T[capacity];
            copy(arr, arr + currentSize, newArr);
            delete[] arr;
            arr = newArr;
        }
        arr[currentSize++] = val;
    }

    // Print the ArrayList
    void print() const {
        for (int i = 0; i < currentSize; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    int size() const {
        return currentSize;
    }

    // Insertion Sort
    void insertionSort() {
        for (int i = 1; i < currentSize; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // Bubble Sort
    void bubbleSort() {
        for (int i = 0; i < currentSize - 1; i++) {
            for (int j = 0; j < currentSize - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // Selection Sort
    void selectionSort() {
        for (int i = 0; i < currentSize - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < currentSize; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            swap(arr[i], arr[minIndex]);
        }
    }
};

int main() {
    ArrayList<int> intList;
    ArrayList<double> doubleList;
    ArrayList<char> charList;

    // Insert elements
    intList.insert(5);
    intList.insert(2);
    intList.insert(7);
    intList.insert(3);
    intList.insert(1);

    cout << "Original Integer ArrayList: ";
    intList.print();

    // Sort using Selection Sort
    intList.selectionSort();
    cout << "Integer ArrayList after Selection Sort: ";
    intList.print();

    // Insert elements
    doubleList.insert(5.5);
    doubleList.insert(2.2);
    doubleList.insert(7.7);
    doubleList.insert(3.3);
    doubleList.insert(1.1);

    cout << "Original Double ArrayList: ";
    doubleList.print();

    // Sort using Bubble Sort
    doubleList.bubbleSort();
    cout << "Double ArrayList after Bubble Sort: ";
    doubleList.print();

    // Insert elements
    charList.insert('e');
    charList.insert('b');
    charList.insert('g');
    charList.insert('d');
    charList.insert('a');

    cout << "Original Char ArrayList: ";
    charList.print();

    // Sort using Insertion Sort
    charList.insertionSort();
    cout << "Char ArrayList after Insertion Sort: ";
    charList.print();

    return 0;
}
