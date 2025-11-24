// Problem: CF 1730 A - Planets
// https://codeforces.com/contest/1730/problem/A

#include <cstdio>
#include <map>
#include <utility>

/*
 * Problem: A. Planets
 *
 * Purpose: 
 *   Given n planets on various orbits and two machines with different costs,
 *   determine the minimum cost to destroy all planets.
 *   Machine 1: destroys 1 planet for 1 Triganic Pu.
 *   Machine 2: destroys all planets on one orbit for c Triganic Pus.
 *
 * Algorithms:
 *   - Count frequency of each orbit using a map
 *   - For each orbit, decide whether to use machine 1 (cost = count) or 
 *     machine 2 (cost = c), choosing the cheaper option
 *
 * Time Complexity: O(n log n)
 *   - Building the map takes O(n log n) due to map insertion
 *   - Iterating through map is O(k log n) where k <= n is number of unique orbits
 *   - Overall: O(n log n)
 *
 * Space Complexity: O(n)
 *   - Map stores at most n elements (orbit frequencies); in worst case all distinct orbits
 */
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, c;
    scanf("%ld %ld", &n, &c);
    std::map<long, long> m; // Map to store orbit -> count of planets
    while (n--) {
      long x;
      scanf("%ld", &x);
      ++m[x]; // Increment count for orbit x
    }
    long res(0);
    for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
      long val = it->second; // Get number of planets on current orbit
      // Choose minimum between destroying one by one or using machine 2
      res += (val < c) ? val : c;
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/