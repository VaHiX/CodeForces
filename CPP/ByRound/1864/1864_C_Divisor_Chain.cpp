// Problem: CF 1864 C - Divisor Chain
// https://codeforces.com/contest/1864/problem/C

/*
 * Problem: C. Divisor Chain
 * 
 * Algorithm/Technique: Greedy approach with divisor selection and binary splitting.
 * 
 * Time Complexity: O(log x) per test case, as we perform operations proportional to the number of bits in x.
 * Space Complexity: O(log x), due to storing the sequence of operations.
 *
 * The solution works as follows:
 * 1. First, we greedily subtract divisors (starting from 1, then 2, 4, 8, ...) such that 
 *    the current number x is divisible by that divisor and also not divisible by twice that divisor.
 *    This avoids using the same divisor more than twice.
 * 2. Once we can no longer use this method, we divide the number by 2 repeatedly until it reaches 1.
 * This ensures that the number of operations remains within the limit of 1000.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    std::vector<long> res;
    res.push_back(x);
    long w(1);
    while (w < x) {
      if ((x % w == 0) && (x % (2 * w) != 0)) {
        x -= w;
        res.push_back(x);
      }
      w *= 2;
    }
    while (x > 1) {
      res.push_back(x / 2);
      x /= 2;
    }
    printf("%ld\n", res.size());
    for (long p = 0; p < res.size(); p++) {
      printf("%ld ", res[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/