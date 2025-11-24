// Problem: CF 1566 C - MAX-MEX Cut
// https://codeforces.com/contest/1566/problem/C

/*
C. MAX-MEX Cut
Algorithm: Greedy approach to maximize MEX sum by optimally cutting the bi-table.
Time Complexity: O(n) per test case, where n is the length of the strings.
Space Complexity: O(1) excluding input storage.

The problem involves splitting a binary bi-table into segments such that the sum of MEX values is maximized.
MEX of a bi-table is the smallest digit (0, 1, or 2) not present in the table.
For each pair of characters from the two rows:
- If different, contribute 2 to MEX (since both 0 and 1 are present, MEX = 2).
- If same and both are '1':
    - Check if next pair is '00'. If so, merge these pairs to get MEX = 2.
- If same and both are '0':
    - Check if next pair is '11'. If so, merge these pairs to get MEX = 2.
    - Else, add 1 to MEX (since only one digit is present).
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string a, b;
    std::cin >> a >> b;
    long idx(0), cnt(0);
    while (idx < n) {
      if (a[idx] != b[idx]) {
        // Characters differ: MEX is at least 2
        cnt += 2;
      } else if (a[idx] == '1' && b[idx] == '1') {
        // Both are '1': check if next pair is '00'
        if ((idx + 1 < n) && (a[idx + 1] == '0') && (b[idx + 1] == '0')) {
          cnt += 2;
          ++idx; // Skip next index as it was already considered
        }
      } else if (a[idx] == '0' && b[idx] == '0') {
        // Both are '0': check if next pair is '11'
        if (idx + 1 < n && a[idx + 1] == '1' && b[idx + 1] == '1') {
          cnt += 2;
          ++idx; // Skip next index as it was already considered
        } else {
          // No pair to merge, MEX is 1 (since 0 is present but 1 and 2 are missing)
          ++cnt;
        }
      }
      ++idx;
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/