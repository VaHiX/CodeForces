// Problem: CF 2035 B - Everyone Loves Tres
// https://codeforces.com/contest/2035/problem/B

/*
B. Everyone Loves Tres
Problem: Find the smallest integer of length n consisting only of digits 3 and 6 that is divisible by both 33 and 66.
If no such integer exists, return -1.

Algorithms/Techniques: 
- Mathematical divisibility checking (33 = 3 * 11, 66 = 2 * 3 * 11)
- Greedy construction of result string
- Precomputed patterns based on parity of n

Time Complexity: O(n) per test case - string construction takes linear time
Space Complexity: O(n) - for storing the result string

Approach:
- A number made of only '3' and '6' is divisible by 33 if it's divisible by both 3 and 11.
- It's divisible by 66 if it's divisible by both 2, 3, and 11.
- Since 66 = 2 × 3 × 11, the number must:
    1. Be even (ends in 6)
    2. Have digit sum divisible by 3
    3. Satisfy divisibility rule for 11

Key observations:
- All '3's and '6's can be arranged to produce valid numbers for some n.
- For cases n=1, n=3: No solution exists.
- If n is odd and >3, use (n-5) '3's followed by "36366"
- If n is even and >2, use (n-2) '3's followed by "66"

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
    std::string res("-1"); // Default result is -1

    if (n == 1 || n == 3) {
      // For n=1 or n=3, no valid number can be formed
      res = "-1";
    } else if (n % 2) {
      // If n is odd and > 3
      // Construct result as (n-5) '3's + "36366"
      res = std::string(n - 5, '3') + "36366";
    } else {
      // If n is even and > 2
      // Construct result as (n-2) '3's + "66"
      res = std::string(n - 2, '3') + "66";
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/