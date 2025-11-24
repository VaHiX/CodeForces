// Problem: CF 488 A - Giga Tower
// https://codeforces.com/contest/488/problem/A

/*
 * Problem: Giga Tower
 * Algorithm: Brute Force Search
 * 
 * Purpose: Find the minimum positive integer b such that a + b is a lucky number.
 * A lucky number contains at least one digit '8'.
 * 
 * Time Complexity: O(1000 * log(max_a)) where log(max_a) is the number of digits in a,
 * since we check up to 1000 candidates and each check takes time proportional to the number of digits.
 * 
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

#include <cstdio>
bool isLucky(long x, int d) {
  if (x < 0) {
    x = -x;  // Handle negative numbers by taking absolute value
  }
  while (x > 0) {
    if (x % 10 == d) {
      return true;  // Found the digit '8'
    } else {
      x /= 10;  // Move to the next digit
    }
  }
  return false;  // Digit '8' not found
}
int main() {
  const int L = 8;  // The digit we are looking for
  long a;
  scanf("%ld", &a);
  for (int p = 1; p <= 1000; p++) {
    if (isLucky(a + p, L)) {
      printf("%d\n", p);  // Print the minimum b such that a + b is lucky
      break;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/