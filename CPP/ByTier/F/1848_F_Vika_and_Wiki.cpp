// Problem: CF 1848 F - Vika and Wiki
// https://codeforces.com/contest/1848/problem/F

/*
Algorithm: Recursive approach with bit manipulation
Techniques: Bitwise XOR, Divide and Conquer, Pattern recognition

Time Complexity: O(n), where n is the size of the input array.
Space Complexity: O(log n), due to recursion depth.

The key insight is that the operation a[i] = a[i] ^ a[(i+1) % n] can be viewed as
a transformation on the array. The recurrence relation is structured in a way
that allows us to reduce the problem size by half recursively.

The algorithm works by:
1. If n == 1, return 1 if the element is non-zero, 0 otherwise.
2. Check if the first half of the array equals the second half.
   - If yes, we can reduce the problem size by half.
   - If no, perform XOR operation and recurse on the reduced array.
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define ll long long
using namespace std;
const int N = 1 << 20;
char getch() {
  static char buf[100000], *s, *s2;
  return (s == s2) && (s2 = (s = buf) + fread(buf, 1, 100000, stdin)),
         s == s2 ? EOF : *s++;
}
int read() {
  int x = 0, w = 1;
  char ch = 0;
  while (!isdigit(ch)) {
    if (ch == '-')
      w = -1;
    ch = getch();
  }
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getch();
  return x * w;
}
int t, n, m, k;
void init() {}
int Solve(int n, vector<int> &a) {
  if (n == 1)
    return a[0] > 0;  // Base case: if single element and non-zero, need 1 step
  bool ok = true;
  for (int i = 0; i < n / 2; ++i) {
    ok &= (a[i] == a[i + n / 2]);  // Check if first and second halves are equal
  }
  if (ok)
    return Solve(n / 2, a);  // If equal, recursively solve for half the array
  else {
    for (int i = 0; i < n / 2; ++i) {
      a[i] ^= a[i + n / 2];  // XOR the second half with the first
    }
    return n / 2 + Solve(n / 2, a);  // Add steps needed to process current layer
  }
}
void charming() {
  init();
  n = read();
  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    a[i] = read();
  cout << Solve(n, a) << endl;
}
signed main() {
  charming();
  return 0;
}


// https://github.com/VaHiX/CodeForces/