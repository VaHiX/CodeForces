// Problem: CF 2155 D - Batteries
// https://codeforces.com/contest/2155/problem/D

/*
Problem: D. Batteries
Approach:
- This is an interactive problem where we need to find a working pair of batteries among n batteries.
- Some batteries work and some don't, but we know at least 2 work (a >= 2).
- We can test any two batteries in a flashlight which turns on if both work.
- Goal: Find two working batteries using at most floor(n^2 / a) queries.

Algorithm:
- The strategy uses a nested loop approach where we try pairs of batteries with increasing gap,
  starting from gap=1. For each fixed gap, we iterate through all batteries and test them against
  their "next" battery (with wraparound). When a pair works (returns 1), the solution stops.

Time Complexity: O(n^2) which is acceptable since n <= 40.
Space Complexity: O(1) - only using constant extra space.

*/

#include <stdio.h>
#include <iostream>

using namespace std;
#define int long long
#define deci long double
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define inparr(n)                                                              \
  for (int i = 0; i < n; i++)                                                  \
    cin >> arr[i];
#define fr(s, n) for (int i = s; i < n; i++)
#define rfr(s, n) for (int i = s; i >= n; i--)
#define frj(s, n) for (int j = s; j < n; j++)
#define rfrj(s, n) for (int j = s; j >= n; j--)
#define vi vector<int>
#define pb push_back
#define vvi vector<vector<int>>
#define vpi vector<pair<int, int>>
#define mii map<int, int>
#define pii pair<int, int>
#define txtio                                                                  \
  freopen("substantial_losses_input.txt", "r", stdin);                         \
  freopen("output.txt", "w", stdout);
#define all(x) x.begin(), x.end()

void solve(int test) {
  int n;
  cin >> n;
  int gap = 1; // Start with gap of 1
  while (1) {
    for (int i = 1; i <= n; i++) { // Iterate over all batteries
      int nxt = i + gap; // Compute next battery index
      if (nxt > n)
        nxt %= n; // Wrap around if needed
      cout << i << ' ' << nxt << endl; // Query the flashlight with pair (i, nxt)
      cout.flush(); // Ensure output is flushed to prevent idleness limit error
      int x;
      cin >> x; // Read response from jury
      if (x) // If the flashlight turned on (both batteries work)
        return; // Solution found, exit
    }
    gap++; // Increase gap for next iteration
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/