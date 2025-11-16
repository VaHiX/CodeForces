// Problem: CF 965 D - Single-use Stones
// https://codeforces.com/contest/965/problem/D

/*
Purpose: This code solves the problem of determining the maximum number of frogs that can cross a river using stones as jumping points.
         Each frog can jump a maximum distance of 'l' units and stones at position i can be used by at most one frog.
         The river is 'w' units wide, and there are 'a_i' stones at distance i from the start.

Algorithms/Techniques: 
- Greedy approach with sliding window
- Dynamic allocation and update of available stones at each position

Time Complexity: O(w * l), where w is the width of the river and l is the maximum jump length.
Space Complexity: O(w), for storing the number of stones at each position and the frog count at each position.

*/

#include <cstdio>
#include <vector>
int main() {
  long w, l;
  scanf("%ld %ld", &w, &l);
  std::vector<long> a(w + 1, 2e9);  // Store the number of stones at each position
  for (long p = 1; p < w; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> b(w + 1, 0);  // b[i] represents how many frogs can pass through position i
  for (long p = 1; p <= w; p++) {
    if (a[p] <= 0) {
      continue;  // No stones at this position, skip
    }
    if (p <= l) {
      b[p] = a[p];  // If position is within initial jump range, all stones can be used
      continue;
    }
    // For positions beyond initial jump range, we need to redistribute stones from previous positions
    for (long u = p - l; u < p; u++) {
      long mv = (b[u] < (a[p] - b[p])) ? b[u] : (a[p] - b[p]);  // Calculate how many frogs from position u can be moved to p
      b[u] -= mv;  // Reduce the number of frogs at u
      b[p] += mv;  // Increase the number of frogs at p
      if (b[p] >= a[p]) {  // If all stones at p are now used, break
        break;
      }
    }
  }
  printf("%ld\n", b.back());  // Output the maximum number of frogs that can cross the river
  return 0;
}


// https://github.com/VaHiX/CodeForces/