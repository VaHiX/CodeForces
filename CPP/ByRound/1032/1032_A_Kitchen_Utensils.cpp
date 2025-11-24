// Problem: CF 1032 A - Kitchen Utensils
// https://codeforces.com/contest/1032/problem/A

/*
 * Problem: Kitchen Utensils
 * 
 * Purpose: Given a list of remaining utensil types after a dinner with k guests,
 * determine the minimum number of utensils that could have been stolen.
 * 
 * Algorithm:
 * 1. Count frequency of each utensil type.
 * 2. For each utensil type, calculate the minimum number of sets required
 *    to satisfy the constraint that every guest gets the same number of dishes,
 *    where each dish uses a fixed set of utensils (same set per dish).
 * 3. The total minimum utensils needed is determined by:
 *    For each utensil type with count 'u', we need at least ceil(u/k) sets.
 *    Each set contains k utensils, so if we have ceil(u/k) sets, that means
 *    (ceil(u/k) * k) utensils are needed for this type in the best case.
 * 4. The maximum of all necessary sets across types determines how many complete
 *    dish sets each guest gets.
 * 5. Compute total stolen utensils as the number of missing utensils:
 *    (max_sets * k * different_types) - sum(remaining_utensils)
 *
 * Time Complexity: O(n log n) due to map operations (insertion and iteration)
 * Space Complexity: O(n) for storing counts in the map
 */

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::map<long, long> m;
  for (long p = 0; p < n; p++) {
    ++m[a[p]]; // Count frequency of each utensil type
  }
  long mx(0); // Maximum number of sets needed for any utensil type
  for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
    long u = it->second; // Frequency of current utensil type
    long tmp = k * ((u + k - 1) / k); // Calculate min required sets * k (i.e., total needed for this type)
    mx = (mx > tmp) ? mx : tmp; // Update max sets needed to cover all types
  }
  long stolen(0);
  for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
    stolen += (mx - it->second); // Add difference between required and available
  }
  printf("%ld\n", stolen);
  return 0;
}


// https://github.com/VaHiX/codeForces/