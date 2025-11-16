// Problem: CF 1011 B - Planning The Expedition
// https://codeforces.com/contest/1011/problem/B

/*
B. Planning The Expedition
Algorithm: Binary search on answer + greedy verification
Time Complexity: O(m * log(m/n)) where m is the number of food packages and n is the number of participants
Space Complexity: O(W) where W = 101 is the maximum food type value

The problem asks for the maximum number of days an expedition can last given that:
- Each participant must eat exactly one food package per day
- All participants must eat the same food type during the entire expedition
- We have m daily food packages of various types

Approach:
1. Count frequency of each food type
2. Binary search on the number of days (d)
3. For a given d, check if it's possible to distribute food for d days
   - For each food type, we need at least n/d participants to consume it
   - This means the count of that food type should be >= d * (number of participants who want this food type)
   - Greedily check how many participants can get food from current food type count

The inner loop checks for all possible numbers of days, and for each day count,
we verify if it's feasible using a greedy approach.

Note: The code uses a simplified verification that loops over all possible
days up to m/n, which is valid since maximum possible days is bounded.
*/

#include <cstdio>
#include <vector>
int main() {
  const long W = 101; // Maximum food type value + 1
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> a(W, 0); // Count of each food type
  for (long p = 0; p < m; p++) {
    long x;
    scanf("%ld", &x);
    ++a[x]; // Increment count for that food type
  }
  long mx(0); // Store maximum valid number of days
  for (long d = 1; d <= m / n; d++) { // Try all possible day counts
    long rem(n); // Number of participants still needing food
    for (long u = 0; u < W; u++) {
      rem -= a[u] / d; // How many participants can be satisfied with this food type for d days
    }
    if (rem <= 0) { // All participants can be fed for 'd' days
      mx = d; // Update maximum valid day count
    }
  }
  printf("%ld\n", mx);
  return 0;
}


// https://github.com/VaHiX/codeForces/