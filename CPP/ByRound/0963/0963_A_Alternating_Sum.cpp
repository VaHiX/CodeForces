// Problem: CF 963 A - Alternating Sum
// https://codeforces.com/contest/963/problem/A

#include <iostream>
#include <string>

using namespace std;
#define ll long long
const ll md = 1e9 + 9;
ll n, a, b, k, ans, sum, xa, xi, x, ia;
ll ksm(ll a, ll b) {
  ll re = 1;
  a %= md;
  while (b) {
    if (b & 1) {
      re = re * a % md;
    }
    a = a * a % md;
    b /= 2;
  }
  return re;
}
string s;
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> a >> b >> k;
  cin >> s;
  ans = 0;
  x = ksm(a, n);  // x = a^n
  ia = ksm(a, md - 2), xa = 1;  // ia = a^(-1) mod md, xa = 1
  for (int i = 0; i < k; i++) {
    if (s[i] == '+') {
      ans = (ans + x * xa % md) % md;  // Add contribution of s[i] = +1
    } else {
      ans = (ans + md - x * xa % md) % md;  // Add contribution of s[i] = -1
    }
    x = x * ia % md, xa = xa * b % md;  // Update x for next term and xa for next coefficient
  }
  xa = 1;
  sum = 0;
  xi = ksm(b * ia, k);  // xi = (b * a^(-1))^k
  x = (n + 1) / k;  // Number of complete cycles
  if (xi == 1) {
    cout << ans * x % md << endl;  // If the sum is 1, just multiply by number of cycles
  } else {
    ll xxx = (1 + md - ksm(xi, x));  // Sum of geometric series: (1 - xi^x)
    ll xxx1 = ksm(1 + md - xi, md - 2);  // Inverse of (1 - xi)
    cout << ans * xxx % md * xxx1 % md << endl;  // Final result is ans * (1 - xi^x) / (1 - xi)
  }
}


// https://github.com/VaHiX/CodeForces/