// Problem: CF 1735 E - House Planning
// https://codeforces.com/contest/1735/problem/E

/*
Algorithm/Techniques:
- The main idea is to determine if there exist positions of houses (h) and two
planned points (p1, p2) such that the given distance arrays d1 and d2 are valid.
- The key observation is that for each house h[i], and two points p1 and p2, we
have d1[i] = |p1 - h[i]| and d2[i] = |p2 - h[i]|.
- Since distances are non-negative, we can try all possible candidates for the
difference between p1 and p2, which is k = |p1 - p2|.
- For a fixed k, we attempt to match elements from d1 and d2 to form valid pairs
(d1[i], d2[i]) such that d1[i] = |p1 - h[i]| and d2[i] = |p2 - h[i]|.
- We use a greedy approach: for each element in sorted d1 (starting from
largest), we check if it can be matched to either (p1 - h[i]) or (p2 - h[i])
based on fixed k.
- To avoid invalid solutions when p1 and p2 may not be distinct, we try all
valid combinations of p1 and p2 that satisfy distance constraints.
- All valid combinations are checked using a brute force search over possible
values of k (difference of p1 and p2) and checking if d1 and d2 can be split
into pairs matching the constraints.

Time Complexity: O(n^2 log n)
Space Complexity: O(n)

The solution tries all combinations of distances from the sorted array d1 and
checks for valid splits using a greedy matching and map-based lookup.
*/
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;
typedef long long ll;
const int N = 1003;
map<ll, ll> mp;
ll n, a[N], b[N], v[N];
int T;
bool C(ll k) {
  mp.clear();
  for (int i = 1; i <= n; i++)
    mp[b[i]]++, v[i] = 0;
  for (int i = n; i > 0; i--) {
    ll x = a[i] + k, y = abs(a[i] - k);
    if (mp.count(x) && mp[x]) {
      mp[x]--;
      v[i] = 1;
      continue;
    }
    if (mp.count(y) && mp[y]) {
      mp[y]--;
      v[i] = 2;
      continue;
    }
    return 0;
  }
  cout << "YES" << endl;
  ll p = (k <= 1e9) ? 1e9 : 2e9 - k;
  for (int i = 1; i <= n; i++)
    cout << p + ((v[i] == 1) ? -a[i] : a[i]) << " ";
  cout << endl << p << " " << p + k << endl;
  return 1;
}
void Solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    cin >> b[i];
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++)
    if (C(a[1] + b[i]) || C(abs(a[1] - b[i])))
      return;
  cout << "NO" << endl;
}
int main() {
  cin >> T;
  while (T--)
    Solve();
}

// https://github.com/VaHiX/CodeForces/