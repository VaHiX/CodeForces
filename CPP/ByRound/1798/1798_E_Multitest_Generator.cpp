// Problem: CF 1798 E - Multitest Generator
// https://codeforces.com/contest/1798/problem/E

/*
Algorithm: Dynamic Programming with Preprocessing
Approach:
- We process the array from right to left to determine if a subarray starting at index i can form a valid multitest.
- For each position, we check if we can form a valid test by using a[i] as the length of the first subarray.
- We maintain three arrays:
  - poss[i]: whether a subarray starting at i can form a valid multitest.
  - count[i]: minimum operations needed to make subarray starting at i a multitest.
  - mx[i]: maximum count value reachable from position i.
- Then for each prefix, we determine f based on the precomputed values.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the arrays used
*/
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <stddef.h>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace __gnu_pbds;
template <class T>
using oset =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define ll long long
#define ld long double
#define ar array
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int, int>
#define pb push_back
#define all(x) x.begin(), x.end()
#define f first
#define s second
#define endl "\n"
const int MOD = 1e9 + 7;
const int inf = 1e9;
const ll linf = 1e18;
const int d4i[4] = {-1, 0, 1, 0}, d4j[4] = {0, 1, 0, -1};
const int d8i[8] = {-1, -1, 0, 1, 1, 1, 0, -1},
          d8j[8] = {0, 1, 1, 1, 0, -1, -1, -1};
void sol() {
  int n;
  cin >> n;
  vi a(n), poss(n + 1), count(n + 1), mx(n + 1);
  poss[n] = true;
  count[n] = 0;
  mx[n] = 0;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  int mxx = 0;
  for (int i = n - 1; i >= 0; i--) {
    // Update the max reachable count
    mx[i] = max(mxx + 1, mx[i]);
    // If a[i] + i + 1 exceeds array bounds, it's impossible to form a valid test
    if (a[i] + i + 1 > n) {
      poss[i] = false;
      count[i] = 1;
      continue;
    }
    // Check if we can form a valid multitest from this point
    poss[i] = poss[a[i] + i + 1];
    count[i] = 1 + count[a[i] + i + 1];
    // Update the maximum reachable count
    mx[i] = max(mx[i], mx[a[i] + i + 1] + 1);
    if (poss[i])
      mxx = max(mxx, count[i]);
  }
  // Compute answer for each prefix
  for (int i = 0; i < n - 1; i++) {
    // If we can form a multitest at i+1 and a[i] equals the required count
    if (poss[i + 1] && a[i] == count[i + 1])
      cout << 0 << " ";
    // If we can form a multitest here, only one operation is needed
    else if (poss[i + 1])
      cout << 1 << " ";
    // If a[i] is small enough to make it work
    else if (a[i] <= mx[i + 1])
      cout << 1 << " ";
    else
      cout << 2 << " ";
  }
  cout << endl;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  cin >> t;
  while (t--) {
    sol();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/