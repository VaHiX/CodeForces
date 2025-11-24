// Problem: CF 1621 E - New School
// https://codeforces.com/contest/1621/problem/E

// Flowerbox: 
// Problem: New School
// Purpose: Determine if it's possible to assign teachers to student groups after each student refuses to study.
// Algorithm: 
//   - For each group, calculate average age of students.
//   - Sort teachers in descending order of age.
//   - Sort groups in descending order of average age.
//   - Use precomputed arrays to check if a valid assignment is possible for each student removal.
// Time Complexity: O(n * log(n) + m * log(m) + total_students)
// Space Complexity: O(n + m + total_students)

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
const ll N = 1e5 + 5;
ll n, m, k[N], p[N], s[N], b[N], c[N], ps[N];
double a[N], as[N];
vector<ll> v[N];
bool cmp(ll x, ll y) { return as[x] > as[y]; }
int main() {
  ll t;
  cin >> t;
  while (t--) {
    scanf("%lld%lld", &n, &m);
    for (ll i = 0; i < n; i++)
      scanf("%lf", &a[i]);
    sort(a, a + n);
    reverse(a, a + n);
    for (ll i = 0; i < m; i++) {
      p[i] = i;
      scanf("%lld", &k[i]);
      v[i].clear();
      s[i] = 0;
      b[i] = c[i] = i;
      for (ll j = 0; j < k[i]; j++) {
        ll x;
        scanf("%lld", &x);
        v[i].push_back(x);
        s[i] += x;
      }
      as[i] = 1.0 * s[i] / k[i];
    }
    sort(p, p + m, cmp);
    for (ll i = 0; i < m; i++)
      ps[p[i]] = i;
    ll f1 = m, f2 = -1;
    for (ll i = 0; i < m; i++)
      if (a[i] < as[p[i]]) {
        f1 = i;
        break;
      }
    for (ll i = m - 1; i >= 0; i--) {
      if (a[i] < as[p[i]]) {
        f2 = i;
        break;
      }
    }
    for (ll i = 1; i < m; i++) {
      if (as[p[i - 1]] <= a[i])
        b[i] = b[i - 1];
    }
    for (ll i = m - 2; i >= 0; i--) {
      if (c[i + 1] == -1)
        c[i] = -1;
      else if (as[p[i + 1]] > a[i + 1]) {
        if (as[p[i + 1]] <= a[i])
          c[i] = c[i + 1];
        else
          c[i] = -1;
      } else if (c[i + 1] != i + 1)
        c[i] = c[i + 1];
    }
    string ans = "";
    for (ll i = 0; i < m; i++) {
      ll x = ps[i];
      for (auto it : v[i]) {
        double st = 1.0 * (s[i] - it) / (k[i] - 1);
        if (st >= as[i]) {
          if (st <= a[b[x]] && b[x] - 1 < f1 && x + 1 > f2)
            ans += '1';
          else
            ans += '0';
        } else {
          if (c[x] != -1 && st <= a[c[x]] && c[x] + 1 > f2 && x - 1 < f1)
            ans += '1';
          else
            ans += '0';
        }
      }
    }
    puts(ans.data());
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/