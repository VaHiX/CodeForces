// Problem: CF 2063 D - Game With Triangles
// https://codeforces.com/contest/2063/problem/D

/*
D. Game With Triangles
Algorithms/Techniques: Greedy, Sorting, Binary Search, Prefix Sums
time complexity: O((n + m) log(n + m)) per test case
space complexity: O(n + m)

This solution computes the maximum number of operations (kmax) that can be performed by choosing 3 non-collinear points from n points on y=0 and m points on y=2 to form triangles.
For each valid number of operations k from 1 to kmax, we maximize the total area using a greedy approach:
- Sort both arrays a and b
- For k operations, try all possible distributions of chosen points between a and b to maximize triangle areas
- Use prefix sums for efficient computation of potential gains
- Binary search is used to find the optimal split of points for maximizing score in each operation count k.
*/

#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, m, a[N], b[N];
ll sa[N], sb[N];

// Calculates the combined score given x points from array a and (k-x) from array b
ll calc(int x, int k) { return sa[x] + sb[k - x]; }

void clr() {}

void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= m; i++)
    cin >> b[i];
  sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
  
  // Determine maximum number of valid operations based on greedy selection
  int na = 0, nb = 0, kmax = 0;
  while (2 * (na + 1) <= n - nb && 2 * nb < m - na ||
         2 * (nb + 1) <= m - na && 2 * na < n - nb) {
    if (n - nb - 2 * na >= m - na - 2 * nb)
      kmax++, na++;
    else
      kmax++, nb++;
  }
  
  cout << kmax << '\n';
  
  // Compute prefix sums for areas contributed by choosing pairs from a and b.
  // sa[i] = sum of differences in sorted a for first i pairs (largest to smallest)
  for (int i = 1; i <= n / 2; i++)
    sa[i] = sa[i - 1] + a[n - i + 1] - a[i];
  for (int i = 1; i <= m / 2; i++)
    sb[i] = sb[i - 1] + b[m - i + 1] - b[i];

  // For each operation count k from 1 to kmax, find best way to distribute selections
  for (int k = 1; k <= kmax; k++) {
    const int LL = k - min({k, m / 2, n, m - k}),
              RR = min({k, n / 2, m, n - k});
    int L = LL, R = RR + 1, mid;

    // Binary search to find the optimal split minimizing the loss in area
    while (L < R - 1) {
      mid = L + R >> 1;
      if (calc(mid, k) >= calc(mid - 1, k))
        L = mid;
      else
        R = mid;
    }
    
    cout << calc(L, k) << ' ';
  }
  cout << '\n';
  clr();
}

int main() {
  ios::sync_with_stdio(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/