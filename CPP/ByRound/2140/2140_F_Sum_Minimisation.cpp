// Problem: CF 2140 F - Sum Minimisation
// https://codeforces.com/contest/2140/problem/F

// F. Sum Minimisation
// Algorithms/Techniques: Greedy, Mathematical Analysis, Prime Factorization, Sorting
// Time Complexity: O(N * log(N) + sqrt(N) * log(N)) per test case
// Space Complexity: O(N + sqrt(N)) per test case

#include <assert.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;
const ll ILL = 2167167167167167167;
const int INF = 2100000000;
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
#define all(p) p.begin(), p.end()
template <class T> using _pq = priority_queue<T, vector<T>, greater<T>>;
template <class T> int LB(vector<T> &v, T a) {
  return lower_bound(v.begin(), v.end(), a) - v.begin();
}
template <class T> int UB(vector<T> &v, T a) {
  return upper_bound(v.begin(), v.end(), a) - v.begin();
}
template <class T> bool chmin(T &a, T b) {
  if (b < a) {
    a = b;
    return 1;
  } else
    return 0;
}
template <class T> bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return 1;
  } else
    return 0;
}
template <class T> void So(vector<T> &v) { sort(v.begin(), v.end()); }
template <class T> void Sore(vector<T> &v) {
  sort(v.begin(), v.end(), [](T x, T y) { return x > y; });
}
bool yneos(bool a, bool upp = false) {
  if (a) {
    cout << (upp ? "YES\n" : "Yes\n");
  } else {
    cout << (upp ? "NO\n" : "No\n");
  }
  return a;
}
template <class T> void vec_out(vector<T> &p, int ty = 0) {
  if (ty == 2) {
    cout << '{';
    for (int i = 0; i < (int)p.size(); i++) {
      if (i) {
        cout << ",";
      }
      cout << '"' << p[i] << '"';
    }
    cout << "}\n";
  } else {
    if (ty == 1) {
      cout << p.size() << "\n";
    }
    for (int i = 0; i < (int)(p.size()); i++) {
      if (i)
        cout << " ";
      cout << p[i];
    }
    cout << "\n";
  }
}
template <class T> T vec_min(vector<T> &a) {
  assert(!a.empty());
  T ans = a[0];
  for (auto &x : a)
    chmin(ans, x);
  return ans;
}
template <class T> T vec_max(vector<T> &a) {
  assert(!a.empty());
  T ans = a[0];
  for (auto &x : a)
    chmax(ans, x);
  return ans;
}
template <class T> T vec_sum(vector<T> &a) {
  T ans = T(0);
  for (auto &x : a)
    ans += x;
  return ans;
}
int pop_count(long long a) {
  int res = 0;
  while (a) {
    res += (a & 1), a >>= 1;
  }
  return res;
}
template <class T> T square(T a) { return a * a; }
vector<int> Eratosthenes(int a) {
  if (a < 2)
    return {};
  vector<int> p(a + 1, 1), ans;
  p[0] = 0, p[1] = 0;
  int k = 2;
  while (k * k <= a) {
    if (p[k]) {
      ans.push_back(k);
      for (int i = 2; i * k <= a; i++) {
        p[i * k] = 0;
      }
    }
    k++;
  }
  while (k <= a) {
    if (p[k])
      ans.push_back(k);
    k++;
  }
  return ans;
}
void solve();
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  rep(i, 0, t) solve();
}
void solve() {
  int N;
  cin >> N;
  vector<ll> A(N);
  rep(i, 0, N) cin >> A[i];
  So(A);
  ll S = vec_sum(A);
  auto E = Eratosthenes(N - 1);
  ll tmp = 1;
  for (auto e : E) {
    ll v = 1;
    while (v * e < N) {
      v *= e;
      tmp = min(tmp * e, (ll)INF); // Find the largest prime power that fits into N
    }
  }
  if (A[0] == A[N - 1]) { // If all elements are equal, cannot reduce further
    cout << S << "\n";
    return;
  }
  if ((A[0] + A[N - 1]) % 2 == 0) { // Even sum case
    if (S % N) { // If not divisible by N, impossible to reduce
      cout << "-1\n";
      return;
    }
    rep(i, 0, N - 1) {
      // Check divisibility using prime powers for valid operation
      if ((A[i + 1] - A[i]) % tmp) {
        cout << "-1\n";
        return;
      }
    }
    cout << S << "\n"; // Valid case, answer is sum
  } else { // Odd sum case
    if (S % N != 1) { // Not valid for reducing by one element
      cout << "-1\n";
      return;
    }
    A[0]--; // Decrement smallest element to make it fit the pattern
    rep(i, 0, N - 1) {
      if ((A[i + 1] - A[i]) % tmp) { // Check divisibility again after adjustment
        cout << "-1\n";
        return;
      }
    }
    cout << S - 1 << "\n"; // Adjusted sum is the result
  }
}


// https://github.com/VaHiX/codeForces/