// CS130A HW1 build blcok chain

#include <string>

#ifndef CHAIN_H
#define CHAIN_H

class FakeChain {
 public:
  // constructor
  FakeChain();

  // modify
  bool add(int amount, std::string sender, std::string receiver);

  // const func
  bool find(std::string sender) const;
  void print();
  int sum() const;

  //  private:
  struct Transaction {
    int amount;            // amount of money that has been transferred
    std::string sender;    // sender of money
    std::string receiver;  // receiver of money
    std::string nonce;     // random string that will be used during hashing for
                           // the next transaction
    std::string hash;      // hash of content of previous transaction
    Transaction* prev;
  };

  Transaction* first;  // pointer to the first node
  Transaction* last;   // pointer to the lastest node
  clock_t t;

  // helper
  std::string getNonce();
  char* getHash(Transaction* last, std::string nonceTemp);
};

#endif