// Problem: CF 2127 G2 - Inter Active (Hard Version)
// https://codeforces.com/contest/2127/problem/G2

/*
Algorithm: Interactive problem solving using binary search and XOR properties to determine a hidden permutation.
Approach:
1. Select k = (n+1)/2 as a fixed value
2. Use binary coding technique with M = log2(n-1)+1 bits to encode positions
3. Query permutations with specific arrangements to get XOR values for each position
4. Identify "good" and "bad" positions based on XOR properties
5. Use binary search on good positions to find cycle mappings
6. Use direct deduction for bad positions

Time Complexity: O(n * log(n) * log(n)) due to nested loops and binary searches
Space Complexity: O(n) for storing vectors and intermediate values
*/
#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define rng(i, a, b) for (int i = (a); i < (b); ++i)
const int MOD = 1e9 + 7;
#ifdef Tomato
template <typename T> ostream &operator<<(ostream &o, vector<T> vec) {
  o << "{";
  int f = 0;
  for (T i : vec)
    o << (f++ ? " " : "") << i;
  return o << "}";
}
void bug__(int c, auto... a) {
  cerr << "\e[1;" << c << "m";
  (..., (cerr << a << " "));
  cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#else
#define bug(x...) void(0)
#endif
template <class... T> void input(T &...a) { (cin >> ... >> a); }
template <class T, class... Ts> void print(const T &a, const Ts &...b) {
  cout << a;
  (cout << ... << (cout << ' ', b));
  cout << '\n';
}
void print() { cout << '\n'; }
ll power(ll a, ll b, ll mod = MOD) {
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}
void solve() {
  int n;
  cin >> n;
  const int k = (n + 1) / 2;  // Select k as (n+1)/2 for query strategy
  const int M = __lg(n - 1) + 1;  // Calculate number of bits needed
  cout << k + 1 << endl;  // Output k+1 as the fixed constant
  vector<int> p(n + 1);  // Result permutation
  auto query = [&](vector<int> &q) -> int {  // Helper to make queries
    cout << "? ";
    for (int i = 1; i <= n; i++)
      cout << q[i] << " \n"[i == n];
    cout.flush();
    int res;
    cin >> res;
    return res;
  };
  vector<int> c(n + 1), d(1 << M);  // c maps positions to binary codes, d maps codes to positions
  auto binary_coding = [&]() {  // Generate binary coding for positions
    for (int i = 0, cnt = 1; cnt <= n; i++, cnt++) {
      c[cnt++] = i;
      if (cnt <= n)
        c[cnt] = (1 << M) - 1 - i;
    }
    for (int i = 1; i <= n; i++)
      d[c[i]] = i;
  };
  vector<int> xors(n + 1);  // XOR values for each position
  vector<vector<int>> res1(M, vector<int>(n + 1)), res2(M, vector<int>(n + 1));  // Results from queries
  vector<int> good, bad;  // Good positions are those with non-zero XOR, bad are those with zero XOR
  auto getXORs = [&]() {  // Compute XOR values for all positions
    for (int bit = 0; bit < M; bit++) {
      vector<int> A, B;
      for (int i = 1; i <= n; i++) {
        if (c[i] & (1 << bit))
          B.pb(i);
        else
          A.pb(i);
      }
      int m = A.size(), l = B.size();
      for (int i = 0; i < m; i++) {
        vector<int> q(n + 1);
        for (int j = 0; j < m; j++)
          q[j + 1] = A[(j + i) % m];
        for (int j = 0; j < l; j++)
          q[j + m + 1] = B[j];
        int res = query(q);
        res1[bit][q[1]] = res;
        res2[bit][q[m]] = res;
      }
      for (int i = 0; i < l; i++) {
        vector<int> q(n + 1);
        for (int j = 0; j < l; j++)
          q[j + 1] = B[(j + i) % l];
        for (int j = 0; j < m; j++)
          q[j + l + 1] = A[j];
        int res = query(q);
        res1[bit][q[1]] = res;
        res2[bit][q[l]] = res;
      }
      for (int i = 1; i <= n; i++) {
        if (res1[bit][i] != res2[bit][i])
          xors[i] ^= (1 << bit);
      }
    }
    for (int i = 1; i <= n; i++) {
      if (xors[i] != 0)
        good.pb(i);
      else
        bad.pb(i);
    }
  };
  auto solve3 = [&]() {  // Process good positions using binary search
    for (auto pos : good) {
      if (p[pos])
        continue;
      int x = xors[pos], bit = __lg(x & (-x));  // Find lowest set bit
      vector<int> A, B;
      for (int i = 1; i <= n; i++) {
        if (c[i] & (1 << bit))
          B.pb(i);
        else
          A.pb(i);
      }
      if (c[pos] & (1 << bit))
        swap(A, B);
      int m = A.size(), l = B.size(), id = 0;
      for (int i = 0; i < m; i++)
        if (A[i] == pos)
          id = i;
      vector<int> base(n + 1);
      for (int j = 0; j < m; j++)
        base[j + 1] = A[(j + id) % m];
      for (int j = 0; j < l; j++)
        base[j + m + 1] = B[j];
      int L = 2, R = m;
      while (L < R) {
        int mid = (L + R) >> 1;
        vector<int> q(n + 1);
        for (int i = 1; i < mid; i++)
          q[i] = base[i + 1];
        q[mid] = base[1];
        for (int i = mid + 1; i <= n; i++)
          q[i] = base[i];
        int res = query(q);
        if (res != res1[bit][pos])
          R = mid;
        else
          L = mid + 1;
      }
      int s = 0;
      if (res2[bit][pos] > res1[bit][pos])
        p[base[L]] = pos, s = base[L];
      else
        p[pos] = base[L], s = pos;
      while (!p[p[s]]) {
        int X = xors[p[s]];
        p[p[s]] = d[X ^ c[s]];
        s = p[s];
      }
    }
  };
  auto solve2 = [&]() {  // Process bad positions using direct deduction
    for (auto pos : bad) {
      if (p[pos])
        continue;
      auto calc = [&](vector<int> &q) {
        int val = count(all(p), 0) / 2;
        vector<int> inv(n + 1);
        for (int i = 1; i <= n; i++)
          inv[q[i]] = i;
        for (int i = 1; i <= n; i++)
          val += (inv[i] < inv[p[i]]);
        return val;
      };
      vector<int> cand, ok;
      for (int i = 1; i <= n; i++) {
        if (i != pos && !p[i])
          cand.pb(i);
        if (p[i])
          ok.pb(i);
      }
      while ((int)cand.size() != 1) {
        vector<int> q = {0}, L, R;
        int len = ((int)cand.size() + 1) / 2;
        for (int i = 0; i < len; i++)
          q.pb(cand[i]), L.pb(cand[i]);
        for (int i = len; i < k; i++)
          q.pb(ok[i - len]);
        q.pb(pos);
        for (int i = len; i < (int)cand.size(); i++)
          q.pb(cand[i]), R.pb(cand[i]);
        for (int i = k - len; i < (int)ok.size(); i++)
          q.pb(ok[i]);
        int res = query(q) - calc(q);
        if (res != 0)
          swap(L, R);
        cand = L;
        for (auto x : R)
          ok.pb(x);
      }
      p[pos] = cand[0];
      p[cand[0]] = pos;
    }
  };
  binary_coding();  // Generate binary codes
  getXORs();  // Compute XOR values
  solve3();  // Solve good positions
  solve2();  // Solve bad positions
  cout << "! ";
  for (int i = 1; i <= n; i++)
    cout << p[i] << " \n"[i == n];
  cout.flush();
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T = 1;
  input(T);
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/