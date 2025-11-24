// Problem: CF 1850 F - We Were Both Children
// https://codeforces.com/contest/1850/problem/F

/*
F. We Were Both Children
Algorithm: Frequency counting with sieve-like approach
Time Complexity: O(n log n) per test case
Space Complexity: O(n)

Mihai and Slavic were looking at a group of n frogs, numbered from 1 to n,
all initially located at point 0. Frog i has a hop length of a_i.
Each second, frog i hops a_i units forward. Before any frogs start hopping,
Slavic and Mihai can place exactly one trap in a coordinate in order to catch
all frogs that will ever pass through the corresponding coordinate.

The task is to find the maximum number of frogs that can be caught by placing
a single trap at some point between 1 and n.
This is solved by:
- For each frog with hop length a_i, we increment the count for all multiples of a_i
  (since a frog with hop length a_i will pass through points a_i, 2*a_i, 3*a_i, ...)
- We use a map to store the frequency of hop lengths, then for each unique hop length,
  we go through its multiples and increment their counters in an array v.
- The answer is the maximum value in that array.
*/

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> m; // Store frequency of each hop length
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++m[x]; // Count occurrences of each hop length
    }
    std::vector<long> v(n + 1, 0); // v[i] stores how many frogs pass through position i
    long mx(0); // Track maximum number of frogs passing through any point
    
    for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
      long key = it->first;   // Current hop length
      long val = it->second;  // Number of frogs with this hop length
      
      // For each multiple of the current hop length (up to n)
      for (long p = 1; p * key <= n; p++) {
        v[p * key] += val;    // Add count of frogs that pass through this point
        mx = (mx > v[p * key] ? mx : v[p * key]); // Update max
      }
    }
    
    printf("%ld\n", mx); // Output the maximum number of frogs caught
  }
}


// https://github.com/VaHiX/codeForces/