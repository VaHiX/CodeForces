// Problem: CF 1328 B - K-th Beautiful String
// https://codeforces.com/contest/1328/problem/B

/*
B. K-th Beautiful String
Purpose: Given n and k, return the k-th lexicographically smallest string of length n with exactly two 'b's and (n-2) 'a's.
Algorithm:
  - For each test case, we construct the k-th such string by:
    1. Initializing a string of n 'a's.
    2. Finding where to place the first 'b' by subtracting triangular numbers from k until k becomes less than or equal to the current position.
    3. Placing the second 'b' at the appropriate offset.
Time Complexity: O(n) per test case in worst case (due to string initialization), but overall efficient due to precomputed logic.
Space Complexity: O(n) for storing the result string.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s(n, 'a'); // Initialize string with all 'a's
    long pos(0);          // Position tracking for triangular number subtraction
    while (pos < k) {
      k -= pos;           // Subtract current position from k to simulate decrementing triangular numbers
      ++pos;              // Increment position
    }
    s[(n - 1) - pos] = 'b';             // Place first 'b' at calculated position
    s[(n - 1) - (k - 1)] = 'b';         // Place second 'b' accordingly
    std::cout << s << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/