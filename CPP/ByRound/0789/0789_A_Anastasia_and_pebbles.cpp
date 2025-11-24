// Problem: CF 789 A - Anastasia and pebbles
// https://codeforces.com/contest/789/problem/A

/*
 * Problem: Anastasia and pebbles
 * Purpose: To determine the minimum number of days needed to collect all pebbles
 *          given that Anastasia has two pockets, each can hold at most k pebbles,
 *          and she cannot mix pebble types in a single pocket.
 * 
 * Algorithm:
 *   - For each pebble type, calculate how many trips are needed to collect all
 *     pebbles of that type (ceil(w_i / k)).
 *   - Sum up all trips across all types.
 *   - Since there are two pockets, the total number of days is ceil(total_trips / 2).
 * 
 * Time Complexity: O(n) - single pass through the input
 * Space Complexity: O(1) - only using a few variables
 */

#include <cstdio>
int main() {
  long n, k; // n: number of pebble types, k: capacity of each pocket
  scanf("%ld %ld", &n, &k);
  long total(0); // total number of trips needed to collect all pebbles
  while (n--) {
    long x; // number of pebbles of current type
    scanf("%ld", &x);
    // Calculate trips needed for current type: ceil(x / k)
    total += (x / k) + (x % k > 0);
  }
  // Each day can have at most 2 trips (one per pocket)
  // So minimum days = ceil(total / 2)
  long days = (total / 2) + (total % 2);
  printf("%ld\n", days);
  return 0;
}


// https://github.com/VaHiX/CodeForces/