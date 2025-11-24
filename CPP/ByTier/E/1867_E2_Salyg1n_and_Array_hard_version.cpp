// Problem: CF 1867 E2 - Salyg1n and Array (hard version)
// https://codeforces.com/contest/1867/problem/E2

/*
Algorithm/Technique: 
The problem involves finding the XOR of all elements in an array using a limited number of queries. 
Each query returns the XOR of k consecutive elements starting at position i, and then reverses that subarray.
The key idea is to use overlapping queries to determine the XOR of the entire array while minimizing queries.

Approach:
1. For every k elements, query the XOR of the subarray starting at position i.
2. Keep XORing these query results to get the final XOR of all array elements.
3. For the last part of the array (if not exactly divisible by k), we adjust our query strategy:
   - Query the middle of the last block
   - Query the end of the last block 
   - This is to handle the partial block correctly due to reversal operations.

Time Complexity: O(n/k * k) = O(n), since we perform at most n/k queries and each query takes O(k) time.
Space Complexity: O(1), as we only use constant extra space.
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <utility>

void Yes() {
  std::cout << "YES" << "\n";
  return;
}
void No() {
  std::cout << "NO" << "\n";
  return;
}
template <typename T> void out(T x) { std::cout << x << "\n"; }
using namespace std;
using ll = long long;
using PII = pair<int, int>;
const int N = 2e5 + 10;
void query(int x) {
  cout << "? ";
  cout << x << endl;
}
struct DSU {
  vector<int> p;
  vector<int> sz;
  DSU(int n) : p(n + 1) {
    iota(p.begin(), p.end(), 0);
    sz.resize(n + 1, 1);
  }
  int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
  int findsz(int x) { return sz[find(x)]; }
  bool same(int x, int y) { return find(x) == find(y); }
  bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)
      return false;
    sz[x] += sz[y];
    p[y] = x;
    return true;
  }
};
void Solve() {
  ll n, k;
  cin >> n >> k;
  ll ans = 0;
  ll tmp = 0;
  // Iterate through the array in steps of k, querying each k-length block
  for (int i = 1; i <= n - k + 1; i += k) {
    query(i);
    ll p;
    cin >> p;
    ans ^= p; // Accumulate XOR of query results
    tmp = i;
  }
  // Handle the remaining elements that do not form a complete block of size k
  if (tmp <= n - k + 1) {
    ll p;
    ll rem = n % k;
    query(n - k + 1 - rem / 2);
    cin >> p;
    ans ^= p;
    query(n - k + 1);
    cin >> p;
    ans ^= p;
  }
  cout << "! ";
  cout << ans << endl;
}
signed main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    Solve();
}


// https://github.com/VaHiX/CodeForces/