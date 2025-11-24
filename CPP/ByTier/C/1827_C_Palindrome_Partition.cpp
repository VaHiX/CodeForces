// Problem: CF 1827 C - Palindrome Partition
// https://codeforces.com/contest/1827/problem/C

/*
Algorithm: Manacher's Algorithm with modifications to count beautiful substrings
Techniques: 
- Manacher's Algorithm for finding all palindromic substrings efficiently
- Using a stack-based approach to track and count partitions into even palindromes

Time Complexity: O(n) amortized, where n is the length of the string
Space Complexity: O(n), for storing the modified string and auxiliary arrays

The code modifies the input string to handle both even and odd-length palindromes,
then uses Manacher's algorithm to efficiently find all palindromic substrings. 
It maintains counts of how many ways each position can be partitioned into even palindromes,
and accumulates this to compute the total number of beautiful substrings.
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
int n;
void solve() {
  string s;
  cin >> n;
  cin >> s;
  n += 2;
  s = '#' + s + '@'; // Add sentinels to simplify edge cases
  vector<int> d(n), ans(n), st; // d: palindrome radius, ans: count of partitions, st: stack for indices
  ll res = 0;
  for (int i = 1, f = 0; i < n - 1; i++) {
    // Use previously computed values to avoid redundant comparisons
    if (d[f] + f > i)
      d[i] = min(d[f] + f - i, d[f - (i - f)]);
    // Expand palindrome centered at i
    while (s[i + d[i] + 1] == s[i - d[i]])
      d[i]++, f = i;
    st.push_back(i - 1); // Push the index into stack (adjusted for 0-based indexing)
    while (!st.empty()) {
      int p = st.back();
      if (d[p] + p < i) {
        st.pop_back(); // Pop if current palindrome doesn't include it
      } else {
        int l = p - (i - p); // Mirror index
        ans[i] = ans[l] + 1; // Update count based on mirrored count
        break;
      }
    }
    res += ans[i]; // Accumulate result
  }
  cout << res << "\n";
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/