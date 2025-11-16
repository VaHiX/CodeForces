// Problem: CF 682 A - Alyona and Numbers
// https://codeforces.com/contest/682/problem/A

/*
 * Problem: Alyona and Numbers
 * Algorithm: Mathematical counting using modular arithmetic
 * Time Complexity: O(1) - constant time due to fixed size arrays and operations
 * Space Complexity: O(1) - fixed size vectors of size 5, regardless of input size
 *
 * The solution uses the fact that for x + y to be divisible by 5,
 * the remainder of x when divided by 5 must be the opposite of the
 * remainder of y when divided by 5. We count how many numbers in [1,n]
 * and [1,m] have each possible remainder (0 to 4), then compute valid pairs.
 */

#include <cstdio>
#include <vector>
const int D = 5;
int main() {
  long n, m;
  scanf("%ld %ld\n", &n, &m);
  std::vector<long long> a(D); // a[i] = count of numbers in [1,n] with remainder i when divided by D
  std::vector<long long> b(D); // b[i] = count of numbers in [1,m] with remainder i when divided by D
  a[0] = n / D; // numbers from 1 to n that are divisible by D (remainder 0)
  b[0] = m / D; // same for m
  for (int p = 1; p < D; p++) {
    // For remainders 1 to D-1, add one more if the modulo is >= p
    a[p] = (n / D) + (n % D >= p);
    b[p] = (m / D) + (m % D >= p);
  }
  long long res(0);
  // For each remainder r1 from [1,n], find how many from [1,m] have remainder (D - r1) % D
  // so that their sum mod D is 0
  for (int p = 0; p < D; p++) {
    res += a[p] * b[(D - p) % D];
  }
  printf("%lld\n", res);
  return 0;
}


// https://github.com/VaHiX/CodeForces/