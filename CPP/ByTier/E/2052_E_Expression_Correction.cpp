// Problem: CF 2052 E - Expression Correction
// https://codeforces.com/contest/2052/problem/E

/*
E. Expression Correction
time limit per test3 seconds
memory limit per test1024 megabytes

Algorithms/Techniques:
- Parsing mathematical expressions with addition and subtraction
- Brute-force digit manipulation: try removing each digit and inserting it at all possible positions
- Evaluation of parsed expressions to check correctness

Time Complexity:
O(n^3) where n is the length of the input string.
- Parsing the expression takes O(n)
- For each digit, we remove it (O(n)) and try inserting at all positions (O(n)) -> O(n^2) for one digit
- We do this for all digits -> O(n^3)

Space Complexity:
O(n) for storing strings and intermediate data structures.

Problem Description:
This program solves an expression correction puzzle. Given a mathematical equality,
it determines if it's correct. If not, it tries to correct it by moving exactly one digit.
If possible, it outputs the corrected equality; otherwise, it outputs "Impossible".
*/
#include <stdint.h>
#include <array>
#include <iostream>
#include <string>

#define int int64_t
using namespace std;

bool check(string s) {
  array<int, 2> n = {0, 0}; // stores the sum of left and right hand side expressions
  int ni = 0;               // index of current expression (0 for left, 1 for right)
  bool neg = 0;             // flag to track if current number is negative
  int cn = 0;               // current number being built from digits
  s.push_back('=');         // add sentinel '=' to simplify processing last term
  bool last_is_digit = 0;   // tracks if the previous character was a digit
  bool lz = 0;              // flag to detect leading zeros (invalid unless the whole number is "0")
  for (auto &c : s) {
    if (c == '-' || c == '+' || c == '=') { // when operator or end of expression encountered
      if (!last_is_digit)
        return 0; // invalid case: operator without preceding digit
      last_is_digit = 0;
      if (neg)
        n[ni] -= cn;   // subtract current number from the sum
      else
        n[ni] += cn;   // add current number to the sum
      neg = 0;
      cn = 0;
      lz = 0;
    }
    if (c >= '0' && c <= '9') { // processing a digit
      if (lz)
        return 0; // invalid: leading zero detected after first digit of number
      int d = c - '0';
      cn = cn * 10 + d;
      if (d == 0 && !last_is_digit)
        lz = 1;     // set leading zero flag if zero is first non-zero digit in a number
      last_is_digit = 1; // mark that we just processed a digit
    }
    if (cn > 9999999999) // overflow check to handle max number length constraint
      return 0;
    if (c == '-')        // toggle neg flag for next number
      neg = !neg;
    if (c == '=')        // advance to next expression side
      ni++;
  }
  return n[0] == n[1];   // return true if both sides are equal
}

signed main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  string s;
  cin >> s;
  if (check(s)) {        // check if input expression is already correct
    cout << "Correct\n";
    return 0;
  }
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] >= '0' && s[i] <= '9') {  // we can only move digits
      string s2 = s;
      s2.erase(s2.begin() + i);        // remove digit at position i
      for (int j = 0; j <= s2.size(); ++j) { // attempt inserting it at each possible position
        string s3 = s2;
        s3.insert(s3.begin() + j, s[i]);   // insert original digit back into string
        if (check(s3)) {                   // validate new expression
          cout << s3 << '\n';
          return 0;
        }
      }
    }
  }
  cout << "Impossible\n";
  return 0;
}


// https://github.com/VaHiX/codeForces/