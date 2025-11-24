// Problem: CF 2002 E - Cosmic Rays
// https://codeforces.com/contest/2002/problem/E

/*
E. Cosmic Rays
Algorithm/Techniques: Stack-based simulation with pair compression
Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

This code simulates the process of cosmic rays deleting elements from a compressed array,
where each element is represented as a pair (count, value). The strength of an array is 
the number of seconds it takes to become empty under the described deletion rules.

The solution uses a stack to maintain active pairs and computes the strength for each prefix
by simulating the deletion process efficiently.
*/

#include <iostream>
#include <utility>

#define int long long
using namespace std;
const int maxn = 3e5 + 10;
pair<int, int> s[maxn];
int tp, n;

void sol() {
  cin >> n;
  tp = 0;
  for (int i = 1, a, b; i <= n; ++i) {
    cin >> a >> b;
    // While stack is not empty and current element's value is greater than or equal to
    // the top of stack, merge elements (simulate deletion process)
    while (tp && s[tp].first <= a) {
      --tp;
      if (tp && s[tp].second == b)
        --tp, a = s[tp + 1].first + a - s[tp + 2].first;
    }
    s[++tp] = {a, b}; // Push current element onto stack
    cout << s[1].first << ' '; // Output the strength (first element of stack)
  }
  cout << '\n';
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    sol();
}


// https://github.com/VaHiX/codeForces/