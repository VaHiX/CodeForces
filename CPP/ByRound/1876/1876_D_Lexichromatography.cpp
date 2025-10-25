// Problem: CF 1876 D - Lexichromatography
// https://codeforces.com/contest/1876/problem/D

/*
 * Problem: D. Lexichromatography
 * 
 * Purpose:
 * This code counts valid colorings (blue/red) of an array such that:
 * 1. The subsequence of blue elements is lexicographically strictly less than red elements.
 * 2. No subarray is imbalanced: the count difference of each value between blue and red is at most 1.
 * 
 * Techniques:
 * - Union-Find (Disjoint Set Union) for grouping indices based on dependencies.
 * - Bit manipulation for fast exponentiation.
 * - Preprocessing to track last occurrences and detect conflicts.
 * 
 * Time Complexity: O(n * α(n)) where α is the inverse Ackermann function (nearly constant).
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

#define rg register
#define file(x)                                                                \
  freopen(x ".in", "r", stdin);                                                \
  freopen(x ".out", "w", stdout)
using namespace std;
const int maxn = 2e6 + 10;
const long long mod = 998244353;
inline long long ksm(long long a, long long b) {
  long long re = 1;
  while (b) {
    if (b & 1)
      re = re * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return re;
}
inline void Adder(long long &x, long long y) {
  if ((x += y) >= mod)
    x -= mod;
}
inline void Reduce(long long &x, long long y) {
  if ((x -= y) < 0)
    x += mod;
}
int n;
int A[maxn];
namespace BCJ {
int Fa[maxn], Size[maxn];
inline void init(const int Lim = n) {
  for (rg int i = 1; i <= n; i += 1)
    Size[Fa[i] = i] = 1;
}
inline int find(int x) { return Fa[x] == x ? x : Fa[x] = find(Fa[x]); }
} // namespace BCJ
bool vis[maxn], Color[maxn];
int Refer[maxn];
inline bool check() {
  vector<int> Red, Blue;
  for (rg int i = 1; i <= n; i += 1)
    if (Color[i])
      Red.emplace_back(A[i]);
    else
      Blue.emplace_back(A[i]);
  return Red == Blue;
}
inline void Cover(int l, int r) {
  for (rg int i = BCJ::find(l); i > r; i = BCJ::find(i))
    BCJ::Fa[i] = i - 1;
}
int main() {
  scanf("%d", &n);
  for (rg int i = 1; i <= n; i += 1)
    scanf("%d", A + i);
  BCJ::init();
  static int lst[maxn];
  for (rg int i = 1; i <= n; i += 1)
    lst[A[i]] = 0;
  int Diff = 0;
  Color[0] = 1;
  for (rg int i = 1; i <= n; i += 1) {
    Refer[i] = lst[A[i]];     // Store the last occurrence of A[i]
    Color[i] = Color[Refer[i]] ^ 1; // Determine color based on previous occurrence
    lst[A[i]] = i;            // Update the last occurrence
    if (Refer[i] && !vis[Refer[i]]) {
      vis[Refer[i]] = vis[i] = true;
      Cover(i, Refer[i]);     // Union consecutive elements to enforce constraints
    }
    if (!Refer[i])
      Diff += 1;              // Count unique values (for valid colorings)
  }
  for (rg int i = 1; i <= n; i += 1)
    if (Refer[i])
      BCJ::Fa[BCJ::find(i)] = BCJ::find(Refer[i]); // Merge related components
  int Con = 0;
  for (rg int i = 1; i <= n; i += 1)
    Con += BCJ::find(i) == i; // Count disjoint components
  long long Ans = ksm(2, Diff - 1); // Total valid colorings before constraint adjustment
  if (check()) // If the coloring results in same subsequences
    Reduce(Ans, ksm(2, Con - 1)); // Subtract invalid cases
  printf("%lld\n", Ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/