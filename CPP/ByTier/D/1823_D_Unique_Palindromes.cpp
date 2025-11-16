// Problem: CF 1823 D - Unique Palindromes
// https://codeforces.com/contest/1823/problem/D

/*
 * Problem: D. Unique Palindromes
 * 
 * Purpose: Given a string length n and k conditions specifying the number of unique
 *          palindromic substrings in prefixes of the string, find a valid string
 *          that satisfies all conditions or determine that none exists.
 * 
 * Algorithm:
 * 1. First, we check the feasibility of conditions:
 *    - Each prefix length x[i] must be at least as large as the number of palindromes c[i].
 *    - The difference in palindromes between consecutive conditions must be less than or equal
 *      to the difference in prefix lengths.
 * 2. Then we construct a valid string:
 *    - Start with a base string "abc".
 *    - For each condition, add characters to meet the palindrome count requirements,
 *      alternating between new characters and repeated characters.
 *    - Pad the result to length n with 'a's.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> x(k + 1), c(k + 1);
  for (int i = 1; i <= k; i++) {
    cin >> x[i];
  }
  for (int i = 1; i <= k; i++) {
    cin >> c[i];
  }
  x[0] = 3, c[0] = 3;
  for (int i = 0; i < k; i++) {
    // Check if the prefix length is sufficient for the number of palindromes required
    if (x[i] < c[i]) {
      cout << "NO" << '\n';
      return;
    }
    // Check if the increase in palindromes is feasible given the prefix length increase
    if (i < k && x[i + 1] - x[i] < c[i + 1] - c[i]) {
      cout << "NO" << '\n';
      return;
    }
  }
  cout << "YES" << '\n';
  string ans = "abc";  // Initial string with 3 palindromes
  int next_char = 0;   // Index for the next character to use
  string X = "abc";    // String used to generate new palindromes
  int cnt = 3;         // Count of palindromes in current prefix
  
  // Process each condition
  for (int i = 0; i < k; i++) {
    int A = c[i + 1] - c[i];  // Difference in palindromes
    int B = x[i + 1] - x[i];  // Difference in prefix lengths
    
    // Add characters that don't contribute to new palindromes
    for (int j = 0; j < B - A; j++) {
      char nc = (int)('a' + next_char);
      ans += nc;
      next_char++;
      next_char %= 3;  // Cycle through a, b, c
    }
    
    // Add characters that do contribute to new palindromes
    for (int j = 0; j < A; j++) {
      ans += (int)('a' + cnt);
    }
    
    if (A) {
      cnt++;  // Increment to next palindrome count
    }
  }
  
  // Pad the result to reach the required string length n
  while (ans.size() < n) {
    ans += 'a';
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/