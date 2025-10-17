// Problem: CF 2136 B - Like the Bitset
// https://codeforces.com/contest/2136/problem/B

/*
B. Like the Bitset
time limit per test1 second
memory limit per test256 megabytes

Algorithms/Techniques:
- Greedy approach with interval constraint checking
- Segment validation using maximum element property
- Permutation construction based on binary string positions

Time Complexity: O(n) per test case, where n is the length of the string s.
Space Complexity: O(n) for storing the input and output permutation.

Task:
You are given a binary string s of length n, as well as an integer k.
Aquawave wants to construct a permutation p of length n, so that for each 1 <= i <= n where s[i] = '1',
the following holds:
For each interval [l,r] (1 <= l <= r <= n) whose length is at least k (i.e. r - l + 1 >= k),
if it covers position i (i.e. l <= i <= r), then the maximum element among p[l], p[l+1], ..., p[r]
is not p[i].

Input:
Each test contains multiple test cases. The first line contains the number of test cases t.
The first line of each test case contains two integers n and k (1 <= n <= 2*10^5, 1 <= k <= n)
The second line contains the binary string s of length n.

Output:
If there is at least one possible permutation:
Print "YES" in the first line of output;
Then, print n integers p_1, p_2, ..., p_n (1 <= p_i <= n, all p_i-s are distinct) in the second line.
Otherwise, print "NO" in the single line of output.

*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void solve() {
  int n, k;
  string s;
  cin >> n >> k >> s;
  int mx = 0, cur = 0;
  for (char c : s) {
    if (c == '1')
      cur++; // Count consecutive 1s
    else {
      if (cur > mx)
        mx = cur; // Keep track of maximum consecutive 1s
      cur = 0;
    }
  }
  if (cur > mx)
    mx = cur;
  if (mx >= k)
    cout << "NO\n"; // If any sequence of 1s is longer than or equal to k, impossible
  else {
    int cnt = count(s.begin(), s.end(), '1');
    int sm = 1, lg = cnt + 1; // Assign smaller numbers to 1s, larger to 0s
    cout << "YES\n";
    for (char c : s) {
      if (c == '1')
        cout << sm++ << " "; // Smaller numbers (1 to cnt) for indices with '1'
      else
        cout << lg++ << " "; // Larger numbers (cnt+1 to n) for indices with '0'
    }
    cout << "\n";
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/