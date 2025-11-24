// Problem: CF 1930 F - Maximize the Difference
// https://codeforces.com/contest/1930/problem/F

/*
 * Problem: Maximize the Difference
 * Algorithm/Technique: Bit manipulation with trie-like structure
 *
 * Time Complexity: O(q * log n), where q is the number of queries and n is the size of the array.
 * Space Complexity: O(n), due to the boolean flag array used to track reachable values.
 *
 * This solution uses a clever bit manipulation trick to efficiently compute the maximum
 * difference between the max and min of the array after each query.
 * The key idea is to maintain two sets:
 *   - T0: contains all possible values that can be achieved by OR-ing elements with some x.
 *   - T1: contains all current elements in the array.
 * Then, we try to find the largest value that is present in both sets to compute the maximum difference.
 */
#include <stdio.h>
#include <iosfwd>

using namespace std;
struct VG{
  bool fl[1 << 22]; // Boolean array to mark reachable values (bit manipulation optimization)
  void co(int x) {
    if (fl[x])
      return;
    fl[x] = 1;
    for (int p = x; p; p -= (p & -p)) // Clear lowest set bit iteratively
      co(x ^ (p & -p)); // Toggle bits of x to find all combinations
  }
  void init(int n) {
    for (int i = 0; i < n; ++i)
      fl[i] = 0;
  }
} T1, T0;
void sol() {
  int n, q;
  scanf("%d%d", &n, &q);
  int e = 1, z = 0;
  while (e < n)
    e <<= 1, z++; // Find smallest power of 2 >= n and calculate bit length z
  T0.init(e);
  T1.init(e);
  int ans = 0;
  for (int i = 1, a; i <= q; ++i) {
    scanf("%d", &a);
    (a += ans) %= n; // Decrypt the value using previous output
    T0.co(a ^ ((1 << z) - 1)); // Mark all possible XOR values with all bits set
    T1.co(a); // Mark current value
    int st = 0;
    for (int j = z - 1; j >= 0; --j)
      if (T0.fl[st | (1 << j)] && T1.fl[st | (1 << j)]) // Try to build result greedily
        st |= 1 << j;
    printf("%d\n", ans = st); // Output result for this query
  }
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    sol();
}


// https://github.com/VaHiX/CodeForces/