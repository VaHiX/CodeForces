// Problem: CF 2081 B - Balancing
// https://codeforces.com/contest/2081/problem/B

/*
B. Balancing
Algorithms/Techniques: Greedy, Segment Analysis
Time Complexity: O(n) per test case
Space Complexity: O(n) for the array

The problem involves making an array strictly increasing using minimal operations.
Each operation allows replacing a subarray with any values preserving the relative order of elements.
We analyze the array to identify segments where the sequence is decreasing, and count how many such segments exist.
Then we compute the minimal number of operations based on these segments.
*/
#include <iostream>

#define int long long
using namespace std;
int t, n, s, l, r, a[200005];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    s = l = 0; // s: count of decreasing transitions, l: start of first decreasing segment
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int i = 1; i < n; i++)
      if (a[i] > a[i + 1]) { // If current element is greater than next, it's a decreasing transition
        s++; // Increment the count of transitions
        r = i + 1; // Record the end of this decreasing segment
        if (!l)
          l = i; // Record start of first transition
      }
    // If number of transitions is odd or if there is a transition where difference is less than length,
    // we need one more operation.
    if (s % 2 || (s && a[r] - a[l] < r - l))
      cout << s / 2 + 1 << '\n';
    else
      cout << s / 2 << '\n';
  }
}


// https://github.com/VaHiX/codeForces/