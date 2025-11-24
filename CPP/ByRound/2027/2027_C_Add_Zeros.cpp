// Problem: CF 2027 C - Add Zeros
// https://codeforces.com/contest/2027/problem/C

/*
C. Add Zeros
Algorithm: Greedy with sorting and set operations
Time Complexity: O(n log n) per test case due to sorting and set operations
Space Complexity: O(n) for storing the array and set

The problem involves maximizing the length of an array by performing operations where:
1. Choose position i such that a[i] = |a| + 1 - i (where |a| is current size)
2. Append i-1 zeros to the end of the array
We use a greedy approach with sorting to determine optimal order of operations.
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>

using namespace std;
#define int long long
int T, n;
const int maxn = 3e5 + 5;
pair<int, int> a[maxn];

void solve() {
  set<int> st; // Set to keep track of valid ending positions
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i].first, a[i].first += i - 1, a[i].second = i; // Transform values and store position
  sort(a + 1, a + n + 1); // Sort by transformed value
  st.emplace(n); // Initialize set with last index
  for (int i = 1; i <= n; ++i)
    if (st.count(a[i].first)) // If current transformed value is in set
      st.emplace(a[i].first + a[i].second - 1); // Add new valid ending position
  cout << *st.rbegin() << '\n'; // Output maximum possible length
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/