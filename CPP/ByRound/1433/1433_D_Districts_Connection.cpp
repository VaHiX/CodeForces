// Problem: CF 1433 D - Districts Connection
// https://codeforces.com/contest/1433/problem/D

/*
 * Problem: Districts Connection
 * 
 * Algorithm:
 * - The problem is to connect all districts with n-1 edges such that:
 *   1. All districts are connected in a single component (tree).
 *   2. No two districts connected directly belong to the same gang.
 * 
 * Approach:
 * - Group districts by gang.
 * - If all districts belong to the same gang, it's impossible (NO).
 * - Otherwise, we can build a star graph:
 *   - Connect all districts from the first gang to one district of another gang.
 *   - Then connect remaining districts in the first gang to the same district of the second gang.
 *   - This ensures no two connected districts belong to the same gang.
 * 
 * Time Complexity: O(n), where n is the number of districts.
 * Space Complexity: O(n), for storing the gangs and groups.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 1);  // Stores gang of each district (1-indexed)
    bool possible(false);        // Flag to check if any district belongs to a different gang
    std::vector<long> first, second;  // first: districts of the same gang as district 1, second: others
    
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]);
      if (a[p] != a[1]) {
        second.push_back(p);   // Add district to second group if it's from a different gang
        possible = true;       // Mark that at least one district is from a different gang
      } else {
        first.push_back(p);    // Add district to first group if it's from the same gang
      }
    }
    
    if (!possible) {
      puts("NO");  // If all districts are from the same gang, impossible to connect
      continue;
    }
    
    puts("YES");
    long x(a[1]), cnt(0);  // x is the gang of district 1, cnt counts edges added
    
    // Connect all districts in 'second' group to district 1 (which is from the first gang)
    for (long p = 0; p < second.size() && cnt + 1 < n; p++, cnt++) {
      printf("1 %ld\n", second[p]);
    }
    
    // Connect districts in 'first' group (except the first one) to the first district of 'second' group
    for (long p = 1; p < first.size() && cnt + 1 < n; p++, cnt++) {
      printf("%ld %ld\n", first[p], second[0]);
    }
    
    // Connect remaining districts of 'first' to the rest of 'second' in a chain
    for (long p = 1; p < first.size() && cnt + 1 < n; p++, cnt++) {
      for (long q = 1; q < second.size() && cnt + 1 < n; q++, cnt++) {
        printf("%ld %ld\n", first[p], second[q]);
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/