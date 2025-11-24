// Problem: CF 1742 F - Smaller
// https://codeforces.com/contest/1742/problem/F

/*
Algorithm/Techniques: Greedy, String Manipulation, Prefix Analysis

The problem asks us to determine, after each operation, whether we can rearrange the characters of two strings `s` and `t` such that `s` is lexicographically smaller than `t`. 

Key Insight:
- The lexicographically smaller string will have its first character as small as possible (preferably 'a').
- If `t` contains any character other than 'a', we can always rearrange `s` and `t` such that `s` is smaller.
- If `t` is composed only of 'a's and `s` is longer than `t`, we can also make `s` lexicographically smaller by placing 'a's first in `s` and a larger character later.
- If both `s` and `t` are all 'a's and `len(s) >= len(t)`, it's impossible.

Time Complexity: O(sum of all lengths of x strings) - we process each character in the input strings once.
Space Complexity: O(1) - we only store a few variables and do not use any data structures proportional to input size.
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    long long q, val, n, len1 = 0, len2 = 0; // len1 and len2 store the lengths of s and t respectively
    string str;
    cin >> q;
    bool a = 0, b = 0; // a tracks if s contains non-'a' characters, b tracks if t contains non-'a' characters
    
    for (int i = 0; i < q; i++) {
      cin >> n >> val >> str; // n is operation type (1 or 2), val is number of times to append, str is the string to append
      
      for (char c : str) {
        if (n == 1) { // operation on s
          if (c != 'a')
            a = 1; // mark that s contains a non-'a' character
          len1 += val;
        } else { // operation on t
          if (c != 'a')
            b = 1; // mark that t contains a non-'a' character
          len2 += val;
        }
      }
      
      // If t contains a non-'a' character, we can rearrange s and t so s < t
      if (b)
        cout << "YES" << "\n";
      // If t is all 'a's, but s is shorter than t, we can make s lexicographically smaller
      else if (!a && len1 < len2)
        cout << "YES" << "\n";
      // Otherwise, it's impossible
      else
        cout << "NO" << "\n";
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/