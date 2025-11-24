// Problem: CF 2013 C - Password Cracking
// https://codeforces.com/contest/2013/problem/C

/*
Purpose: This code is designed to deduce a hidden binary password of length n by asking queries about substrings.
         It uses a greedy approach to determine each character of the password one by one.

Algorithms/Techniques:
- Greedy approach for building the string character by character
- Binary search-like logic using substring queries to determine character values
- Two phases:
  1. Extend the string by appending '0' or '1' (from the end)
  2. Prepend '0' or '1' (from the beginning)

Time Complexity: O(n^2) in the worst case due to up to 2n queries and each query taking O(n) time to check substring.
Space Complexity: O(n) for storing the intermediate string t and the final password.

*/
#include <iostream>
#include <string>

using namespace std;
int ask(string s) {
  cout << "? " << s << endl;
  int op;
  cin >> op;
  return op;
}
void Showball() {
  int n;
  cin >> n;
  string t = "";
  // Phase 1: Build the string from the end by appending '0' or '1'
  while (t.size() < n) {
    if (ask(t + '0'))  // If appending '0' gives a valid substring, use it
      t = t + '0';
    else if (ask(t + '1'))  // If appending '1' gives a valid substring, use it
      t = t + '1';
    else
      break;  // Neither '0' nor '1' works, so stop
  }
  // Phase 2: Build the string from the beginning by prepending '0' or '1'
  while (t.size() < n) {
    if (ask('1' + t)) {  // If prepending '1' gives a valid substring, use it
      t = '1' + t;
    } else
      t = '0' + t;  // Otherwise, prepend '0'
  }
  cout << "! " << t << endl;
}
int main() {
  int t;
  cin >> t;
  while (t--)
    Showball();
}


// https://github.com/VaHiX/CodeForces/