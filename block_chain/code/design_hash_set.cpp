// https://leetcode.com/problems/design-hashset/
// accepted version (next siez is prime number)

#include <iostream>
#include <vector>

class MyHashSet {
 public:
  /** Initialize your data structure here. */
  struct Slot {
    // int id;
    int value;
    bool empty = true;
    // Slot(int i, int v, bool e) : id(i), value(v), empty(e){
  };

  // initialize size with small prime numbr
  int size = 101;
  int id = 0;
  vector<Slot> hashSet;

  // vector<int> hashSet = vector<int>(slots);
  // vector<Slot> hashSet = vector<Slot> (size);

  int myHash(int key) {
    // cout << "now mod " << key << endl;
    return key % size;
  }

  int myChain(int n) { return n; }

  void doubleSize() {
    int size_old = size;
    for (int i = size * 2; isPrime(i); i++) size = i;

    vector<Slot> tempSet;
    tempSet = hashSet;

    hashSet.clear();
    Slot temp = {-1, true};  // empty = true
    for (int i = 0; i < size; i++) {
      hashSet.push_back(temp);
    }

    // rehash all keys to new set
    for (int i = 0; i < size_old; i++) {
      if (tempSet.at(i).empty == false) {
        add(tempSet.at(i).value);
        id--;
      }
    }

    cout << "rehashed, the new size is " << hashSet.size() << endl;
  }

  MyHashSet() {
    Slot temp = {-1, true};  // empty = true
    for (int i = 0; i < size; i++) {
      hashSet.push_back(temp);
    }
  }

  void add(int key) {
    if (id >= hashSet.size() / 2) {
      doubleSize();
    }

    // create a Slot for this key, struct initializer list !!!
    Slot curr = {key, false};
    // or uniform initialization
    // Slot curr {id, key, false};

    int count = 0;        // collision count
    int n = myHash(key);  // the slot that we might put in

    if (hashSet.at(n).empty) {
      hashSet.at(n) = curr;
      //   cout << "added " << key << " at " << n << endl;
    } else {
      // find the next available slot
      while (hashSet.at(n).empty == false) {
        if (hashSet.at(n).value == key) return;
        count++;
        n = (n + myChain(count)) % hashSet.size();
        // cout << "collision = " << count << endl;
      }
      // this is a hash set, so no duplicates
      hashSet.at(n) = curr;
      //   cout << "move forward and added " << key << " at " << n << endl;
    }

    id++;
    // printHash();
  }

  void remove(int key) {
    int count = 0;
    int n = myHash(key);
    while (count < size) {
      if (hashSet.at(n).value == key && hashSet.at(n).empty == false) {
        // cout << "removed " << key << endl;
        hashSet.at(n).empty = true;
        hashSet.at(n).value = -1;
        id--;
        break;
      } else {
        count++;
        n = (n + myChain(count)) % size;
      }
    }
    // printHash();
  }

  /** Returns true if this set contains the specified element */
  bool contains(int key) {
    int count = 0;
    int n = myHash(key);
    while (count < size) {
      if (hashSet.at(n).value == key && hashSet.at(n).empty == false) {
        // cout << "contain " << key << endl;
        return true;
      } else {
        count++;
        n = (n + myChain(count)) % size;
      }
    }
    // cout << "not contain " << key << endl;
    return false;
  }

  void printHash() {
    for (int i = 0; i < size; i++) {
      //   cout << hashSet.at(i).value << " ";
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
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet obj = new MyHashSet();
 * obj.add(key);
 * obj.remove(key);
 * bool param_3 = obj.contains(key);
 */