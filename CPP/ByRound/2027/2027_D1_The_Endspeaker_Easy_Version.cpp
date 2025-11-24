// Problem: CF 2027 D1 - The Endspeaker (Easy Version)
// https://codeforces.com/contest/2027/problem/D1

/*
D1. The Endspeaker (Easy Version)
Algorithms/Techniques: Dynamic Programming with Two Pointers

Time Complexity: O(n * m) per test case
Space Complexity: O(n + m)

This problem uses dynamic programming with a sliding window technique to find the minimum cost of removing all elements from array 'a' using operations on array 'b'. 
The key idea is that at each step, we decide how many elements to remove based on the current value of k (which corresponds to b[k]) and track the minimum total cost.
A two-pointer approach is used in the DP update step to efficiently compute valid prefixes.
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef unordered_map<ll, vl> mlv;
typedef unordered_map<ll, bool> mlb;
const ll infll = 1e18;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vl a(n + 1), pre(n + 1);
    ll max_a = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      max_a = max(max_a, a[i]);
      pre[i] = pre[i - 1] + a[i]; // prefix sum
    }
    vl b(m + 1);
    for (int i = 1; i <= m; i++)
      cin >> b[i];
    if (max_a > b[1]) { // if any element is larger than the max possible prefix sum, impossible
      cout << "-1\n";
      continue;
    }
    vl dp(n + 1, infll); // dp[i] = minimum cost to make first i elements empty
    dp[0] = 0; // base case: no cost for empty array
    for (int j = 1; j <= m; j++) {
      int l = 0, r = 1;
      while (r <= n) {
        while (l < r && pre[r] - pre[l] > b[j]) // shrink window from left until valid prefix
          l++;
        if (l < r)
          dp[r] = min(dp[r], dp[l] + m - j); // update with cost of operation type 2
        r++;
      }
    }
    cout << dp[n] << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/