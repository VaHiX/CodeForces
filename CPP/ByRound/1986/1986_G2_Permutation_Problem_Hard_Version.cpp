// Problem: CF 1986 G2 - Permutation Problem (Hard Version)
// https://codeforces.com/contest/1986/problem/G2

/*
Algorithm: 
- For each element in the permutation, we calculate a pair (x, y) = (p[i]/gcd(p[i], i+1), (i+1)/gcd(p[i], i+1))
- The condition p[i] * p[j] is divisible by i * j is transformed to x * p[j] is divisible by y * (j+1)
- By doing this transformation, we preprocess all divisors of x and use a sieve-like technique to count valid pairs efficiently.
- For each y value, we iterate over multiples of y and count matching x values from ys array.
- This solution uses a combination of precomputed prime factorization, divisor enumeration, and optimized counting to avoid O(n^2) check.

Time Complexity: O(n * sqrt(n) + n * log(n)) 
Space Complexity: O(n)
*/

#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;
int n;
int a[500000];
int gcd(int a, int b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}
int p[500001];
vector<int> divs;
void getDivs(int x) {
  divs.clear();
  divs.push_back(1);
  while (x > 1) {
    int pp = p[x];
    int cnt = 0;
    while (p[x] == pp) {
      cnt++;
      x = x / pp;
    }
    int sz = divs.size();
    int curr = 1;
    for (int j = 1; j <= cnt; j++) {
      curr *= pp;
      for (int k = 0; k < sz; k++) {
        divs.push_back(divs[k] * curr);
      }
    }
  }
}
void gen() {
  n = 500000;
  for (int i = 0; i < n; i++)
    a[i] = i + 1;
  mt19937 rnd(4321);
  shuffle(a, a + n, rnd);
}
void read() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
}
int cnt[500001];
vector<int> ys[500001];
void solve() {
  read();
  int ones = 0;
  vector<pair<int, int>> xy;
  for (int i = 0; i < n; i++) {
    int x = a[i];
    int g = gcd(x, i + 1);
    x /= g;
    int y = (i + 1) / g;
    ones += (y == 1);
    xy.push_back({x, y});
    ys[x].push_back(y);
  }
  sort(xy.begin(), xy.end(),
       [](auto a, auto b) { return a.second < b.second; });
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    int j = i;
    int y = xy[i].second;
    while (j + 1 < n && xy[j + 1].second == y)
      j++;
    for (int k = i; k <= j; k++) {
      getDivs(xy[k].first);
      for (int d : divs) {
        cnt[d]++;
      }
    }
    for (int a = y; a <= n; a += y) {
      for (int b : ys[a]) {
        ans += cnt[b];
      }
    }
    for (int k = i; k <= j; k++) {
      getDivs(xy[k].first);
      for (int d : divs) {
        cnt[d] = 0;
      }
    }
    i = j;
  }
  for (int i = 0; i < n; i++) {
    ys[xy[i].first].clear();
  }
  cout << (ans - ones) / 2 << "\n";
}
int main() {
  ios_base::sync_with_stdio(0);
  for (int i = 1; i <= 500000; i++)
    p[i] = i;
  for (int i = 2; i <= 500000; i++) {
    if (p[i] != i)
      continue;
    if (1LL * i * i > 500000)
      continue;
    for (int j = i * i; j <= 500000; j += i) {
      p[j] = min(p[j], i);
    }
  }
  int tt = 1;
  cin >> tt;
  while (tt--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/