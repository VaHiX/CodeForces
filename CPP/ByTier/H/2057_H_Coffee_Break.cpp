// Problem: CF 2057 H - Coffee Break
// https://codeforces.com/contest/2057/problem/H

/*
H. Coffee Break

Algorithm:
This problem uses a two-pass approach with a stack-based simulation to compute the maximum number of students that can be gathered at each coffee machine.

The key idea is to simulate the movement of students using a stack-based greedy strategy:
1. For each position, simulate how many students can be moved from adjacent positions.
2. The "get_right_out" and "get_left_out" functions calculate contributions from left and right respectively.
3. Using a monotonic stack to efficiently propagate student flows.

Time Complexity: O(n) per test case
Space Complexity: O(n) for auxiliary arrays and stack storage

*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using vi = vector<int>;
using ll = long long;
vector<ll> a, lhs, rhs;
vector<int> st;

// Computes how many students can be moved to the right from each position.
// This simulates moving students from current room to the next one.
vector<ll> get_right_out(const vector<ll> &a, vector<ll> &res) {
  const int n = a.size();
  st.clear(); // Reset stack
  res.assign(n + 1, 0); // Initialize result array with zeros
  for (int i = 0; i < n; ++i) {
    ll x = a[i] + res[i]; // Current number of students at position i
    st.push_back(i); // Push index onto stack
    while (x != 0) {
      if (st.empty()) { // If stack is empty, distribute remaining students
        const int len = i + 1;
        const ll cnt = x / (len + 1); // Number of full rounds to process
        res[i + 1] += cnt * len; // Add to next position
        x -= cnt * (len + 1);
        if (x != 0) {
          res[i + 1] += x;
          st.push_back(x - 1);
          x = 0;
        }
      } else {
        const int j = st.back(); // Get last index from stack
        if (x > i - j) { // If more students than available space
          res[i + 1] += i - j; // Move all students to next room
          st.pop_back();
          x -= i - j + 1;
        } else { // Else move only required number of students
          res[i + 1] += x;
          st.back() += x;
          x = 0;
        }
      }
    }
  }
  return res;
}

// Computes how many students can be moved to the left from each position.
// Reverses array, applies right-out computation, then reverses back.
vector<ll> get_left_out(vector<ll> &a, vector<ll> &b) {
  reverse(a.begin(), a.end());
  get_right_out(a, b);
  reverse(b.begin(), b.end());
  reverse(a.begin(), a.end());
  return b;
}

void solve() {
  int n;
  cin >> n;
  a.resize(n);
  for (ll &x : a)
    cin >> x;

  get_right_out(a, lhs); // Compute left contributions
  get_left_out(a, rhs);  // Compute right contributions

  ll ans = 0;
  for (int i = 0; i < n; ++i)
    cout << lhs[i] + a[i] + rhs[i + 1] << ' '; // Combine all contributions
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/