// Problem: CF 1743 C - Save the Magazines
// https://codeforces.com/contest/1743/problem/C

/*
 * Problem: Save the Magazines
 * 
 * Purpose: Given n boxes of magazines, each with a lid (1) or not (0), 
 *          determine the maximum number of magazines that can be saved 
 *          by moving lids such that each lid can only be moved once and 
 *          can move left to adjacent boxes.
 *          
 * Algorithm: Greedy approach. For each transition from '0' to '1', 
 *            we consider whether we should move the lid from the '1' 
 *            box to the previous '0' box to optimize total saved magazines.
 *            
 * Time Complexity: O(n) per test case, where n is the number of boxes
 * Space Complexity: O(n) for storing the string and the array a
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    s += '0'; // Add a sentinel '0' at the end to simplify boundary checks
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      std::cin >> a[p];
    }
    a.push_back(0); // Add a sentinel 0 to align indexing with s
    long prev(-1), idx(-1);
    for (long p = 1; p <= n; p++) {
      if (s[p - 1] == '0' && s[p] == '1') {
        // Found a transition from uncovered to covered box.
        // Store the current value and index for possible future movement.
        prev = a[p - 1];
        idx = p - 1;
      } else if (idx >= 0 && s[p - 1] == '1') {
        // If we had previously seen a transition, and now we are in a covered box,
        // try to move the lid left (if beneficial).
        if (a[p - 1] < prev) {
          s[idx] = '1';     // Move the lid from idx to p-1
          idx = p - 1;      // Update index to new lid position
          s[p - 1] = '0';   // Mark previous box as uncovered
          prev = a[p - 1];  // Update value for comparison
        }
        if (s[p] == '0') {
          // If the next box is uncovered, no more movement possible from current idx.
          prev = idx = -1;
        }
      }
    }
    long cnt(0);
    for (long p = 0; p < n; p++) {
      // Count total magazines in boxes with lids ('1')
      cnt += (s[p] == '1') * a[p];
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/