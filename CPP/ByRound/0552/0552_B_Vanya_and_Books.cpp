// Problem: CF 552 B - Vanya and Books
// https://codeforces.com/contest/552/problem/B

#include <cstdio>
int main() {
  long long n;
  scanf("%lld\n", &n);
  long long d(1), start(1), end(10), total(0);
  // Loop through each digit length group (1-digit, 2-digits, etc.)
  while (start <= n) {
    // If the current range exceeds n, adjust the end to n+1
    if (n < end) {
      end = n + 1;
    }
    // Add the contribution of current digit length group to total digits
    total += d * (end - start);
    // Move to the next digit length group
    start = end;
    end *= 10;
    ++d;
  }
  printf("%lld\n", total);
  return 0;
}
/*
B. Vanya and Books

Purpose: Calculate the total number of digits required to label books from 1 to n.

Algorithm: 
- Iterate through digit lengths (1-digit numbers, 2-digit numbers, etc.)
- For each digit length group, calculate how many numbers exist in that range
- Multiply by the digit length to get contribution to total
- Accumulate the total

Time Complexity: O(log n) - The loop runs for the number of digits in n
Space Complexity: O(1) - Only a constant amount of extra space used
*/

// https://github.com/VaHiX/codeForces/