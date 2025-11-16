// Problem: CF 1605 B - Reverse Sort
// https://codeforces.com/contest/1605/problem/B

/*
Purpose: 
This code solves the problem of sorting a binary string using a specific operation: 
choosing a subsequence in non-increasing order and reversing it in-place.
The algorithm identifies segments of the string that are out of order and performs 
a minimal number of operations to sort the string.

Algorithms/Techniques:
- Two-pointer technique to identify unsorted regions
- Greedy approach to determine which indices to reverse
- Sorting the indices of operations for final output

Time Complexity: O(n^2) in worst case due to multiple passes and sorting operations
Space Complexity: O(n) for storing indices of operations

*/
#include <algorithm>
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
    long left(0);
    // Move left pointer to the first '1'
    while (left < s.size() && s[left] == '0') {
      ++left;
    }
    long right(s.size() - 1);
    // Move right pointer to the first '0' from the end
    while (right >= 0 && s[right] == '1') {
      --right;
    }
    std::vector<long> v;
    // While there are mismatches between left and right pointers
    while (left < right) {
      // Add indices to the vector for operation
      v.push_back(left);
      ++left;
      v.push_back(right);
      --right;
      // Skip over all '0's from the left
      while (left < s.size() && s[left] == '0') {
        ++left;
      }
      // Skip over all '1's from the right
      while (right >= 0 && s[right] == '1') {
        --right;
      }
    }
    // If operations were needed, sort them
    if (v.size() > 0) {
      sort(v.begin(), v.end());
      std::cout << "1\n" << v.size();
      for (long p = 0; p < v.size(); p++) {
        std::cout << " " << (1 + v[p]); // Convert to 1-based indexing
      }
      std::cout << std::endl;
    } else {
      std::cout << "0" << std::endl; // No operations needed
    }
  }
}


// https://github.com/VaHiX/CodeForces/