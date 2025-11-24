// Problem: CF 1994 E - Wooden Game
// https://codeforces.com/contest/1994/problem/E

/*
Purpose: This code solves the "Wooden Game" problem where we are given a forest of rooted trees,
         and we want to maximize the bitwise OR of the sizes of subtrees removed in a sequence of operations.
         
Algorithms/Techniques: 
- For each tree, we compute the maximum possible bitwise OR of the sizes of subtrees that can be removed.
- The key insight is that to maximize the OR, we should try to include larger subtree sizes.
- The maximum OR value that can be achieved for a tree of size n is determined by taking the maximum over all possible subtree sizes,
  and using the OR operation to combine them.
- For any tree of size n, we process each vertex and greedily compute what maximum OR we can get by taking the current vertex' size.

Time Complexity: O(n) per test case, where n is the total number of vertices across all trees.
Space Complexity: O(n) for storing the tree structure and auxiliary arrays.

*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#ifdef ONLINE_JUDGE
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
#endif
using namespace std;
int read() {
  int num = 0, f = 1;
  char c;
  while (!isdigit(c = getchar()))
    if (c == '-')
      f = -1;
  while (isdigit(c))
    num = num * 10 + (c & 15), c = getchar();
  return num * f;
}
void write(int x, char ch = ' ') {
  int F[20], cnt = 0;
  if (!x)
    putchar('0');
  if (x < 0)
    putchar('-'), x = -x;
  while (x)
    F[cnt++] = x % 10 + '0', x /= 10;
  while (cnt)
    putchar(F[--cnt]);
  putchar(ch);
}
namespace Main {
const int N = 200010;
int n, a[N], x, y, z, xx, yy, zz;
void main() {
  for (n = read(), z = 0; n--;) { // Process each tree
    x = read(), y = z;
    for (int i = 1; i <= x; ++i)
      z = max(z, y | i); // Compute maximum OR as we go through the vertices
    for (; --x;)
      read(); // Read and discard the parent information
  }
  write(z, '\n'); // Output the final maximum OR
}
}; // namespace Main
int main() {
  const bool base = 1, IO = 1;
  int T;
  if (!base)
    T = 1;
  else if (IO)
    T = read();
  else
    ios::sync_with_stdio(0), cin >> T;
  for (; T--;)
    Main::main();
  return 0;
}


// https://github.com/VaHiX/CodeForces/