// Problem: CF 2027 D2 - The Endspeaker (Hard Version)
// https://codeforces.com/contest/2027/problem/D2

/*
 * Problem: D2. The Endspeaker (Hard Version)
 *
 * Purpose:
 *   This code solves a dynamic programming problem involving minimizing the cost to reduce an array 'a' 
 *   to empty using two types of operations, while also counting the number of ways achieving that minimum.
 *
 * Algorithms/Techniques:
 *   - Dynamic Programming with Sliding Window Optimization
 *   - Two-pointer technique for efficiently maintaining prefix sums and update counts
 *   - Modular arithmetic for result handling (`mod = 1e9 + 7`)
 *
 * Time Complexity: O(n * m)
 * Space Complexity: O(n)
 */

#include <ctype.h>
#include <iosfwd>
#include <stdio.h>
#include <string.h>
#define EL puts("Elaina")
typedef long long ll;
using namespace std;
namespace IO {
const int siz = 1 << 18; // Input buffer size for fast I/O
char buf[siz], *p1, *p2;
inline char getc() {
  return p1 == p2 && (p2 = buf + fread(p1 = buf, 1, siz, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
inline int read() {
  int x = 0;
  char ch = getc();
  bool f = 1;
  while (!isdigit(ch))
    ch == '-' && (f = 0), ch = getc(); // Skip non-digit chars (handle negatives)
  while (isdigit(ch))
    x = x * 10 + (ch ^ 48), ch = getc(); // Build integer from digits
  return f ? x : -x;
}
} // namespace IO

using IO::read;

const int maxn = 3e5 + 3, mod = 1e9 + 7; // Constants for problem limits and modulus
int n, m, a[maxn], b[maxn], g[maxn];      // Arrays: input array 'a', cost array 'b', count of ways 'g'
ll f[maxn];                               // dp array storing minimum cost to process first i elements

inline void add(int &x, const int y) { (x += y) >= mod && (x -= mod); }
// Helper: Adds two numbers (modularly), handles overflow properly

inline void MyDearMoments() {
  n = read(), m = read();                             // Read input values
  int tmp = 0;
  for (int i = 1; i <= n; ++i)
    a[i] = read(), a[i] > tmp && (tmp = a[i]);        // Read elements of array 'a' and find max
  for (int i = 1; i <= m; ++i)
    b[i] = read();                                    // Read cost array 'b'

  if (tmp > b[1]) {                                   // If largest element of 'a' exceeds first cost, impossible
    puts("-1");
    return;
  }

  memset(f + 1, 0x3f, n * sizeof(ll));                // Initialize DP array with large values (infty)
  g[0] = 1;                                           // Base case: 1 way to reach zero elements

  for (int k = 1; k <= m; ++k) {                      // Iterate over each step of using cost b[k]
    ll sum = 0;
    int ts = 0;                                       // ts keeps track of total combinations so far
    for (int i = 1, j1 = 1, j2 = 0; i <= n; ++i) {
      sum += a[i];                                    // Expand the current window by including a[i]

      // Shrink window from left if sum exceeds current budget b[k]
      while (j1 <= i && sum > b[k])
        sum -= a[j1], add(ts, mod - g[j1 - 1]), ++j1;

      if (j2 < j1)
        j2 = j1, ts = g[j1 - 1];                      // Reset tracking when necessary

      // Maintain consistency in case of equal DP values
      while (j2 < i && f[j2] == f[j1 - 1])
        add(ts, g[j2++]);

      if (j1 <= i) {
        // Update state for current index using two conditions:
        //   If new state is better, update it and reset count.
        //   If same cost, accumulate the number of ways to such state.
        if (f[j1 - 1] + m - k < f[i])
          f[i] = f[j1 - 1] + m - k, g[i] = ts;
        else if (f[j1 - 1] + m - k == f[i])
          add(g[i], ts);
      }
    }
  }

  printf("%lld %d\n", f[n], g[n]);                    // Output the minimum cost and number of optimal sequences
}

int main() {
  int T = read();
  while (T--)
    MyDearMoments();                                 // Process all test cases one by one
  return 0;
}


// https://github.com/VaHiX/codeForces/