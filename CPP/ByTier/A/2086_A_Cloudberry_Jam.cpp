// Problem: CF 2086 A - Cloudberry Jam
// https://codeforces.com/contest/2086/problem/A

/*
 * Problem: A. Cloudberry Jam
 * Purpose: Calculate the amount of cloudberries needed to prepare n jars of jam.
 *
 * Algorithm:
 * - Each jar requires 3 kg of jam.
 * - Jam is made from equal amounts of berries and sugar.
 * - During cooking, 25% of the total mass evaporates → only 75% remains.
 * - So if we use x kg of berries and x kg of sugar (total 2x kg), 
 *   we get (2x * 3/4) = 3x/2 kg of jam.
 * - To get n jars (i.e. 3n kg of jam):
 *   3x/2 = 3n → x = 2n
 * - Therefore, we need 2*n kg of berries.
 *
 * Time Complexity: O(1) per test case.
 * Space Complexity: O(1).
 */

#include <cstdio>
int main() {
  long t;                        // Read number of test cases
  scanf("%ld", &t);
  while (t--) {                  // Process each test case
    long n;
    scanf("%ld", &n);            // Read number of jars
    printf("%ld\n", 2 * n);      // Output required berries (2 * n)
  }
}


// https://github.com/VaHiX/codeForces/