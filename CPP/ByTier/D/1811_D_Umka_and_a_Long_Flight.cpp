// Problem: CF 1811 D - Umka and a Long Flight
// https://codeforces.com/contest/1811/problem/D

/*
 * Problem: Umka and a Long Flight
 *
 * Purpose: Determine if a Fibonacci rectangle can be tiled with exactly n+1
 * squares, such that one square has side 1 and at most one pair of squares have
 * equal sides.
 *
 * Algorithm:
 * - This is a recursive tiling problem based on the Fibonacci tiling property.
 * - The solution uses a depth-first search (DFS) to simulate how the tiling
 * would proceed.
 * - Each step reduces the problem to a smaller Fibonacci rectangle, maintaining
 * the constraint that the painted cell must lie in a unit square.
 *
 * Time Complexity: O(n) per test case, where n is the order of Fibonacci
 * rectangle. Space Complexity: O(n) for storing Fibonacci numbers and recursion
 * stack.
 */

#include <iostream>
#include <stdio.h>

#define int long long
using namespace std;

namespace IO {
char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh()                                                                   \
  (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin),         \
   (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
inline long long read() {
  char ch = gh();
  long long x = 0;
  char t = 0;
  while (ch < '0' || ch > '9')
    t |= ch == '-', ch = gh();
  while (ch >= '0' && ch <= '9')
    x = x * 10 + (ch ^ 48), ch = gh();
  return t ? -x : x;
}
} // namespace IO
using IO::read;

int fib[50]; // Precomputed Fibonacci numbers up to F_44

// Recursive DFS function to determine valid tiling
// n: current order of rectangle
// a: height of current rectangle (F_n)
// b: width of current rectangle (F_{n+1})
// x, y: coordinates of the colored cell in current rectangle
bool dfs(int n, int a, int b, int x, int y) {
  // Base case: when we reach order 1, it's always valid
  if (n == 1)
    return 1;

  // Calculate half width of the current rectangle
  int p = b / 2;

  // Adjust y coordinate based on reflection rule
  if (y <= p)
    y = b + 1 - y;

  // Check if y is within the valid range for tiling
  if (y <= a)
    return 0;

  // Recursively solve for the next smaller Fibonacci rectangle
  return dfs(n - 1, b - a, a, y - a, x);
}

void solve() {
  int n, x, y;
  n = read(), x = read(), y = read();
  int a = fib[n], b = fib[n + 1];

  // Call DFS to check if valid tiling exists
  if (dfs(n, a, b, x, y))
    cout << "YES\n";
  else
    cout << "NO\n";
}

signed main() {
  // Precompute Fibonacci numbers
  fib[0] = 1, fib[1] = 1;
  for (int i = 2; i <= 45; i++)
    fib[i] = fib[i - 1] + fib[i - 2];

  int t;
  t = read();
  while (t--)
    solve();
  return 0;
}

// https://github.com/VaHiX/CodeForces/