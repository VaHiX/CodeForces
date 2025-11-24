// Problem: CF 2160 B - Distinct Elements
// https://codeforces.com/contest/2160/problem/B

/*
B. Distinct Elements
Algorithms/Techniques: Simulation, Array Reconstruction
Time Complexity: O(n) per test case
Space Complexity: O(n) for the array 'a' and 'b'

Given an array b where each element bi represents the sum of distinct elements in all subarrays ending at position i,
the task is to reconstruct a valid array a such that the computed b matches the input b.

The approach works as follows:
- For each position i, we compute the difference d = b[i] - b[i-1].
- We then determine the index p = i - d.
- If p <= 0, a[i] is assigned a new unique number (incrementing nl).
- Otherwise, we assign a[i] = a[p], maintaining consistency with previous assignments.
This ensures that each element in 'a' reflects how the distinct count changes and helps to satisfy all b values.
*/
#include <ctype.h>
#include <stdio.h>
#include <iosfwd>

using namespace std;
#ifdef __linux__
#define gc getchar_unlocked
#define pc putchar_unlocked
#else
#define gc _getchar_nolock
#define pc _putchar_nolock
#endif
#define int long long
#define R register
#define rint register int
#define _ read<int>()
inline bool blank(const char x) {
  return !(x ^ 9) || !(x ^ 13) || !(x ^ 10) || !(x ^ 32);
}
template <class T> inline T read() {
  T r = 0, f = 1;
  R char c = gc();
  while (c != EOF && !isdigit(c)) {
    if (c == '-')
      f = -1;
    c = gc();
  }
  while (isdigit(c))
    r = (r << 1) + (r << 3) + (c ^ 48), c = gc();
  return f * r;
}
inline void out(int x) {
  if (x < 0)
    pc('-'), x = -x;
  if (x < 10)
    pc(x + '0');
  else
    out(x / 10), pc(x % 10 + '0');
}
inline void read(char &x) {
  for (x = gc(); blank(x) && (x ^ -1); x = gc())
    ;
}
signed main() {
  rint T = _;
  static int b[200005], a[200005];
  while (T--) {
    rint n = _;
    for (rint i = 1; i <= n; ++i)
      b[i] = _;
    int pb = 0, nl = 0;
    for (rint i = 1; i <= n; ++i) {
      int d = b[i] - pb; // Difference between consecutive b values
      pb = b[i];         // Update previous value
      int p = i - d;     // Determine which prior index to reference
      if (p <= 0)
        a[i] = ++nl;     // Assign new number if out of bounds
      else
        a[i] = a[p];     // Reuse previously assigned number
    }
    for (rint i = 1; i <= n; ++i) {
      out(a[i]);
      if (i == n)
        pc('\n');
      else
        pc(' ');
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/