// Problem: CF 2037 E - Kachina's Favorite Binary String
// https://codeforces.com/contest/2037/problem/E

/*
Algorithm/Technique:
- The problem involves reconstructing a binary string from queries about the number of "01" subsequences in substrings.
- The approach is to make queries of the form f(1, i) for i = 2 to n.
- This allows us to understand how many "01" subsequences exist in increasing prefixes of the string.
- By analyzing the sequence of answers, we can determine the structure of the string.
- If we can determine a unique string from the answers, we output it; otherwise, we output IMPOSSIBLE.

Time Complexity: O(n^2) - In worst case, we process n queries and then reconstruct the string with some nested operations.
Space Complexity: O(n) - We store the answers to queries and build the result string.
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define int long long int
const int N = 1e9 + 7;
#define pb push_back
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s = "";
    // Make queries for f(1, i) where i goes from 2 to n
    for (int i = 2; i <= n; i++) {
      cout << '?' << " " << 1 << " " << i << endl;
      cout << flush;
    }
    bool flag = 0;
    vector<int> ans;
    // Read all the answers to our queries
    for (int i = 0; i < n - 1; i++) {
      int x;
      cin >> x;
      ans.pb(x);
    }
    // Reconstruct the string based on the answers
    for (int i = 0; i < n - 1; i++) {
      if (!flag) {
        // If the first answer (f(1,2)) is 0, we don't know the first character
        if (ans[i] == 0) {
          continue;
        } else {
          // If the answer is not zero, we know there is at least one "01" subsequence
          s.pb('1');
          // Append '0' for each count in the answer
          for (int j = 0; j < ans[i]; j++) {
            s = '0' + s;
          }
          flag = 1;
          continue;
        }
      }
      if (flag) {
        // If the difference between current and previous answer is 0, it's a '0'
        if (ans[i] == ans[i - 1]) {
          s.pb('0');
        } else {
          // Otherwise it's a '1'
          s.pb('1');
        }
      }
    }
    // Adjust the length of the string to the required n
    int p = n - s.length();
    for (int i = 0; i < p; i++) {
      s = '1' + s;
    }
    // Output result
    if (!flag) {
      cout << '!' << " " << "IMPOSSIBLE" << endl;
    }
    if (flag) {
      cout << '!' << " " << s << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/