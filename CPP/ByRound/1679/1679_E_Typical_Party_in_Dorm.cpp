// Problem: CF 1679 E - Typical Party in Dorm
// https://codeforces.com/contest/1679/problem/E

/*
Code Purpose:
This code solves the problem of counting all palindromic substrings across all possible strings formed
by replacing question marks in a given string with characters from a queried set. It uses dynamic programming
and bitmasking to efficiently compute the result for each query.

Algorithms/Techniques:
- Dynamic Programming with bitmasking to represent character sets
- Precomputation of powers of base for polynomial hashing
- Recursive function to expand palindromes from centers
- Prefix sum technique using bitmask manipulation

Time Complexity:
- Preprocessing: O(n^2) for precomputing dp states
- Query processing: O(q * 2^17) where q is number of queries
- Overall: O(n^2 + q * 2^17)

Space Complexity:
- O(n * 2^17) for storing dp states
*/

#include <iostream>
#include <string>

using namespace std;
#define rd(i, n) for (int i = 0; i < n; i++)
#define rp(i, n) for (int i = 1; i <= n; i++)
#define ll long long
#define st string
#define pb push_back
const ll P = 998244353;
ll ans[20][1 << 18], p[20][1005], n;
st s, t;

// Function to expand palindrome from center (l, r) and update answer
void fnd(int l, int r, int a, int q) {
  // Base case: out of bounds
  if (l < 0 || r >= n)
    return;
  
  // Handle case when both characters are '?'
  if (s[l] == '?' && s[r] == '?')
    q--;
  else if (s[l] == '?') {
    // If only left is '?', update the character set with right char
    q--;
    a |= (1 << (s[r] - 'a'));
  } else if (s[r] == '?') {
    // If only right is '?', update the character set with left char
    q--;
    a |= (1 << (s[l] - 'a'));
  } else if (s[l] != s[r])
    // If characters don't match, this cannot be a palindrome
    return;
  
  // Add contribution of this palindrome to the answer
  rd(i, 18) ans[i][a] = (ans[i][a] + p[i][q]) % P;
  
  // Continue expanding the palindrome
  fnd(l - 1, r + 1, a, q);
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int q = 0;
  cin >> n >> s;
  
  // Precompute powers of base
  rd(i, 18) {
    p[i][0] = 1;
    rp(j, n) p[i][j] = p[i][j - 1] * i % P;
  }
  
  // Count number of question marks
  for (auto i : s)
    if (i == '?')
      q++;
  
  // Process each position as a center for odd-length palindromes
  rd(i, n) {
    rd(j, 18) ans[j][0] = (ans[j][0] + p[j][q]) % P;
    fnd(i - 1, i + 1, 0, q);
  }
  
  // Process each pair as center for even-length palindromes
  rd(i, n - 1) fnd(i, i + 1, 0, q);
  
  // Apply prefix sum on dp states using bitmask operations
  rd(i, 18) rd(j, 17) rd(k, 1 << 17) if (k >> j & 1) ans[i][k] =
      (ans[i][k] + ans[i][k - (1 << j)]) % P;
  
  // Read number of queries
  cin >> q;
  
  // Process each query
  rd(i, q) {
    cin >> t;
    int a = 0;
    for (auto j : t)
      a |= (1 << (j - 'a'));
    cout << ans[t.size()][a] << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/