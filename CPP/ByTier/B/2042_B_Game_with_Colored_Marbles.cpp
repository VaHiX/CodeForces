// Problem: CF 2042 B - Game with Colored Marbles
// https://codeforces.com/contest/2042/problem/B

/*
B. Game with Colored Marbles
Algorithm: Greedy + Map-based Counting
Time Complexity: O(n log n) per test case due to map operations; overall O(sum(n) * log n) for all test cases
Space Complexity: O(n) for storing the counts of each color in the map

The problem involves a game where Alice and Bob take turns removing marbles.
Alice aims to maximize her score, Bob aims to minimize it.
Score calculation:
- 1 point for each color that Alice has at least one marble of
- 1 additional point for each color that Alice has ALL marbles of

Approach:
1. For each test case, count how many marbles exist for each color using a map.
2. Separate colors into two groups:
   - Colors with exactly 1 marble (ones)
   - Colors with more than 1 marble (more)
3. Calculate Alice's optimal score:
   - For colors with 1 marble: Alice can take at most ceil(ones / 2) of them to get points
   - For colors with multiple marbles: Alice gets full points for all such colors
   - Formula: 2 * ((ones + 1) / 2) + more, where we calculate how many single-marble colors Alice can capture.
*/

#include <cstdio>
#include <map>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> m; // Map to store count of each color
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++m[x]; // Increment count for the color x
    }
    long ones(0), more(0); // Count of colors with 1 marble and > 1 marbles
    for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
      long cnt = it->second;
      if (cnt == 1) {
        ++ones; // Color appears only once
      } else {
        ++more; // Color appears multiple times
      }
    }
    // Compute Alice's score optimally:
    // 2 * ((ones + 1) / 2): number of single-colors Alice can grab (each pair contributes 2 to score)
    // more: all multi-colored groups contribute 1 point each for Alice
    printf("%ld\n", 2 * ((ones + 1) / 2) + more);
  }
}


// https://github.com/VaHiX/codeForces/