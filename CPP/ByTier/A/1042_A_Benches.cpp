// Problem: CF 1042 A - Benches
// https://codeforces.com/contest/1042/problem/A

/*
 * Problem: A. Benches
 * Purpose: Given n benches with initial occupancy counts and m additional people,
 *          calculate the minimum and maximum possible maximum occupancy after
 *          distributing the m newcomers among the benches optimally.
 *
 * Algorithms/Techniques:
 *  - Greedy approach for both min and max cases
 *  - Using multiset to efficiently manage and update bench occupancies
 *
 * Time Complexity: O(n * log n + m * log n)
 * Space Complexity: O(n)
 */

#include <cstdio>
#include <set>
#include <iterator>

int main() {
  long n;
  scanf("%ld", &n);
  long m;
  scanf("%ld", &m);
  std::multiset<long> s;  // Store current bench occupancies
  long mx(0);             // Track maximum initial occupancy
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    s.insert(x);         // Insert current occupancy into multiset
    mx = (mx > x) ? mx : x;  // Update max initial occupancy
  }
  
  // Minimize the maximum: always add to the bench with least occupancy
  for (long p = 0; p < m; p++) {
    long b = (*s.begin()) + 1;  // Get smallest current occupancy and increase it
    s.erase(s.begin());        // Remove the smallest element
    s.insert(b);               // Insert updated value back into multiset
  }
  
  // For maximum: add all newcomers to one bench (greedy maximize)
  printf("%ld %ld\n", *s.rbegin(), mx + m);  // rbegin() gives max, mx + m is max if all go to one bench
  return 0;
}


// https://github.com/VaHiX/codeForces/