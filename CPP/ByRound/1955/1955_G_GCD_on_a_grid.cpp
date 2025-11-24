// Problem: CF 1955 G - GCD on a grid
// https://codeforces.com/contest/1955/problem/G

/*
Algorithm: GCD on a grid
Approach:
- For each possible GCD value that divides both start and end elements, we check if there's a valid path where all elements are divisible by that GCD.
- We use a sieve to precompute primes up to 1e6.
- For each candidate GCD, we use dynamic programming to see if a valid path exists.
- We iterate over all divisors of the GCD of start and end elements.

Time Complexity: O(n * m * sqrt(max_val) + number_of_primes * sqrt(max_val))
Space Complexity: O(n * m + max_val)

Methods:
- pre(): Precomputes primes using Sieve of Eratosthenes
- check(): Uses DP to determine if a path exists with given GCD
- solve(): Main logic to process each test case
*/

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
#define all(x) x.begin(), x.end()
inline char nc() {
  static char buf[1 << 23], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
inline int read() {
  char ch = nc();
  int sum = 0;
  while (!(ch >= '0' && ch <= '9'))
    ch = nc();
  while (ch >= '0' && ch <= '9')
    sum = sum * 10 + ch - 48, ch = nc();
  return sum;
}
vector<int> pri;
bool not_prime[1001000];
void pre(int n) {
  for (int i = 2; i <= n; ++i) {
    if (!not_prime[i]) {
      pri.push_back(i);
    }
    for (int pri_j : pri) {
      if (i * pri_j > n)
        break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0) {
        break;
      }
    }
  }
}
bool dp[101][101];
int a[101][101];
int n, m, ans, t;
int check(int x) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = (dp[i - 1][j] | dp[i][j - 1]) & !(a[i][j] % x); // DP to see if there's valid path to (i,j) with GCD x
    }
  }
  return dp[n][m];
}
void solve() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      a[i][j] = read();
    }
  }
  t = gcd(a[1][1], a[n][m]); // GCD of start and end elements
  if (t == 1) {
    cout << 1 << "\n";
    return;
  }
  ans = 1;
  int tmp = t;
  vector<int> p;
  vector<int> q;
  for (int i = 1; i * i <= t; i++) {
    if (t % i == 0) {
      if (!not_prime[i]) { // If i is prime
        p.emplace_back(i);
      } else {
        q.emplace_back(i);
      }
      if (!not_prime[t / i]) { // If t/i is prime
        p.emplace_back(t / i);
      } else {
        q.emplace_back(t / i);
      }
    }
  }
  vector<int> w;
  for (auto it : p) {
    if (check(it)) { // If path exists with this GCD
      ans = max(ans, it);
    } else {
      w.emplace_back(it);
    }
  }
  if (ans == 1) {
    cout << ans << "\n";
    return;
  } else {
    sort(all(q), greater<int>()); // Sort from largest to smallest
    for (auto it : q) {
      if (it <= ans) {
        cout << ans << "\n";
        return;
      }
      bool flag = 0;
      for (int i = 0; i < w.size(); i++) {
        if (it % w[i] == 0) { // If it's divisible by any non-prime factor in w
          flag = 1;
          break;
        }
      }
      if (flag) {
        continue;
      }
      if (check(it)) { // If path exists with this GCD
        cout << max(ans, it) << "\n";
        return;
      }
    }
  }
  cout << ans << "\n";
  return;
}
signed main() {
  pre(1000000); // Precompute primes
  dp[0][1] = 1; // Base case for DP
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int test = 1;
  test = read(); // Read test cases
  while (test--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/