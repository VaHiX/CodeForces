// Problem: CF 932 C - Permutation Cycle
// https://codeforces.com/contest/932/problem/C

/*
Algorithm/Techniques: 
This solution constructs a permutation by grouping numbers into cycles of length A and B. 
It first determines how many cycles of each type can fit into N by checking all possible splits of N into parts divisible by A and B. 
Once the number of cycles is determined, it builds the permutation by placing elements in cycles of size A and B, ensuring g(i) equals either A or B as required.

Time Complexity: O(N / A + N / B), which is efficient enough for N up to 10^6.
Space Complexity: O(1), as no extra space is used apart from a few variables.
*/

#include <cstdio>

int main() {
  long n, a, b;
  scanf("%ld %ld %ld", &n, &a, &b);
  long x(-1), y(-1);  // x = number of cycles of length a, y = number of cycles of length b
  for (long p = 0; p <= n; p += a) {
    if ((n - p) % b == 0) {
      x = p / a;
      y = (n - p) / b;
      break;
    }
  }
  if (x < 0 || y < 0) {
    puts("-1");
    return 0;
  }
  long cur(1);
  while (x--) {
    for (long p = 1; p <= a; p++) {
      printf("%ld ", cur + (p % a));  // Generate a cycle of length a
    }
    cur += a;
  }
  while (y--) {
    for (long p = 1; p <= b; p++) {
      printf("%ld ", cur + (p % b));  // Generate a cycle of length b
    }
    cur += b;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/