// Problem: CF 639 A - Bear and Displayed Friends
// https://codeforces.com/contest/639/problem/A

#include <cstdio>
#include <set>
#include <vector>
/*
 * Problem: Bear and Displayed Friends
 * 
 * Purpose:
 *   This program simulates a social network system where a bear (Limak) manages
 *   his online friends. The system displays at most k friends at a time based on
 *   their 'relation values' (t[i]). When a friend comes online, they are added to
 *   the set of online friends. If the number of online friends exceeds k, only the
 *   top k (by relation value) are displayed.
 * 
 * Algorithm:
 *   - Use a std::set to maintain online friends, sorted by their relation value.
 *   - On adding a friend (type 1):
 *     - Insert into the set.
 *     - If size exceeds k, remove the friend with the smallest relation value.
 *   - On querying (type 2):
 *     - Check if the friend exists in the display set.
 * 
 * Time Complexity:
 *   - Each insertion and deletion in the set is O(log n).
 *   - For each query of type 1, at most one removal: O(log n) per query.
 *   - For each query of type 2, O(1) lookup.
 *   - Total per query: O(log n).
 *   - For q queries: O(q * log n).
 * 
 * Space Complexity:
 *   - Storage for relation values: O(n).
 *   - Storage for online friends in the set: O(k).
 *   - Total: O(n + k).
 */
int main() {
  long n, k, q;
  scanf("%ld %ld %ld\n", &n, &k, &q);
  std::vector<long> t(n + 1);
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &t[p]);
  }
  std::set<long> disp;  // Set to keep track of online friends, sorted by t[i]
  while (q--) {
    long x, y;
    scanf("%ld %ld\n", &x, &y);
    if (x == 1) {
      // Friend y becomes online
      disp.insert(y);
      if (disp.size() > k) {
        // If more than k friends online, remove the one with smallest t[i]
        long currentMin(1000000000);  // Initialize with large value
        long oust(-1);                // Friend to be removed
        for (std::set<long>::iterator setIt = disp.begin(); setIt != disp.end();
             setIt++) {
          if (t[*setIt] < currentMin) {
            currentMin = t[*setIt];
            oust = *setIt;
          }
        }
        disp.erase(oust);
      }
    } else if (x == 2) {
      // Check if friend y is displayed
      puts((disp.count(y) > 0) ? "YES" : "NO");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/