// Problem: CF 1552 A - Subsequence Permutation
// https://codeforces.com/contest/1552/problem/A

/*
Purpose: This code solves the problem of finding the minimum number of characters to permute in a string 
         such that the resulting string is sorted alphabetically. The solution works by comparing 
         the original string with its sorted version and counting the mismatches. The number of mismatches 
         directly corresponds to the minimum k required.

Algorithms/Techniques: 
- Sorting
- Character comparison
- Greedy approach (minimum k equals number of mismatched characters)

Time Complexity: O(n * log(n)) per test case due to sorting operation, where n is string length.
Space Complexity: O(n) for storing the sorted version of the string.

Input Format:
- First line contains number of test cases t
- For each test case:
  - First line contains integer n (length of string)
  - Second line contains string s of lowercase letters

Output Format:
- For each test case, output the minimum k required to sort the string alphabetically
*/

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::string t = s;
    sort(t.begin(), t.end()); // Sort the string to get target configuration
    long cnt(0);
    for (long p = 0; p < t.size(); p++) {
      cnt += (s[p] != t[p]); // Count mismatches between original and sorted strings
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/