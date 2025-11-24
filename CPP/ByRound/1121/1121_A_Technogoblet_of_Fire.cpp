// Problem: CF 1121 A - Technogoblet of Fire
// https://codeforces.com/contest/1121/problem/A

/*
 * Problem: Technogoblet of Fire
 * 
 * Purpose: Determine the minimal number of new school names needed so that
 * exactly k Chosen Ones are selected by the Technogoblet of Fire.
 * 
 * Algorithm:
 * 1. For each school, determine the maximum power among its students (best[s]).
 * 2. For each Chosen One, check if their power is less than the best in their school.
 *    If so, they won't be selected without a new school name.
 * 3. Count how many such Chosen Ones need new schools assigned.
 * 
 * Time Complexity: O(n + m + k)
 * Space Complexity: O(n + m)
 * 
 * Techniques:
 * - Preprocessing: Find maximum power per school
 * - Greedy checking: For each Chosen One, decide if they need a new school
 */

#include <cstdio>
#include <vector>
int main() {
  long n, m, k;
  scanf("%ld %ld %ld", &n, &m, &k);
  std::vector<long> pow(n + 1), sc(n + 1), best(m + 1, 0); // pow: power of each student, sc: school of each student, best: maximum power per school
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &pow[p]);
  }
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &sc[p]);
    best[sc[p]] = (best[sc[p]] > pow[p]) ? best[sc[p]] : pow[p]; // Update max power for school sc[p]
  }
  long cnt(0);
  for (long p = 0; p < k; p++) {
    long x;
    scanf("%ld", &x);
    cnt += (pow[x] < best[sc[x]]); // If current student's power is less than best in their school, they need a new school
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/