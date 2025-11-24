// Problem: CF 649 A - Любимые числа Поликарпа
// https://codeforces.com/contest/649/problem/A

/*
 * Task: Find the maximum power of 2 that divides at least one number in the sequence,
 *       and count how many numbers are divisible by this power.
 *
 * Algorithm:
 *   - For each number in the input:
 *       - Determine the highest power of 2 that divides it by repeatedly
 *         checking divisibility by 2^k (starting from 2^1).
 *       - Keep track of the maximum such power encountered (mxd).
 *       - Count how many numbers are divisible by this maximum power.
 *
 * Time Complexity: O(n * log(max(a_i))) where n is the number of elements and max(a_i) is the largest number.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long mxd(1), cnt(0);  // mxd: max power of 2 found so far, cnt: count of numbers divisible by mxd
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    long div(1);  // div will hold the highest power of 2 dividing x
    while (x % (2 * div) == 0) {  // while x is divisible by 2 * div
      div *= 2;  // increase power of 2
    }
    if (div > mxd) {  // if current div is greater than max seen so far
      mxd = div;  // update max
      cnt = 1;  // reset count
    } else if (div == mxd) {  // if current div equals max seen so far
      ++cnt;  // increment count
    }
  }
  printf("%ld %ld\n", mxd, cnt);  // output result
  return 0;
}


// https://github.com/VaHiX/CodeForces/