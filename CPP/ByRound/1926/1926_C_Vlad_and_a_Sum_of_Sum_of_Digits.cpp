// Problem: CF 1926 C - Vlad and a Sum of Sum of Digits
// https://codeforces.com/contest/1926/problem/C

/*
C. Vlad and a Sum of Sum of Digits
Algorithm: Preprocessing with dynamic programming to compute sum of digit sums from 1 to n.
Time Complexity: O(N) preprocessing + O(1) per query, where N = 200007
Space Complexity: O(N) for the vector v

Vladislav wrote the integers from 1 to n, inclusive, on the board. Then he replaced each integer with the sum of its digits.
What is the sum of the numbers on the board now?

For example, if n=12 then initially the numbers on the board are:
1,2,3,4,5,6,7,8,9,10,11,12.
Then after the replacement, the numbers become:
1,2,3,4,5,6,7,8,9,1,2,3.
The sum of these numbers is 1+2+3+4+5+6+7+8+9+1+2+3=51
*/

#include <cstdio>
#include <vector>
long sumdigits(long x) {
  long s(0);
  while (x) {
    s += (x % 10);     // Add last digit to sum
    x /= 10;           // Remove last digit
  }
  return s;
}
int main() {
  const long N = 200007;
  std::vector<long> v(N, 0);  // Precompute prefix sums of digit sums
  for (long p = 1; p < N; p++) {
    v[p] = v[p - 1] + sumdigits(p);  // Build prefix sum array
  }
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld\n", v[n]);  // Output precomputed result
  }
}


// https://github.com/VaHiX/codeForces/