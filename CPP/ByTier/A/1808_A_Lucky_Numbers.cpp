// Problem: CF 1808 A - Lucky Numbers
// https://codeforces.com/contest/1808/problem/A

/*
 ==========================================================
 * Problem: A. Lucky Numbers
 * Purpose: Find the number in the range [l, r] with the maximum "luckiness", 
 *          where luckiness is defined as the difference between the largest 
 *          and smallest digits of the number.
 * 
 * Algorithm:
 *   - For each test case, iterate through numbers from l to r, but limit the 
 *     iteration to at most 200 numbers beyond l to optimize performance.
 *   - For each number, compute its luckiness using a helper function 'check'.
 *   - Track the maximum luckiness and the corresponding number.
 *   - Output the number with the maximum luckiness.
 * 
 * Time Complexity: O(t * min(r - l + 1, 200)) = O(t * 200) = O(t)
 * Space Complexity: O(1)
 ==========================================================
 */
#include <cstdio>
int check(long x) {
  int mn(9), mx(0);
  while (x) {
    int d = x % 10;           // Extract the last digit
    x /= 10;                  // Remove the last digit
    mn = (mn < d) ? mn : d;   // Update minimum digit
    mx = (mx > d) ? mx : d;   // Update maximum digit
  }
  return (mx - mn);           // Return the difference (lucky number)
}
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long left, right;
    scanf("%ld %ld", &left, &right);
    long res(left), val(0);
    // Iterate up to 200 numbers after 'left' to find the luckiest number
    for (long p = left; p <= right && p <= left + 200; p++) {
      int tst = check(p);
      if (tst > val) {
        val = tst;      // Update maximum luckiness
        res = p;        // Update the number with maximum luckiness
      }
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/CodeForces/