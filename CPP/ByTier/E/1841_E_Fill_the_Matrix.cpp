// Problem: CF 1841 E - Fill the Matrix
// https://codeforces.com/contest/1841/problem/E

/*
Algorithm: Monotonic Stack + Greedy
Approach:
- The problem involves placing integers in a matrix such that:
  - Black cells cannot contain integers.
  - Beauty is defined as the number of adjacent pairs (j, j+1) in the same row.
- For each column, we know how many black cells there are (a[i]), so the rest are white.
- Using a monotonic stack, we precompute the number of white cells in each "segment"
  that can be filled greedily to maximize beauty.
- Then, we use a greedy strategy to assign the integers, maximizing beauty at each step.

Time Complexity: O(n) amortized per test case due to stack operations and linear traversal.
Space Complexity: O(n) for storing arrays and the stack.

*/
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#define endl '\n'
using namespace std;
using ll = long long;
int MOD = 114514;
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> a(n + 2);
    a[0] = a[n + 1] = n;  // Sentinel values for easier computation
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    vector<ll> suf(n + 1);  // suf[i] stores the number of white cells in segments of width i
    stack<int> st;
    st.push(0);
    for (int i = 1; i <= n + 1; ++i) {
      // Maintain a decreasing stack based on a[i]
      while (st.size() >= 2 && a[st.top()] < a[i]) {
        int k = st.top();
        st.pop();
        int j = st.top();
        // Compute contribution of the segment (j+1, k) to suf[i - j - 1]
        suf[i - j - 1] += min(a[i], a[j]) - a[k];
      }
      st.push(i);
    }
    ll m;
    cin >> m;
    ll ans = 0;
    // Greedily assign integers to maximize beauty
    for (int i = n; i; --i) {
      // Determine how many full segments of size i we can fill
      ll mi = min(suf[i], m / i);
      ans += mi * (i - 1);  // Add beauty from these segments
      suf[i - 1] += suf[i] - mi;  // Propagate remaining segments
      m -= mi * i;  // Reduce remaining integers
    }
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/