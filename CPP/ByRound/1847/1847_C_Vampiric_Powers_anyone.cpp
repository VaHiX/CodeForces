// Problem: CF 1847 C - Vampiric Powers, anyone?
// https://codeforces.com/contest/1847/problem/C

/*
Purpose: This code solves the problem of finding the maximum possible strength of a Stand user that can be summoned by DIO using XOR operations on existing strengths.

Algorithm:
- Uses a Trie data structure to efficiently store and query prefix XOR values.
- For each element in the input array, we compute the prefix XOR and use the trie to find the best previous prefix xor to maximize the result of XOR operations.
- The maximum XOR of any two elements from the prefix array is computed using the trie.

Time Complexity: O(N * 8) per test case, where N is the number of elements. Since 8 is constant, effectively O(N).
Space Complexity: O(N * 8) for the trie structure, which is effectively O(N) as 8 is constant.

Techniques:
- Prefix XOR
- Trie (Trie-based maximum XOR query)

*/
#include <algorithm>
#include <cstdio>

#define LL long long
#define maxn int(2e5 + 5)
#define is(a) (a >= '0' && a <= '9')
#define iabs(a) ((a) > 0 ? (a) : (-a))
#define imax(a, b) ((a) > (b) ? (a) : (b))
#define imin(a, b) ((a) < (b) ? (a) : (b))
using namespace std;
int N, T, ans, a[maxn], n, g[maxn], sum[maxn];
int b[maxn][2];
inline void read(int &x) {
  x = 0;
  bool f = 0;
  char ch = getchar();
  for (; !is(ch); ch = getchar())
    f |= ch == '-';
  for (; is(ch); ch = getchar())
    x = (x << 3) + (x << 1) + (ch ^ 48);
  x = f ? -x : x;
}
void pus(int x) {
  int p = 0;
  for (int i = 7; i >= 0; --i) {
    int ji = 1 << i;
    int y = (x & ji) ? 1 : 0;
    // If the bit is already present in trie, go to that node.
    if (b[p][y])
      p = b[p][y];
    else
      // Otherwise, create a new node and move to it.
      ++n, b[p][y] = n, p = b[p][y];
  }
  g[p] = x; // Store the value at the end of the trie path.
  return;
}
int que(int x) {
  int p = 0;
  for (int i = 7; i >= 0; --i) {
    int ji = 1 << i;
    int y = (x & ji) ? 1 : 0;
    // Try to go the path that maximizes XOR (opposite bit).
    if (b[p][y ^ 1])
      p = b[p][y ^ 1];
    else
      // If not possible, follow the same bit.
      p = b[p][y];
  }
  return g[p]; // Return the stored value (best prefix XOR for current x)
}
int main() {
  read(T);
  while (T--) {
    read(N);
    ans = 0;
    pus(0); // Initialize the trie with 0
    for (int i = 1; i <= N; ++i) {
      read(a[i]);
      sum[i] = sum[i - 1] ^ a[i]; // Compute prefix XOR
      int x = que(sum[i]); // Query for maximum XOR with current prefix
      pus(sum[i]); // Insert current prefix into trie
      ans = max(ans, x ^ sum[i]); // Update maximum strength
    }
    printf("%d\n", ans);
    // Reset trie for next test case
    for (int i = 0; i <= n; ++i)
      g[i] = 0, b[i][0] = b[i][1] = 0;
    n = 0;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/