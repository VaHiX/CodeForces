// Problem: CF 1648 A - Weird Sum
// https://codeforces.com/contest/1648/problem/A

/*
A. Weird Sum
Algorithms/Techniques: 
    - Grouping cells by color using a map
    - For each color, calculate the contribution of row and column coordinates separately
    - Use sorting and mathematical trick to compute sum of pairwise distances efficiently

Time Complexity: O(n * m * log(n * m))
Space Complexity: O(n * m)

Egor has a table of size n × m, with lines numbered from 1 to n and columns numbered from 1 to m. Each cell has a color that can be presented as an integer from 1 to 10^5.
Let us denote the cell that lies in the intersection of the r-th row and the c-th column as (r, c). We define the manhattan distance between two cells (r1, c1) and (r2, c2) as the length of a shortest path between them where each consecutive cells in the path must have a common side. The path can go through cells of any color.
Egor decided to calculate the sum of manhattan distances between each pair of cells of the same color. Help him to calculate this sum.
*/
#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  const ll nt = 1e6; // Offset to differentiate row and column indices
  ll n, m;
  scanf("%lld %lld", &n, &m);
  std::map<ll, std::vector<ll>> w; // Map to store coordinates for each color
  for (ll row = 0; row < n; row++) {
    for (ll col = 0; col < m; col++) {
      ll r;
      scanf("%lld", &r);
      w[r].push_back(row);            // Store row index for color r
      w[nt + r].push_back(col);       // Store column index for color r (with offset)
    }
  }
  ll res(0);
  for (std::map<ll, std::vector<ll>>::iterator it = w.begin(); it != w.end();
       it++) {
    std::vector<ll> v = it->second;
    sort(v.begin(), v.end()); // Sort coordinates to efficiently compute sum of distances
    ll cur(0);
    for (ll p = 0; p < v.size(); p++) {
      // Use mathematical formula: for sorted array, contribution of v[p] is 
      // (2 * p - (v.size() - 1)) * v[p]
      cur += (2 * p - (v.size() - 1)) * v[p];
    }
    res += cur;
  }
  printf("%lld\n", res);
}


// https://github.com/VaHiX/codeForces/