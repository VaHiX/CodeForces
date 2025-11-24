// Problem: CF 1687 E - Become Big For Me
// https://codeforces.com/contest/1687/problem/E

/*
Algorithm: 
  This solution attempts to find a sequence of operations to transform v = 1 into the GCD of all pairwise products of elements in array a.
  - The key idea is to decompose numbers into prime factors and identify which subsets of elements contribute to the final GCD.
  - It uses a greedy approach to select sub-sequences for enlarge/reduce operations to manipulate v towards the target GCD.
  - It iterates through all possible combinations of selected indices using bitmasks and generates operations accordingly.

Time Complexity: O(n^2 * log(max(a))) where n is the size of input array.
Space Complexity: O(n) for storing the input array, visited flags, and auxiliary data structures.
*/

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#define N 100005
int n, a[N];
inline int cal(int x, int y) {
  int res = 0;
  while (x % y == 0)
    res++, x /= y;
  return res;
}
std::vector<int> V;
bool vis[N];
inline void sol() {
  int s = 0;
  for (int i = 1; i <= n; i++)
    if (!vis[i])
      s = std::__gcd(s, a[i]);
  for (int i = 1; i <= n; i++)
    if (!vis[i]) {
      int x = a[i], t = a[i], cnt = 0;
      for (int y = 2; y <= x; y++)
        if (x % y == 0) {
          while (x % y == 0)
            x /= y;
          if (cal(t, y) == cal(s, y))
            continue;
          for (int j = 1; j <= n; j++)
            if (!vis[j] && cal(a[j], y) == cal(s, y)) {
              V.push_back(j), t = std::__gcd(t, a[j]);
              break;
            }
          cnt++;
        }
      if (cnt < 7)
        V.push_back(i);
      break;
    }
}
std::vector<std::pair<int, std::vector<int>>> ans;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  sol(); // First pass to select initial subset
  for (auto i : V)
    vis[i] = 1;
  sol(); // Second pass to refine subset
  for (int l = 1; l < (1 << V.size()); l++) {
    int x = __builtin_popcount(l), y = x & 1 ? 2 - x : x - 2, z = 0;
    if (y < 0)
      z = 1, y = -y;
    std::vector<int> j;
    for (int i = 0; i < (int)V.size(); i++)
      if ((l >> i) & 1)
        j.push_back(V[i]);
    std::sort(j.begin(), j.end());
    while (y--)
      ans.emplace_back(z, j);
  }
  printf("%d\n", (int)ans.size());
  for (auto [i, j] : ans) {
    printf("%d %d ", i, (int)j.size());
    for (auto k : j)
      printf("%d ", k);
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/