// Problem: CF 1992 E - Novice's Mistake
// https://codeforces.com/contest/1992/problem/E

/*
 * Problem: E. Novice's Mistake
 *
 * Purpose:
 *   This program finds all valid (a, b) pairs for a given integer n such that 
 *   K1o0n's incorrect solution to the apple problem gives the correct answer.
 *   
 *   In K1o0n's version:
 *     - The value of 'n' is treated as a string, and multiplied by 'a' by 
 *       concatenating it 'a' times to form a new string s.
 *     - Then, 'b' characters are removed from the end of this string s.
 *     - If b >= len(s), the result becomes empty.
 *   
 *   The correct value should be n*a - b. So we seek (a, b) pairs where:
 *     - The integer value of the modified string equals n*a - b.
 *
 * Algorithms/Techniques:
 *   Brute-force search for valid pairs (a, b).
 *   For a given 'n', iterate over possible values of 'a' from 1 to 10000,
 *   and for each 'a', iterate over possible 'b' values within reasonable limits.
 *   For each pair (a, b),:
 *     - Construct string s = n repeated a times.
 *     - Remove last b characters to get new string.
 *     - Convert the resulting string back to integer.
 *     - Check if it equals the correct value n*a - b.
 *
 * Time Complexity: O(10^7) in worst case per test case (due to nested loops).
 * Space Complexity: O(k), where k is number of valid pairs, at most 1e5.
 */

#include <cstdio>
#include <string>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::pair<long, long>> v; // Store valid (a, b) pairs
    std::string s(std::to_string(n)); // Convert n to string for easy concatenation
    
    for (long a = 1; a <= 10000; a++) {
      long start = a * s.size() - 10; // Lower bound for b
      start = (start > 1 ? start : 1); // Ensure non-negative start
      
      for (int b = start; b < s.size() * a; b++) {
        long x(n * a - b), y(0); // x is expected value, y is computed from string
        
        // Build the number represented by s repeated 'a' times, with 'b' chars removed
        for (long p = 0; p < s.size() * a - b; p++) {
          y *= 10;
          y += (s[p % s.size()] - '0'); // Take digit from repeated string s
        }
        
        if (x == y) { // If computed value matches expected value
          v.push_back({a, b});
        }
      }
    }
    
    printf("%ld\n", v.size()); // Number of valid pairs found
    
    for (std::pair<long, long> x : v) {
      printf("%ld %ld\n", x.first, x.second); // Output each valid pair
    }
  }
}


// https://github.com/VaHiX/codeForces/