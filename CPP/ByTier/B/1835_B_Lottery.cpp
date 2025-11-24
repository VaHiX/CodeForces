// Problem: CF 1835 B - Lottery
// https://codeforces.com/contest/1835/problem/B

/*
Purpose: This code solves the lottery problem where Bytek, the last participant, wants to maximize his chance of winning
         by choosing an optimal value for his ticket. The lottery selects a target number uniformly from 0 to m,
         and k closest numbers to the target (with tie-breaking by index) are declared winners.
         Bytek's goal is to determine the best value to pick and the number of winning target values for that choice.

Algorithm:
    - Sort the ticket values of previous participants.
    - For each unique value in the sorted list:
        * Consider different candidate values around the current value (v[i], v[i]+1, v[i]+2)
        * For each candidate value, calculate how many targets would make Bytek a winner.
        * Track the maximum count and smallest optimal value.

Time Complexity: O(n log n) due to sorting, where n is the number of participants.
Space Complexity: O(n) for storing ticket values.

Techniques:
    - Sorting and sliding window analysis
    - Binary search-like calculations to count valid targets
    - Greedy optimization for maximizing win count
*/

#include <algorithm>
#include <iostream>
#include <vector>

#define fi first
#define se second
using namespace std;

void solve() {
  using ll = long long;
  int n;
  ll m;
  int k;
  cin >> n >> m >> k;
  vector<ll> v(n);
  for (auto &x : v)
    cin >> x;
  
  // If k is greater than or equal to n, Bytek will always win
  if (k > n)
    return cout << m + 1 << " 0\n", [] {}();

  sort(v.begin(), v.end());
  ll ans1{}, ans2{0};
  
  // Iterate through groups of identical values
  for (int i{0}, j; i < n; i = j) {
    j = i + 1;
    // Move to the end of the group of equal values
    while (j < n && v[j] == v[i])
      ++j;
    
    // Check if we can place the candidate value (v[i] - 2) to have a chance of winning
    if (i < k && (i ? v[i - 1] : -1) < v[i] - 2) {
      ll x{-1};
      // Calculate the right boundary of the target range
      ll y{i + k - 1 < n ? (v[i] - 2 + v[i + k - 1] - 1) / 2 : m};
      if (y - x > ans1)
        ans1 = y - x, ans2 = v[i] - 2;
    }

    // Check candidate value (v[i] - 1)
    if (i < k && (i ? v[i - 1] : -1) < v[i] - 1) {
      ll x{-1};
      ll y{i + k - 1 < n ? (v[i] - 1 + v[i + k - 1] - 1) / 2 : m};
      if (y - x > ans1)
        ans1 = y - x, ans2 = v[i] - 1;
    }

    // Check candidate value v[i]
    {
      ll x{j - k >= 0 ? (v[j - k] + v[i]) / 2 : -1};
      ll y{i + k - 1 < n ? (v[i] + v[i + k - 1] - 1) / 2 : m};
      if (y - x > ans1)
        ans1 = y - x, ans2 = v[i];
    }

    // Check candidate value (v[i] + 1)
    if (v[i] + 1 < (j < n ? v[j] : m + 1)) {
      ll x{j - k >= 0 ? (v[j - k] + v[i] + 1) / 2 : -1};
      ll y{j + k - 1 < n ? (v[i] + 1 + v[j + k - 1] - 1) / 2 : m};
      if (y - x > ans1)
        ans1 = y - x, ans2 = v[i] + 1;
    }

    // Check candidate value (v[i] + 2)
    if (v[i] + 2 < (j < n ? v[j] : m + 1)) {
      ll x{j - k >= 0 ? (v[j - k] + v[i] + 2) / 2 : -1};
      ll y{j + k - 1 < n ? (v[i] + 2 + v[j + k - 1] - 1) / 2 : m};
      if (y - x > ans1)
        ans1 = y - x, ans2 = v[i] + 2;
    }
  }
  cout << ans1 << ' ' << ans2 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t{1};
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/