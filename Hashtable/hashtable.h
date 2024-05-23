#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

class HashTable {
    string* table;
    int N;
    int count;

    // Polynomial Hash Code using a=7
    int hash_code(string key) {
        int code = 0;
        int a = 7;
        for (int i = 0; i < key.length; i++) {
            code = code * a + key[i];
        }
        return code;
    }

    // MAD Compression Function where a = 11, b = 461, p = 919
    int compress(int code) {
        int a = 11;
        int b = 461;
        int p = 919;
        return ((a * code + b) % p) % N;
    }

    int hashfn(string key) {
        return compress(hash_code(key));
    }

public:
    HashTable(int N) {
        this->N = N;
        table = new string[N];
        for (int i = 0; i < N; i++) {
            table[i] = "";
        }
        count = 0;
    }

    // Insert key into the hash table using quadratic probing
    int insert(string key) {
        int index = hashfn(key);
        int originalIndex = index;
        int k = 1;
        while (table[index] != "") {
            if (table[index] == key) return index; // Key already exists
            index = (originalIndex + k * k) % N;
            k++;
            if (index == originalIndex) return -1; // Table is full
        }
        table[index] = key;
        count++;
        return index;
    }

    // Search for key in the hash table using quadratic probing
    int search(string key) {
        int index = hashfn(key);
        int originalIndex = index;
        int k = 1;
        while (table[index] != "") {
            if (table[index] == key) return index;
            index = (originalIndex + k * k) % N;
            k++;
            if (index == originalIndex) return -1; // Not found
        }
        return -1; // Not found
    }

    // Remove key from the hash table
    int remove(string key) {
        int index = search(key);
        if (index == -1) return -1; // Key not found
        table[index] = ""; // Mark as empty
        count--;
        return index;
    }

    // Print the hash table
    void print() {
        for (int i = 0; i < N; i++) {
            cout << i << ": " << table[i] << endl;
        }
    }
};
