// Problem: CF 2003 B - Turtle and Piggy Are Playing a Game 2
// https://codeforces.com/contest/2003/problem/B

/*
B. Turtle and Piggy Are Playing a Game 2

Algorithm:
This problem involves a game between two players (Turtle and Piggy) modifying a sequence.
The key insight is that each player chooses an adjacent pair and replaces one element with either max or min of the two, removing the other.
Since both players play optimally, we analyze what happens at each step:
- Turtle (maximizer) will choose an index to maximize a[0] in the end
- Piggy (minimizer) will choose an index to minimize a[0] in the end

However, upon closer observation or mathematical analysis of the optimal strategy,
it turns out that for this specific game, the final value of a[0] equals the median of the array.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array

*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read array elements
    }
    sort(a.begin(), a.end()); // Sort to find median
    printf("%ld\n", a[n / 2]); // Median is at index n/2 in sorted array
  }
}


// https://github.com/VaHiX/codeForces/