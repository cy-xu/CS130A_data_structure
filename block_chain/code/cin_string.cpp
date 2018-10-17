// cin with strings
#include <iostream>
#include <string>
using namespace std;

int main() {
  string mystr;
  int num;
  char buffer[256];

  cout << "Tell me a number? ";
  fgets(buffer, 256, stdin);
  num = atoi(buffer);
  cout << "This is num " << num << ".\n";

  cout << "What's your name? ";
  getline(cin, mystr);

  // cin >> mystr >> mystr2;
  cout << "Hello " << mystr << ".\n";

  cout << "What is your favorite team? ";
  getline(cin, mystr);
  cout << "I like " << mystr << " too!\n";
  return 0;
}