// Problem: CF 2143 E - Make Good
// https://codeforces.com/contest/2143/problem/E

/*
E. Make Good

Purpose:
This code attempts to transform a given bracket string into a valid (regular) bracket sequence by using two specific operations:
1. Replace "((" with "))" 
2. Replace "))" with "(("

Algorithm:
The approach involves analyzing the input string and determining if it's possible to form a valid bracket sequence.
It applies several checks:
- First, it ensures that the total imbalance (sum of '(' vs ')') is divisible by 4 and that the length is even — necessary conditions to potentially form a valid bracket string.
- Then, it simulates a stack-like operation on the input string to reduce consecutive brackets.
- A final check ensures the reduced sequence can be properly balanced with the allowed operations.

Time Complexity: O(n) where n is the length of the input string (each character processed at most twice).
Space Complexity: O(n) for storing the input and auxiliary arrays.

*/

#include <iostream>

#define maxn 200005
using namespace std;
int Test, n, acm, top;
bool a[maxn], gogo[maxn], b[maxn], stk[maxn];
inline void solve() {
  cin >> n;
  int sigma = 0;
  ++acm;
  for (int i = 1; i <= n; ++i) {
    char czs;
    cin >> czs;
    a[i] = (czs == '('); // Convert character to boolean: 1 for '(', 0 for ')'
    if (a[i])
      ++sigma;
    else
      --sigma;
    gogo[i] = 0; // Initialize gogo array (unused in current logic)
  }
  if ((sigma % 4 + 4) % 4 != 0) { // Check if total balance mod 4 is zero (necessary condition)
    cout << -1 << "\n";
    return;
  }
  if (n & 1) { // Odd-length string cannot form a valid bracket sequence
    cout << -1 << "\n";
    return;
  }
  int cnt = 0, noi = 0;
  for (int i = 1; i <= n; ++i) {
    b[++noi] = a[i]; // Push current character onto reduced array
    if (noi >= 2 && b[noi] == b[noi - 1]) { // If two adjacent characters are same
      noi -= 2; // Remove last two elements (simulate stack pop)
      ++cnt; // Increment count of pairs removed
    }
  }
  if (cnt % 2 == 1) { // If the number of pairs removed is odd, not possible to balance
    cout << -1 << "\n";
    return;
  }
  if (!b[1]) { // If first element in stack-like array is ')'
    cnt -= 2; // Use two extra pairs from beginning
    if (cnt < 0) { // Not enough valid pairs
      cout << -1 << "\n";
      return;
    }
    cout << "(("; // Add opening brackets at start
    for (int i = 1; i <= noi; ++i) {
      if (b[i])
        cout << "(";
      else
        cout << ")";
    }
    cout << "))"; // Add closing brackets at end
    for (int i = 1; i <= cnt / 2; ++i)
      cout << "(("; 
    for (int i = 1; i <= cnt / 2; ++i)
      cout << "))";
  } else { // If first element in stack is '('
    for (int i = 1; i <= noi; ++i) {
      if (b[i])
        cout << "(";
      else
        cout << ")";
    }
    for (int i = 1; i <= cnt / 2; ++i)
      cout << "((";
    for (int i = 1; i <= cnt / 2; ++i)
      cout << "))";
  }
  cout << "\n";
  return;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> Test;
  while (Test--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/