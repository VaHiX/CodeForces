// Problem: CF 1906 G - Grid Game 2
// https://codeforces.com/contest/1906/problem/G

/*
 * Problem: Grid Game 2
 * Algorithm: Sprague-Grundy Theorem + Nim Game
 * 
 * The game is a Nim-like game on a 2D grid where each move toggles a sub-grid.
 * The key insight is to compute the Grundy number (Nimber) for each black cell.
 * The Grundy number for a cell (r, c) is computed as XOR of four values:
 *   - S(r, c)
 *   - S(r, c-1)
 *   - S(r-1, c)
 *   - S(r-1, c-1)
 * where S(x, y) computes the XOR of all Grundy numbers for subproblems.
 * 
 * Time Complexity: O(N * log(max(R,C))) where N <= 2e5
 * Space Complexity: O(1) - Only a few variables used.
 */

#include <ctype.h>
#include <stdio.h>
#include <iostream>

#pragma GCC optimize("Ofast")
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
int n, x, y, xx, yy, zz;
bool z;
// Function S computes the Grundy number using recursion with memoization
bool S(int x, int y) { return y ? (S(y, x % y) ^ ((x / y) & 1)) : 0; }
// Function F computes the Grundy number for cell (x, y)
bool F(int x, int y) {
  return S(x, y) ^ S(x, y - 1) ^ S(x - 1, y) ^ S(x - 1, y - 1);
}
void main() {
  // Read number of black cells
  for (n = read(), z = 0; n--;)
    x = read(), y = read(), // Read cell coordinates
    z ^= F(x, y); // Accumulate XOR of Grundy numbers for all cells
  printf(z ? "FIRST\n" : "SECOND\n");
}
} // namespace Main
int main() {
  const bool base = 0, IO = 1;
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