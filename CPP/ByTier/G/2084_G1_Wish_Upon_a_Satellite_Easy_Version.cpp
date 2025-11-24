// Problem: CF 2084 G1 - Wish Upon a Satellite (Easy Version)
// https://codeforces.com/contest/2084/problem/G1

/*
G1. Wish Upon a Satellite (Easy Version)

Algorithms/Techniques: Dynamic Programming with State Compression and Game Theory

Time Complexity: O(n^3) per test case
Space Complexity: O(n^2) 

The problem involves computing the maximum beauty of a permutation where:
- Beauty = sum of f(c) over all subsegments c of the permutation
- f(c) is computed as the value of c[1] after optimal play between Turtle (maximizing) and Piggy (minimizing)
- Some elements in the input are missing (represented by 0) and must be filled optimally

This code uses dynamic programming to find the best arrangement of the missing elements,
where DP tracks optimal values based on position and number of operations.
*/

#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 5005;
const ll inf = 1e18;
int vs[maxn], a[maxn];
ll f[maxn], g[maxn];

void work() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    vs[i] = -1; // Initialize vs array to track known positions
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i])
      vs[a[i]] = (i & 1); // Mark if position of a[i] is odd or even
  }
  int x = (n + 1) / 2; // Half the size for DP
  for (int i = 1; i <= x; i++)
    f[i] = -inf; // Initialize f with negative infinity
  f[0] = 0; // Base case: no elements processed yet
  for (int i = n; i; i--) { // Iterate from back to front
    for (int j = 0; j <= x && j <= n - i; j++)
      g[j] = f[j], f[j] = -inf; // Copy current DP state to g, reset f
    for (int j = 0; j <= x && j <= n - i; j++) {
      if (vs[i] != 0) // If this position is already set
        f[j + 1] = max(f[j + 1], g[j] + 1ll * i * (x - j + n - i - j)); // Update DP with turtle move
      if (vs[i] != 1) // If this position isn't odd (not set to odd)
        f[j] = max(f[j], g[j] + 1ll * i * (i + j + j - x)); // Update DP with piggy move
    }
  }
  cout << f[x] << "\n"; // Output final answer
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T = 1;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/codeForces/