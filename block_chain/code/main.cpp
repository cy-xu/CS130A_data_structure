/*
assignment one, block chain
use this command to compile

g++ -std=c++11 block_chain.cpp main.cpp -o main -I
/usr/local/Cellar/openssl/1.0.2p/include -L /usr/local/Cellar/openssl/1.0.2p/lib
-lcrypto

CY Xu, 2018
*/

#include <stdlib.h> /* atoi */
#include <iostream>

#include "block_chain.h"

// using namespace std;

void addTestCase(FakeChain* chain) {
  int amount;
  // char buffer[256];
  std::string numString;
  std::string sender;
  std::string receiver;

  std::cout << "How much to transfer? Amount (int):";
  std::cin >> amount;

  std::cout << "Who is the Sender(string): ";
  std::cin >> sender;

  std::cout << "Who is the Receiver(string):";

  std::cin >> receiver;

  if (chain->add(amount, sender, receiver)) {
    std::cout << "Amount: " << chain->last->amount << "\n"
              << "Sender: " << chain->last->sender << "\n"
              << "Receiver: " << chain->last->receiver << "\n"
              << "Nonce: " << chain->last->nonce << "\n"
              << "Hash: " << chain->last->hash << "\n"
              << "Success.\n";
  } else
    std::cout << "Something went wrong.\n";
}

int moreTest() {
  std::cout << "Which operation do you want to make? (1 ,2 ,3 or 0 to exit):\n";

  do {
    int choice = 99;
    std::cout << "Enter choice: ";
    std::cin >> choice;
    if (choice >= 0 && choice <= 3) return choice;
    std::cout << "0, 1, 2, 3 only! \n";
  } while (true);
}

void startTest() {
  std::cout << "Welcome to the transaction−chain application... \n"
            << "1) Add a transaction to the chain.\n"
            << "2) Find a transaction with name of receiver or sender.\n"
            << "3) Verify and print the chain.\n";
}

int main() {
  FakeChain firstChain;
  int testCase;

  startTest();

  while (true) {
    testCase = moreTest();

    if (testCase == 1) {
      addTestCase(&firstChain);
    }

    if (testCase == 3) {
      firstChain.print();
    }

    if (testCase == 0) return 0;
  }

  return 0;
}
