// Problem: CF 1889 A - Qingshan Loves Strings 2
// https://codeforces.com/contest/1889/problem/A

/*
 * Problem: Qingshan Loves Strings 2
 * 
 * Purpose:
 *   Given a binary string s of length n, determine if it's possible to make the string "good"
 *   by inserting "01" at most 300 times. A string is good if for all i, s[i] != s[n - i + 1].
 *
 * Algorithms/Techniques:
 *   - Greedy approach with insertion
 *   - String manipulation using insert and count
 *   - Symmetric pair checking
 * 
 * Time Complexity: O(n^2) in worst case due to string insertions and scanning
 * Space Complexity: O(n) for storing the string and operations
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;
int T_T, n, i;
string s;
vector<int> op;

int main() {
  for (cin >> T_T; T_T--;) {
    cin >> n >> s;
    op.clear();
    
    // If length is odd or number of 0s and 1s are unequal, impossible to make good
    if ((n & 1) || count(begin(s), end(s), '0') != n / 2) {
      puts("-1");
      continue;
    }
    
    // Iterate through first half of the string
    for (i = 0; i < n / 2; ++i)
      if (s[i] == s[n - i - 1]) // If symmetric positions are equal
        if (s[i] == '0') {
          // Insert "01" at the end of the string to make it different from matching character
          op.push_back(n - i);  
          s.insert(begin(s) + n - i, {'0', '1'}), n += 2;
        } else {
          // Insert "01" at beginning to avoid conflict with symmetric position
          op.push_back(i);
          s.insert(begin(s) + i, {'0', '1'});
          n += 2;
        }
    
    cout << op.size() << endl;
    for (int x : op)
      printf("%d ", x);
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/