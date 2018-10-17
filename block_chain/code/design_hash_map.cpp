// https://leetcode.com/problems/design-hashmap/

#include <iostream>
#include <vector>

class MyHashMap {
 public:
  /** Initialize your data structure here. */
  struct Slot {
    int key;
    int value;
    bool empty = true;
    // Slot(int i, int v, bool e) : id(i), value(v), empty(e){
  };

  // initialize size with small prime numbr
  int size = 101;
  int id = 0;
  vector<Slot> hashMap0;

  // vector<int> hashMap0 = vector<int>(slots);
  // vector<Slot> hashMap0 = vector<Slot> (size);

  int myHash(int key) {
    // cout << "now mod " << key << endl;
    return key % size;
  }

  int myChain(int n) { return n; }

  void doubleSize() {
    cout << "begin rehash ";
    int size_old = size;
    // for (int i = (size * 2); isPrime(i); i++) {
    size *= 2;
    while (isPrime(size) == false) {
      size++;
      //   cout << "repeating......." << size << endl;
    }

    vector<Slot> tempSet;
    tempSet = hashMap0;

    hashMap0.clear();
    Slot temp = {-1, -1, true};  // empty = true
    for (int i = 0; i < size; i++) {
      hashMap0.push_back(temp);
    }

    // rehash all keys to new set
    for (int i = 0; i < size_old; i++) {
      if (tempSet.at(i).empty == false) {
        put(tempSet.at(i).key, tempSet.at(i).value);
        id--;
      }
    }
    cout << ", rehashed, the new size is " << hashMap0.size() << endl;
  }

  MyHashMap() {
    Slot temp = {-1, -1, true};  // empty = true
    for (int i = 0; i < size; i++) {
      hashMap0.push_back(temp);
    }
  }

  /** value will always be non-negative. */
  void put(int key, int value) {
    if (id > hashMap0.size() / 2) {
      //   cout << "id = " << id << endl;
      doubleSize();
    }

    size = hashMap0.size();

    // create a Slot for this key, struct initializer list !!!
    Slot curr = {key, value, false};
    // or uniform initialization
    // Slot curr {id, key, false};

    int count = 0;        // collision count
    int n = myHash(key);  // the slot that we might put in

    if (hashMap0.at(n).empty) {
      hashMap0.at(n) = curr;
      if (value == 432) {
        cout << "added key " << key << " value " << value << " at " << n
             << endl;
      }
    } else {
      // find the next available slot
      while (hashMap0.at(n).empty == false) {
        if (hashMap0.at(n).key == key) {
          hashMap0.at(n).value = value;
          return;
        };
        count++;
        n = (n + myChain(count)) % size;
        // cout << "collision = " << count << endl;
      }
      // this is a hash set, so no duplicates
      hashMap0.at(n) = curr;
      if (value == 432) {
        cout << "move forwad added key " << key << " value " << value << " at "
             << n << endl;
      }
    }

    id++;
    // printHash();
  }

  /** Returns the value to which the specified key is mapped, or -1 if this map
   * contains no mapping for the key */
  int get(int key) {
    int count = 0;
    int n = myHash(key);
    while (count < size) {
      if (hashMap0.at(n).key == key && hashMap0.at(n).empty == false) {
        // cout << "contain " << key << endl;
        return hashMap0.at(n).value;
      } else {
        count++;
        n = (n + myChain(count)) % size;
      }
    }
    // cout << "not contain " << key << endl;
    return -1;
  }

  /** Removes the mapping of the specified value key if this map contains a
   * mapping for the key */
  void remove(int key) {
    int count = 0;
    int n = myHash(key);
    while (count < size) {
      if (hashMap0.at(n).key == key && hashMap0.at(n).empty == false) {
        // cout << "removed " << key << endl;
        hashMap0.at(n).empty = true;
        hashMap0.at(n).value = -1;
        break;
      } else {
        count++;
        n = (n + myChain(count)) % size;
      }
    }
    // printHash();}
  }

  void printHash() {
    for (int i = 0; i < size; i++) {
      cout << hashMap0.at(i).value << " ";
    }
    // cout << endl;
  }

  bool isPrime(int a) {
    int counter = 0;  // counter for numbers which devided by the number give
                      // reminder 0 (are divisors of the number)
    for (int i = 2; i <= a / 2;
         i++)  // we start from 2 because 1 is divisor to all numbers. Also we
               // go to the number devided by 2 because there isn't number
               // higher than this that can be devider and give a integer as a
               // result. For example 6: 6/1=6; 6/6=1 --> this is for all
               // numbers; 6/3=2 but 6/4 is not integer. We do not need to count
               // 6 as a devider or check if the range (6/2..6)
      if (a % i == 0)  // checking if the number is devisor
        counter++;     // if there is a devisor we count it

    if (counter ==
        0)  // if the counter is equal to 0 that means the number doesn't have
            // any other integer devisors other than 1 and itself therefore it
            // is a prime number and we retrun true
      return true;
    else  // the counter is not 0, which means the number has other devisors
          // other than 1 and itself therefore it is not a prime number
      return false;
  }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap obj = new MyHashMap();
 * obj.put(key,value);
 * int param_2 = obj.get(key);
 * obj.remove(key);
 */