// Problem: CF 1925 A - We Got Everything Covered!
// https://codeforces.com/contest/1925/problem/A

/*
Purpose: This code generates the shortest string such that all possible strings of length n formed using the first k lowercase English letters appear as subsequences.

Algorithm/Techniques:
- The approach uses a cyclic pattern of the first k letters to ensure all combinations are covered.
- For each test case, we repeat the first k letters exactly n times in sequence to form the result string.
- This guarantees that every combination of n characters from the first k letters appears as a subsequence.

Time Complexity: O(n * k) per test case, where n is the length of strings and k is the number of letters used.
Space Complexity: O(k) for storing the string of first k letters.

*/
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  std::string ab = "abcdefghijklmnopqrstuvwxyz";
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    for (long p = 0; p < n; p++) {
      std::cout << ab.substr(0, k); // Output the first k letters repeatedly to cover all combinations
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/