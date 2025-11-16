// Problem: CF 1327 B - Princesses and Princes
// https://codeforces.com/contest/1327/problem/B

/*
 * Code Purpose:
 * This program determines whether adding one more kingdom to one of the princesses' lists
 * can increase the number of marriages in a greedy matching process.
 * 
 * The algorithm simulates the greedy matching:
 * 1. For each princess, try to match her with the lowest numbered kingdom that hasn't been taken yet.
 * 2. If no suitable kingdom exists for a princess, she remains unmarried.
 * 3. After simulating, if any princess is unmarried, we check if we can improve the result
 *    by adding one kingdom to that princess's list.
 * 
 * Time Complexity: O(n^2) in worst case due to nested loops; however, since total entries across all test cases is bounded by 1e5,
 *                  the amortized complexity is acceptable.
 * Space Complexity: O(n) for storing the 'taken' boolean vector.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<bool> taken(n + 1, 0); // Tracks whether a kingdom is already taken
    long x(-1), y(-1); // x will store the index of unmarried princess, y the index of available kingdom
    
    for (long p = 1; p <= n; p++) {
      long m;
      scanf("%ld", &m);
      bool married(false);
      for (long u = 0; u < m; u++) {
        long cand;
        scanf("%ld", &cand);
        // Skip if already taken or if this princess is already married
        if (married || taken[cand]) {
          continue;
        }
        // Mark princess as married and kingdom as taken
        married = true;
        taken[cand] = true;
      }
      // If princess couldn't get married, mark her as unmatched
      if (!married) {
        x = p;
      }
    }
    
    // If all princesses were married optimally
    if (x < 0) {
      puts("OPTIMAL");
    } else {
      // Find the first unused kingdom to add to the unmatched princess's list
      for (long p = 1; p <= n; p++) {
        if (!taken[p]) {
          y = p;
          break;
        }
      }
      printf("IMPROVE\n%ld %ld\n", x, y);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/