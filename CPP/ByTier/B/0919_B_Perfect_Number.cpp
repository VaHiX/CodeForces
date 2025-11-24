// Problem: CF 919 B - Perfect Number
// https://codeforces.com/contest/919/problem/B

/*
 * Problem: Find the k-th smallest positive integer whose digits sum to 10
 * Algorithm: Brute force enumeration
 * Time Complexity: O(k * log(max_number)) where max_number is approximately 10^10
 * Space Complexity: O(1)
 * 
 * The approach is to:
 * 1. Iterate through numbers starting from 1
 * 2. For each number, check if sum of its digits equals 10
 * 3. Keep count of such "perfect" numbers
 * 4. When count reaches k, output that number
 * 
 * The isPerfect function calculates digit sum by repeatedly taking modulo 10 and dividing by 10
 * The main loop goes up to 10^9 which is sufficient for the given constraints
 */

#include <cstdio>
bool isPerfect(long x) {
  int s(0);  // Initialize sum of digits
  while (x > 0) {
    s += (x % 10);  // Add last digit to sum
    x /= 10;  // Remove last digit
  }
  return (s == 10);  // Return true if sum equals 10
}
int main() {
  long k;
  scanf("%ld", &k);
  long cnt(0);  // Counter for perfect numbers found
  for (long p = 1; p < 1e9; p++) {  // Iterate through numbers
    if (!isPerfect(p)) {  // Skip if not perfect
      continue;
    }
    ++cnt;  // Increment counter
    if (cnt == k) {  // If we found the k-th one
      printf("%ld\n", p);
      break;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/