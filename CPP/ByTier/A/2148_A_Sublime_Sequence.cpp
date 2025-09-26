// Problem: CF 2148 A - Sublime Sequence
// https://codeforces.com/contest/2148/problem/A

#include <iostream>

using namespace std;
int main() {
  int tt;
  cin >> tt;
  while (tt--) {
    int n, x;
    cin >> x >> n;
    if (n % 2 == 0)  // If length is even, pairs of x and -x cancel out
      cout << '0' << endl;
    else  // If length is odd, last element is x and all pairs cancel out
      cout << x << endl;
  }
}

/*
Problem: Sublime Sequence
Algorithm: Mathematical pattern recognition
Time Complexity: O(1) per test case
Space Complexity: O(1)

Farmer John creates a sequence of length n by alternating integers x and -x, starting with x.
For example, if n=5, the sequence looks like: x, -x, x, -x, x.
The sum follows a pattern:
- If n is even: all pairs (x, -x) cancel out to 0
- If n is odd: all pairs cancel out except the last x, so sum is x

Input: t test cases, each with integers x and n
Output: Sum of sequence for each test case
*/

// https://github.com/VaHiX/codeForces/