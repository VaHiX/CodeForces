// Problem: CF 2046 E1 - Cheops and a Contest (Easy Version)
// https://codeforces.com/contest/2046/problem/E1

/*
Code Purpose:
This code solves a contest problem where we need to select a set of problems such that each participant from city i solves strictly more problems than participants from city j (for i < j). 
The approach involves:
1. Processing input data to map specializations to indices
2. For each city, determining the minimum strength required for participants to solve at least one problem
3. Constructing problem sets to ensure participants from earlier cities solve MORE problems than later ones
4. Utilizing binary search and sorting for efficient processing

Algorithms/Techniques:
- Binary search (for mapping specializations to indices)
- Sorting (for processing participants and topics)
- Greedy selection of problem difficulties and topics
- Unique element removal using STL functions

Time Complexity: O(n * log(n) + m * n)
Space Complexity: O(n + m)
*/
#include <stddef.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <utility>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
const ll inf = 2e18;
const ll mod = 998244353;
void run_case() {
  ll n, m;
  cin >> n >> m;
  vector<array<ll, 3>> a(n);
  vector<ll> t;
  for (ll i = 0; i < n; i++) {
    cin >> a[i][0] >> a[i][1] >> a[i][2];
    t.push_back(a[i][2]);
  }
  sort(t.begin(), t.end());
  t.erase(unique(t.begin(), t.end()), t.end()); // Remove duplicates from topics
  vector<ll> unused;
  if (t[0] != 0) {
    unused.push_back(0);
    if (t[0] != 1) {
      unused.push_back(1);
    }
  }
  if (t.back() != 1e9) {
    unused.push_back(1e9);
    if (t.back() != 1e9 - 1) {
      unused.push_back(1e9 - 1);
    }
  }
  for (ll i = 1; i < t.size(); i++) {
    if (t[i] != t[i - 1] + 1) {
      unused.push_back(t[i] - 1);
      if (t[i] != t[i - 1] + 2) {
        unused.push_back(t[i] - 2);
      }
      break;
    }
  }
  for (ll i = 0; i < n; i++) {
    a[i][2] = lower_bound(t.begin(), t.end(), a[i][2]) - t.begin(); // Map original topic to index
  }
  ll Asz;
  cin >> Asz;
  vector<ll> A(Asz), Amn(t.size(), inf);
  vector<vector<ll>> Bs(t.size());
  for (ll i = 0; i < Asz; i++) {
    cin >> A[i];
    A[i]--;
  }
  ll Bsz;
  cin >> Bsz;
  vector<ll> B(Bsz);
  ll mx = 0;
  for (ll i = 0; i < Bsz; i++) {
    cin >> B[i];
    B[i]--;
    mx = max(mx, a[B[i]][0]); // Find max strength among participants in city 1 (first city)
    Bs[a[B[i]][2]].push_back(B[i]); // Group participants by specialization
  }
  ll mn1 = inf, mn2 = inf;
  for (ll i = 0; i < Asz; i++) {
    if (a[A[i]][1] <= mx) { // If wisdom is not sufficient for participant to solve more than 1 problem
      cout << "-1\n";
      return;
    }
    if (a[A[i]][0] <= mx) { // If strength is small enough that we need to include this in the first round
      Amn[a[A[i]][2]] = min(Amn[a[A[i]][2]], a[A[i]][1]);
      mn1 = min(mn1, a[A[i]][0]); // Track minimum strength that satisfies condition
    } else {
      mn2 = min(mn2, a[A[i]][0]); // Track minimum strength for other cases
    }
  }
  vector<ll> sc(n, 0); // Count how many problems each participant solves
  vector<pll> ans;
  if (mn1 != inf) {
    ans.push_back({mn1, unused[0]}); // Add a problem with difficulty mn1 and a unused topic
    for (ll i = 0; i < n; i++) {
      if (a[i][0] >= mn1) { // All participants who can solve this problem
        sc[i]++;
      }
    }
  }
  if (mn2 != inf) {
    ans.push_back({mn2, unused[1]}); // Add a problem with difficulty mn2 and another unused topic
  }
  for (ll i = 0; i < t.size(); i++) {
    if (Amn[i] == inf) // Skip if no participant in this topic group satisfies conditions
      continue;
    ans.push_back({Amn[i], t[i]}); // Add a problem for this specialization
    for (auto &j : Bs[i]) { // Increment solve count for participants in this specialization
      if (a[j][1] >= Amn[i]) {
        sc[j]++;
      }
    }
  }
  for (ll i = 0; i < n; i++) {
    if (sc[i] >= 2) { // If any participant solves more than one problem, impossible
      cout << "-1\n";
      return;
    }
  }
  cout << ans.size() << '\n';
  for (auto &[x, y] : ans) {
    cout << x << ' ' << y << '\n';
  }
}
int main() {
  ios_base ::sync_with_stdio(false);
  cin.tie(NULL);
  int tc;
  cin >> tc;
  while (tc--) {
    run_case();
  }
}


// https://github.com/VaHiX/CodeForces/