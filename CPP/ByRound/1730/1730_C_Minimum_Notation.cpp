// Problem: CF 1730 C - Minimum Notation
// https://codeforces.com/contest/1730/problem/C

/*
Algorithm: Greedy + Sorting
Time Complexity: O(n log n) per test case, where n is the length of the string.
Space Complexity: O(1) excluding the input string storage.

Approach:
1. We traverse the string from right to left.
2. For each character, we keep track of the minimum digit seen so far (from the right).
3. If the current digit is not '9' and is greater than the minimum digit seen so far, we increment it by 1.
   This simulates the operation of deleting a digit and inserting the minimum of (digit + 1, 9).
4. After processing all digits, we sort the resulting string to get the lexicographically smallest arrangement.

Key steps:
- Traverse string from right to left.
- Update current character if needed based on comparison with min digit seen so far.
- Sort the final string to obtain lexicographically smallest result.
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    char c = '9'; // Initialize minimum digit seen so far from the right
    for (int i = s.size() - 1; i >= 0; i--) {
      c = min(c, s[i]); // Update minimum digit seen from the right
      s[i] += (s[i] != '9' && s[i] > c); // Increment if condition met (simulate operation)
    }
    sort(s.begin(), s.end()); // Sort to get lexicographically smallest string
    cout << s << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/