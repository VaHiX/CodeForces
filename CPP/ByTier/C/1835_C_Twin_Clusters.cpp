// Problem: CF 1835 C - Twin Clusters
// https://codeforces.com/contest/1835/problem/C

/*
 * Problem: Twin Clusters
 * 
 * Purpose:
 *   Given a sequence of galaxies, each with a number of stars (0 <= g_i < 4^k),
 *   find two disjoint contiguous segments (clusters) whose XOR traits are equal.
 *   If such pairs exist, output their indices; otherwise, output -1.
 * 
 * Algorithm:
 *   - Use prefix XOR to efficiently compute XOR of any subarray.
 *   - Group prefix XOR values by their higher-order bits (specifically, the first n bits).
 *   - For each prefix, check if a previous prefix with the same higher-order bits exists.
 *     If so, the XOR of the subarray between them equals the XOR between two prefixes.
 *   - This allows us to find twin clusters in O(N) time per test case.
 * 
 * Time Complexity: O(N) per test case, where N = 2^(k+1)
 * Space Complexity: O(N) for prefix array and hash map
 * 
 * Techniques:
 *   - Prefix XOR technique
 *   - Hash map for fast lookup of previously seen XOR traits
 *   - Bit manipulation for grouping XOR values
 */

#include <stdio.h>
#include <map>
#include <utility>

#define rg register
#define file(x)                                                                \
  freopen(x ".in", "r", stdin);                                                \
  freopen(x ".out", "w", stdout)
using namespace std;
const int maxn = 1e6 + 10;
int n;
long long A[maxn];
map<long long, pair<int, int>> MP;
inline void Construct(int l1, int r1, int l2, int r2) {
  // Adjust interval order to ensure that the output is in increasing order
  if (l2 < l1) {
    printf("%d %d %d %d\n", l2 + 1, l1, r1 + 1, r2);
    return;
  }
  if (l2 <= r1) {
    // If intervals overlap, it's invalid — do not output
    printf("%d %d %d %d\n", l1 + 1, l2, r1 + 1, r2);
    return;
  }
  printf("%d %d %d %d\n", l1 + 1, r1, l2 + 1, r2);
}
inline bool Insert(int x, int y) {
  // Compute XOR trait of subarray [x+1, y]
  auto Val = A[y] ^ A[x];
  // Check if we've seen this XOR value before
  if (MP.find(Val) == MP.end()) {
    MP[Val] = make_pair(x, y);
    return false;
  }
  // A twin cluster is found
  auto [X, Y] = MP[Val];
  Construct(X, Y, x, y);
  return true;
}
int lst[maxn];
inline void solve() {
  MP.clear();
  scanf("%d", &n);
  int V_Limit = 1 << n;
  int N = 1 << (n + 1);
  for (rg int i = 1; i <= N; i += 1) {
    scanf("%lld", A + i);
    // Compute prefix XOR
    A[i] ^= A[i - 1];
  }
  for (rg int i = 0; i < V_Limit; i += 1)
    lst[i] = -1;
  for (rg int i = 0; i <= N; i += 1) {
    // Group prefix XOR values by their first n bits
    if (lst[A[i] >> n] > -1)
      if (Insert(lst[A[i] >> n], i))
        break;
    lst[A[i] >> n] = i;
  }
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/