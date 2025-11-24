// Problem: CF 2172 F - Cluster Computing System
// https://codeforces.com/contest/2172/problem/F

/*
Purpose: This code solves the problem of connecting servers in a cluster computing system such that all servers are reachable from each other, minimizing the total cost of connections.

Algorithms/Techniques:
- Uses prefix and suffix GCD arrays to efficiently calculate the cost of connecting segments.
- Greedy selection of minimum cost edges (based on GCD of subarrays) to build a minimum spanning tree (MST) effectively.
- Time Complexity: O(n log(max_value)) where n is the number of servers and max_value is the maximum protocol value.
- Space Complexity: O(n) for storing prefix and suffix GCD arrays and input data.

The problem reduces to finding a minimum cost way to connect all nodes, where cost of connecting nodes from index u to v is gcd(p[u], p[u+1], ..., p[v]).
*/

#include <algorithm>
#include <iostream>
#include <utility>

#define int long long
using namespace std;
const int N = 4e5 + 10, mod = 998244353, INF = 1e12;
int T, m, n, k, q, ax, a[N], b[N], c[N], d[N];
int gcd(int a, int b) {
  if (a < b)
    swap(a, b);
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
void work() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[i] = gcd(b[i - 1], a[i]); // b[i] stores GCD of elements from 1 to i
  }
  for (int i = n; i >= 1; i--) {
    c[i] = gcd(c[i + 1], a[i]); // c[i] stores GCD of elements from i to n
  }
  int ans = b[n]; // Initial cost for the full range
  for (int i = 2; i < n; i++)
    ans += min(b[i], c[i]); // Add the minimum of prefix and suffix GCD for internal nodes
  cout << ans << endl;
  return;
}
signed main() {
  T = 1;
  while (T--) {
    work();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/