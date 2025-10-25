// Problem: CF 1886 C - Decreasing String
// https://codeforces.com/contest/1886/problem/C

/*
 * Problem: Decreasing String
 * 
 * Algorithm/Techniques:
 * - Precompute all possible strings s1, s2, ..., sn by removing one character at a time in a way
 *   that each resulting string is lexicographically minimal.
 * - For a given position pos in the concatenated string S, determine which original string 
 *   S_i contains pos and then find the character at the corresponding index in S_i.
 * - The key idea is that at each step, to minimize the lexicographically, we remove the leftmost
 *   character that is greater than the next character. This is implemented using a greedy approach
 *   and a stack-like process (str2 array simulates this).
 * 
 * Time Complexity:
 * - For each test case: O(n^2), where n is the length of the input string. In the worst case,
 *   the inner loop runs up to n times for each outer iteration, making it O(n^2).
 * - Overall: O(sum of n over all test cases), which is bounded by 10^6.
 * 
 * Space Complexity:
 * - O(n) for storing the input string and auxiliary arrays.
 */

#include <string.h>
#include <iostream>

#define inf 1000000000000000000
#define int long long
#define mod 998244353
using namespace std;
const int maxn = 2e6 + 5;
char str[maxn], str2[maxn];

void solve() {
  int pos;
  cin >> str + 1 >> pos;  // Read input string starting from index 1
  int n = strlen(str + 1);  // Length of the input string
  int ans = 0, id = 0;  // ans tracks cumulative length of all previous strings

  // Loop through all possible string lengths from n down to 1
  for (int i = 1; i <= n; i++) {
    // If pos lies within the range of current string's total count (from previous strings)
    if (ans + n - i + 1 >= pos) {
      // Adjust pos to index within the current string
      pos -= ans;
      int lef = 0, last = 0;
      
      // Generate the i-th string using a greedy algorithm to get lexicographically minimal
      for (int j = 1; j <= n; j++) {
        // Remove characters from str2 (simulating a stack) while maintaining order
        while (lef > 0 && last < i - 1 && str2[lef] > str[j]) {
          last++;  // Increment last to mark how many characters we've removed
          lef--;   // Remove the character from the result
        }
        str2[++lef] = str[j];  // Add current character to the result
      }
      
      // Output the required character at position pos in the i-th string
      cout << str2[pos];
      return;
    }
    // Increase the cumulative length by the size of the next string
    ans += (n - i + 1);
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/