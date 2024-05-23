#include <iostream>
#include <algorithm>
using namespace std;

class ArrayList {
private:
    int* arr;
    int capacity;
    int currentSize;

public:
    ArrayList() {
        capacity = 10; // Initial capacity
        arr = (int*)malloc(capacity * sizeof(int));
        currentSize = 0;
    }

    ~ArrayList() {
        free(arr);
    }

    // Insert an element into the ArrayList
    void insert(int val) {
        if (currentSize == capacity) {
            capacity *= 2; // Double the capacity if needed
            arr = (int*)realloc(arr, capacity * sizeof(int));
        }
        arr[currentSize++] = val;
    }

    // Print the ArrayList
    void print() {
        for (int i = 0; i < currentSize; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    int size() {
        return currentSize;
    }

    // Insertion Sort
    void insertionSort() {
        for (int i = 1; i < currentSize; i++) {
            int key = arr[i];
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

    // Quick Sort
    void quickSort(int low, int high) {
        if (low < high) {
            int pivot = partition(low, high);
            quickSort(low, pivot - 1);
            quickSort(pivot + 1, high);
        }
    }

    // Merge Sort
    void mergeSort(int low, int high) {
        if (low < high) {
            int mid = low + (high - low) / 2;
            mergeSort(low, mid);
            mergeSort(mid + 1, high);
            merge(low, mid, high);
        }
    }

private:
    // Partition function for Quick Sort
    int partition(int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    // Merge function for Merge Sort
    void merge(int low, int mid, int high) {
        int n1 = mid - low + 1;
        int n2 = high - mid;

        int* left = (int*)malloc(n1 * sizeof(int));
        int* right = (int*)malloc(n2 * sizeof(int));

        for (int i = 0; i < n1; i++) {
            left[i] = arr[low + i];
        }
        for (int j = 0; j < n2; j++) {
            right[j] = arr[mid + 1 + j];
        }

        int i = 0, j = 0, k = low;
        while (i < n1 && j < n2) {
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
            }
        }

        while (i < n1) {
            arr[k++] = left[i++];
        }

        while (j < n2) {
            arr[k++] = right[j++];
        }

        free(left);
        free(right);
    }
};

int main() {
    ArrayList list;

    // Insert elements
    list.insert(5);
    list.insert(2);
    list.insert(7);
    list.insert(3);
    list.insert(1);

    cout << "Original ArrayList: ";
    list.print();

    // Sort using Insertion Sort
    list.insertionSort();
    cout << "ArrayList after Insertion Sort: ";
    list.print();

    // Sort using Bubble Sort
    list.bubbleSort();
    cout << "ArrayList after Bubble Sort: ";
    list.print();

    // Sort using Selection Sort
    list.selectionSort();
    cout << "ArrayList after Selection Sort: ";
    list.print();

    // Sort using Quick Sort
    list.quickSort(0, list.size() - 1);
    cout << "ArrayList after Quick Sort: ";
    list.print();

    // Sort using Merge Sort
    list.mergeSort(0, list.size() - 1);
    cout << "ArrayList after Merge Sort: ";
    list.print();

    return 0;
}