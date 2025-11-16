// Problem: CF 1608 A - Find Array
// https://codeforces.com/contest/1608/problem/A

/* 
 * Problem: Find Array
 * 
 * Algorithm/Technique: Simple Construction
 * 
 * Time Complexity: O(n) per test case, where n is the input number.
 * Space Complexity: O(1) extra space (not counting the output storage).
 * 
 * Approach: For each test case, we simply print consecutive integers starting from 2 up to n+1.
 * This ensures:
 * 1. All numbers are within [1, 10^9]
 * 2. The sequence is strictly increasing
 * 3. No element is divisible by the previous one (since we're printing consecutive integers,
 *    and consecutive integers are coprime, so the smaller never divides the larger)
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 2; p <= n + 1; p++) {
      printf("%ld ", p); // Print consecutive integers from 2 to n+1
    }
    puts(""); // Print newline after each test case
  }
}

// https://github.com/VaHiX/CodeForces/