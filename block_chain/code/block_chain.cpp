#include <openssl/sha.h>
#include <string.h>
#include <time.h>
#include <cstdlib>   //for rand()
#include <iostream>  // for time ()
#include <string>

#include "block_chain.h"

// using namespace std;

// set up empty block chain
FakeChain::FakeChain() {
  first = nullptr;
  t = clock();
}

// modify
bool FakeChain::add(int amount, std::string sender, std::string receiver) {
  // new Node on heap
  Transaction* newTrans = new Transaction;

  // assign values
  newTrans->amount = amount;
  newTrans->sender = sender;
  newTrans->receiver = receiver;

  std::string nonceTemp = getNonce();
  char* hashFull = getHash(newTrans, nonceTemp);
  char hashDigit = hashFull[strlen(hashFull) - 1];
  int hDigit = hashDigit - '0';

  while (hDigit < 1 || hDigit > 4) {
    nonceTemp = getNonce();
    hashFull = getHash(newTrans, nonceTemp);
    hashDigit = hashFull[strlen(hashFull) - 1];
    hDigit = hashDigit - '0';
  }

  newTrans->nonce = nonceTemp;

  if (first == nullptr) {  // empty list
    newTrans->prev = nullptr;
    newTrans->hash = "";
    first = newTrans;
    last = newTrans;
  } else {
    // start checking hash (0~4) from 2nd node
    newTrans->prev = last;
    newTrans->hash = hashFull;
    last = newTrans;
  }
  // finish and free memory
  free(hashFull);
  return true;
}

char* FakeChain::getHash(Transaction* curr, std::string nonceTemp) {
  // add all info from previous transaction to generate hash
  std::string a = std::to_string(curr->amount);
  std::string s = a + curr->sender + curr->receiver + nonceTemp;

  // convert string to char array, declaring character array
  char prevString[s.length() + 1];
  strcpy(prevString, s.c_str());

  // start hashing with SHA256
  unsigned char digest[SHA256_DIGEST_LENGTH];
  SHA256((unsigned char*)&prevString, strlen(prevString),
         (unsigned char*)&digest);
  char mdString[SHA256_DIGEST_LENGTH * 2 + 1];

  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    /* Convert the unsigned int in hexadecimal format to char and store it in
     * variable 'mdString' */
    sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
  }
  // end of SHA256 hashing

  char* ret = (char*)malloc(strlen(mdString) + 1);
  strcpy(ret, mdString);

  // std::string ret(mdString);
  std::cout << ret << "\n";
  std::cout << ret[strlen(ret) - 1] << "\n";
  // char* mdPtr = &mdString[0];
  return ret;
}

std::string FakeChain::getNonce() {
  srand(time(NULL));
  unsigned long tt = clock() - t;
  tt = tt * rand();
  // int ttt = static_cast<int>(tt);
  // std::string nonce = static_cast<std::string>(ttt);
  std::string nonce = std::to_string(tt);
  return nonce;
}

// int FakeChain::

//     // const func
//     bool
//     FakeChain::find(string sender) const {}
void FakeChain::print() {
  Transaction* n = last;
  // Transaction* n = chain.last;
  // std::cout << last->amount;
  while (n) {
    std::cout << "\n"
              << n->sender << " sent " << n->receiver << " " << n->amount
              << " pitCoins \n"
              << "nonce = " << n->nonce << "\n"
              << "SHA256 = " << n->hash << "\n";
    n = n->prev;
  }
  std::cout << "\n"
            << "we are now back to the very first transaction.\n";
}
// int FakeChain::sum() const {}

// string to_string(char c) {}