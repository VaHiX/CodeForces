// Problem: CF 1682 F - MCMF?
// https://codeforces.com/contest/1682/problem/F

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
#define int long long
const int P = 1e9 + 7;
template <class T> struct Bit {
  int n;
  vector<T> a;
  Bit(int n) : n(n), a(n + 1){};
  void add(int x, T v = 1) {
    for (; x <= n; x += x & -x) // Add value to Fenwick tree at position x
      a[x] += v;
  }
  T sum(int x) {
    T ans = 0;
    for (; x; x -= x & -x) // Sum all values from 1 to x in Fenwick tree
      ans += a[x];
    return ans;
  }
  T operator[](int x) { return sum(x); }
};
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n + 1), b(n + 1), ca(n + 1), s(n + 1), f(n + 1);
  for (int i = 0; i < n; ++i)
    cin >> a[i]; // Read array a
  for (int i = n - 1; i >= 1; i--)
    ca[i] = (a[i] - a[i - 1]) % P; // Compute differences between consecutive elements of a
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
    b[i] += b[i - 1]; // Prefix sum of b
  }
  vector<int> id(n);
  iota(id.begin(), id.end(), 1); // Fill id with 1, 2, ..., n
  sort(id.begin(), id.end(), [&](int i, int j) { return b[i] > b[j]; }); // Sort indices by b values in descending order
  Bit<int> c(n), d(n); // Initialize two Fenwick trees
  for (int i = 1; i <= n; ++i)
    b[i] %= P, s[i] = (s[i - 1] + ca[i] * b[i]) % P; // Precompute prefix sum s
  for (int i : id) {
    f[i] = ((a[i - 1] - 2 * c[i]) * b[i] % P + d[i] - s[i - 1]) % P; // Compute f[i] using Fenwick trees
    c.add(i, ca[i]); // Update Fenwick tree c
    d.add(i, 2LL * ca[i] * b[i] % P); // Update Fenwick tree d
  }
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << ((f[r] - f[l - 1]) % P + P) % P << "\n"; // Output the query result modulo P
  }
}


// https://github.com/VaHiX/CodeForces/