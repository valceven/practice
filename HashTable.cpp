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
        for (int i = 0; i < key.size(); i++) {
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
    
    // Insert key into the hash table
    int insert(string key) {
        int index = hashfn(key);
        int startIndex = index;
        while (table[index] != "") {
            if (table[index] == key) return index; // Key already exists
            index = (index + 1) % N;
            if (index == startIndex) return -1; // Table is full
        }
        table[index] = key;
        count++;
        return index;
    }
    
    // Search for key in the hash table
    int search(string key) {
        int index = hashfn(key);
        int startIndex = index;
        while (table[index] != "") {
            if (table[index] == key) return index;
            index = (index + 1) % N;
            if (index == startIndex) return -1; // Not found
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
