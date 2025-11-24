// Problem: CF 1409 D - Decrease the Sum of Digits
// https://codeforces.com/contest/1409/problem/D

/* 
 * Problem: D. Decrease the Sum of Digits
 * Purpose: For a given number n, find the minimum moves to increase n such that the sum of its digits is <= s.
 * Algorithm: Greedily process digits from right to left, rounding up the first digit that causes the sum to exceed s,
 *            and carry over the increment to the next digit. Keep track of how much we need to add to make this adjustment.
 * Time Complexity: O(log n) per test case (since number of digits is log(n))
 * Space Complexity: O(1) additional space (excluding input)
 */

#include <stdio.h>
#include <iostream>
#include <string>

typedef long long ll;
int main() {
  std::ios_base::sync_with_stdio(false);
  long t; // number of test cases
  std::cin >> t;
  while (t--) {
    std::string num; // input number as string
    std::cin >> num;
    long s; // target sum of digits
    std::cin >> s;
    long cs(0); // current sum of digits
    for (long p = 0; p < num.size(); p++) {
      cs += (num[p] - '0'); // accumulate digit sum
    }
    if (cs <= s) {
      puts("0"); // already valid, no moves needed
      continue;
    }
    ll mult(1), cnt(0), carry(0); // mult: place value, cnt: total moves, carry: for propagation
    for (long p = num.size() - 1; p >= 0 && cs >= s; p--) {
      cs -= (num[p] - '0'); // remove current digit from sum
      ll diff = (10 - (num[p] - '0') - carry) % 10; // compute how much to add to make this digit 0 with carry
      cnt += mult * diff; // add contribution to total moves
      if (num[p] > '0') {
        carry = 1; // set carry for next digit
      }
      mult *= 10; // increase place value
    }
    printf("%lld\n", cnt); // output the required number of moves
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/