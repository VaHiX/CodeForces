// Problem: CF 2077 D - Maximum Polygon
// https://codeforces.com/contest/2077/problem/D

/*
D. Maximum Polygon
time limit per test3 seconds
memory limit per test256 megabytes

Task:
Given an array a of length n, determine the lexicographically largest subsequence s of a such that s can be the side lengths of a polygon.

Recall that s can be the side lengths of a polygon if and only if |s|≥3 and 2*max(s1,s2,...,s|s|) < s1+s2+...+s|s|.

Algorithms/Techniques:
- Sorting and binary search
- Stack-based monotonic processing for prefix maximums
- Greedy selection of elements to build valid polygonal subsequence
- Lexicographically largest subsequence selection

Time Complexity: O(n log n) per test case due to sorting and linear passes.
Space Complexity: O(n) for storing arrays, vectors, and stack.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int T;
int n;
typedef long long ll;
const int MAXN = 2e5 + 10;
int a[MAXN], b[MAXN];
// Function to compare two vectors lexicographically returns larger
vector<int> max(vector<int> a, vector<int> b) {
  for (int i = 0; i < min(a.size(), b.size()); ++i) {
    if (a[i] > b[i])
      return a;
    if (b[i] > a[i])
      return b;
  }
  return a.size() > b.size() ? a : b;
}
int st[MAXN], top;
// Solve for a given maximum element x in the sorted array
vector<int> solve(int x) {
  vector<int> v;
  v.push_back(0); // Sentinel value to simplify index management
  for (int i = 1; i <= n; ++i)
    if (a[i] <= x) // Only consider elements up to threshold x
      v.push_back(a[i]);
  int m = v.size() - 1;
  vector<int> pos(m + 1); // pos[i] stores index of next greater element to the right
  top = 0;
  for (int i = m; i; --i) {
    while (top && v[st[top]] <= v[i]) // Maintain decreasing stack
      --top;
    pos[i] = st[top]; // Store index of nearest greater element
    st[++top] = i;
  }
  vector<ll> sum(m + 1); // Prefix sums for quick range sum queries
  for (int i = 1; i <= m; ++i) {
    sum[i] = sum[i - 1] + v[i];
  }
  ll ret = sum[m]; // Total sum of valid elements
  if (2 * x >= ret) // If even the largest element fails polygon condition, return empty
    return vector<int>();
  int p = 1;
  vector<int> ans;
  while (p <= m) {
    ll s = sum[pos[p] - 1] - sum[p - 1]; // Sum of subarray before pos[p]
    if (pos[p] && 2 * x < ret - s) { // Can we use the current portion?
      ret -= s;
      p = pos[p] - 1; // Skip to next segment
    } else
      ans.push_back(v[p]); // Add element to answer
    ++p;
  }
  return ans;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      b[i] = a[i];
    }
    sort(b + 1, b + n + 1); // Sort to find candidate maxes in order
    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
      if (i == n || 2 * b[i] < b[i + 1]) // Select unique thresholds
        ans = max(ans, solve(b[i])); // Find best subsequence with this max element
    }
    if (ans.empty())
      cout << "-1\n";
    else {
      cout << ans.size() << '\n';
      for (auto v : ans)
        cout << v << ' ';
      cout << '\n';
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/