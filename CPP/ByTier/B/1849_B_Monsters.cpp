// Problem: CF 1849 B - Monsters
// https://codeforces.com/contest/1849/problem/B

/*
B. Monsters

Algorithm: Simulation with sorting by health modulo k
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the pairs

This code simulates a game where monsters are killed in order based on their health values.
Each turn, the monster with the highest health (and smallest index if tied) is damaged by k.
The health of each monster is stored as (health % k, index) to determine who gets hit next.
A custom comparator pairCompare ensures correct ordering for killing priority.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

bool pairCompare(std::pair<long, long> a, std::pair<long, long> b) {
  if (a.first == b.first) {
    return a.second < b.second; // If health mod k is same, smaller index comes first
  } else if (a.first == 0) {
    return true; // If a has no remainder, it should be killed next (health % k = 0)
  } else if (b.first == 0) {
    return false; // If b has no remainder, it should be killed next
  } else
    return a.first > b.first; // Otherwise, higher remainder (health % k) means higher priority
  return true;
}

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<std::pair<long, long>> a(n); // Store (health % k, index)
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      a[p] = std::make_pair(x % k, p + 1); // Store health mod k and original index
    }
    sort(a.begin(), a.end(), pairCompare); // Sort based on custom comparator to determine kill order
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p].second); // Print the indices in order they die
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/