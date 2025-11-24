// Problem: CF 2136 C - Against the Difference
// https://codeforces.com/contest/2136/problem/C

/*
C. Against the Difference
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Task:
Find the length of the longest "neat" subsequence in an array.
A "neat" subsequence is one that can be split into blocks, where each block consists of k elements all equal to k.

Algorithms/Techniques:
Dynamic Programming with memoization and tracking of element positions.

Time Complexity: O(n)
Space Complexity: O(n)

*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 2e5 + 2;
int T, n, a[N], f[N];
vector<int> id[N]; // id[i] stores positions where value i appears

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n;
    for (int i = 1; i <= n; ++i)
      id[i].clear(); // Clear previous indices for current test case
    for (int i = 1; i <= n; ++i)
      cin >> a[i]; // Read array elements
    for (int i = 1; i <= n; ++i) {
      f[i] = f[i - 1]; // Default: don't take current element
      id[a[i]].push_back(i); // Record index of element a[i]
      // If we have at least a[i] occurrences of a[i], consider forming a block
      if (id[a[i]].size() >= a[i])
        f[i] = max(f[i], f[*(id[a[i]].end() - a[i]) - 1] + a[i]); 
      // Add the size of the block (a[i]) to the best result before this block started
    }
    cout << f[n] << '\n'; // Output the maximum neat subsequence length for current case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/