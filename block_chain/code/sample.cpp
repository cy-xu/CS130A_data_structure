/*
To install OpenSSL on Debian, Ubuntu, or other derivative versions:

$ sudo apt-get install libssl-dev

To install the OpenSSL development kit on Fedora, CentOS, or RHEL:

$ sudo yum install openssl-devel

To compile cpp

$ g++ sample.cpp -o sample -lcrypto
*/

#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>

#include <iostream>  // for time ()
using namespace std;

int main() {
  unsigned char digest[SHA256_DIGEST_LENGTH];
  char string[] = "hello world!";

  SHA256((unsigned char*)&string, strlen(string), (unsigned char*)&digest);
  // printf("SHA256 digest hexadecimal format: %s\n\n", digest);
  cout << "SHA256 digest hexadecimal format: " << digest << endl;

  char mdString[SHA256_DIGEST_LENGTH * 2 + 1];

  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    /* Convert the unsigned int in hexadecimal format to char and store it in
     * variable 'mdString' */
    sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
  }

  printf("SHA256 digest: %s\n", mdString);

  return 0;
}
