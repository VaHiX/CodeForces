// Problem: CF 1437 B - Reverse Binary Strings
// https://codeforces.com/contest/1437/problem/B

/*
B. Reverse Binary Strings
Algorithm: Greedy approach to count the number of adjacent equal characters.
           The minimum operations needed is (number of adjacent equal pairs + 1) / 2.
Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(1) - only using a few variables for counting.

The idea is to count how many consecutive identical characters exist,
as each such pair can be fixed with one operation. Since we want to make
the string alternating, we greedily aim to minimize operations by fixing
pairs of adjacent same characters.
*/

#include <iostream>
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
    long cnt(0); // Count of adjacent equal characters
    for (long p = 1; p < n; p++) {
      cnt += (s[p - 1] == s[p]); // If current and previous character are same, increment count
    }
    std::cout << ((cnt + 1) / 2) << std::endl; // Minimum operations needed
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/