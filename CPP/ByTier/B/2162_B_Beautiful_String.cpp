// Problem: CF 2162 B - Beautiful String
// https://codeforces.com/contest/2162/problem/B

/*
Algorithm: Greedy approach
- The key insight is that for a subsequence to be non-decreasing in a binary string,
  it must consist of all '0's followed by all '1's (or just '0's, or just '1's).
- We want to remove a subsequence such that the remaining string is a palindrome.
- A good strategy is to take all the '1's in order to form a non-decreasing subsequence.
  When we remove all '1's, the remaining string consists of only '0's, which is always a palindrome.
- This greedy choice works because:
  1. The subsequence of '1's is non-decreasing.
  2. After removing the '1's, what remains is a string of '0's, which is trivially a palindrome.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing indices

The code:
- Reads input string s
- For each '1' in the string, stores its 1-based index in array b
- Outputs the count of '1's and their indices
*/
#include <iostream>
#include <string>

using namespace std;
constexpr int MAXN = 1e3 + 1;
int b[MAXN];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;
    int k = 0;
    for (int i = 0; i < n; i++)
      if (s[i] == '1')           // If character is '1', store its index
        b[k++] = i + 1;          // Store 1-based index
    cout << k << '\n';           // Output number of '1's
    for (int i = 0; i < k; i++) {
      cout << b[i];
      if (i < k - 1)
        cout << ' ';             // Print space between indices
    }
    cout << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/