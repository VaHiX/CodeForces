// Problem: CF 1219 C - Periodic integer number
// https://codeforces.com/contest/1219/problem/C

/*
C. Periodic integer number
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Alice became interested in periods of integer numbers. We say positive X integer number is periodic with length L if there exists positive integer number P with L digits such that X can be written as PPPP…P. For example:
X = 123123123 is periodic number with length L = 3 and L = 9
X = 42424242 is periodic number with length L = 2,L = 4 and L = 8
X = 12345 is periodic number with length L = 5

For given positive period length L and positive integer number A, Alice wants to find smallest integer number X strictly greater than A that is periodic with length L.

Algorithm:
- If the input number A has a digit pattern that is all 9s or if its length is not divisible by L, then we need to consider creating a longer string of repeated patterns.
- Otherwise:
   - Take prefix of length L from A
   - Check if the cyclic repetition of this prefix is less than A, if so increment it by 1
   - Output the repeated cycle

Time Complexity: O(n) where n is the length of the input number A
Space Complexity: O(n) for storing the string representation of A and intermediate results
*/

#include <iostream>
#include <string>

int main() {
  long r; // period length
  std::cin >> r;
  std::string s; // input number as string
  std::cin >> s;
  bool allnines(true); // flag to check if all digits are '9'
  for (long p = 0; allnines && p < s.size(); p++) {
    if (s[p] != '9') {
      allnines = false;
    }
  }
  if (allnines || (s.size() % r)) { // if input is all 9s or length not divisible by period
    long n = 1 + s.size() / r; // compute number of repetitions needed
    std::string t(r, '0'); // create a string with r zeros
    t[0] = '1'; // set first digit to 1 to make it the smallest possible
    for (long p = 0; p < n; p++) {
      std::cout << t; // output repeated pattern
    }
    std::cout << std::endl;
  } else {
    std::string t = s.substr(0, r); // extract first r digits as the pattern
    bool smaller(false); // flag to determine if current pattern is smaller than A's cyclic representation
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == t[p % r]) {
        continue;
      }
      if (s[p] < t[p % r]) {
        smaller = true;
      }
      break;
    }
    if (!smaller) { // if pattern is not smaller, increment it
      for (long p = t.size() - 1; p >= 0; p--) {
        if (t[p] == '9') {
          t[p] = '0'; // carry over when digit is 9
        } else {
          ++t[p]; // increment the digit
          break;
        }
      }
    }
    for (long p = 0; p < s.size() / r; p++) {
      std::cout << t; // output the pattern repeated for required length
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/