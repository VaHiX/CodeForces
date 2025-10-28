// Problem: CF 1697 A - Parkway Walk
// https://codeforces.com/contest/1697/problem/A

/*
 * Problem: Parkway Walk
 * 
 * Description:
 * You are walking through a parkway with n+1 benches numbered from 1 to n+1.
 * The distance between bench i and i+1 is a_i meters.
 * Initially, you have m units of energy. To walk 1 meter, you spend 1 unit of energy.
 * You can only restore energy by sitting on benches (and this is the only way).
 * Your task is to find the minimum amount of energy you need to restore to reach bench n+1.
 *
 * Algorithm:
 * 1. For each test case:
 *    a. Read n (number of intervals) and m (initial energy)
 *    b. Read distances a_i between consecutive benches
 *    c. Compute total distance = sum(a_i)
 *    d. If total distance <= initial energy, no need to restore -> return 0
 *    e. Otherwise, the energy needed to restore is (total distance - m)
 *
 * Time Complexity: O(n) per test case, where n is the number of intervals.
 * Space Complexity: O(1), only constant extra space used.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long s(0); // s stores the total distance to be covered
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      s += a; // accumulate total distance
    }
    long res = (s > m) ? (s - m) : 0; // if total distance exceeds energy, restore the difference
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/