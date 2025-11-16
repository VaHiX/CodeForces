// Problem: CF 679 B - Bear and Tower of Cubes
// https://codeforces.com/contest/679/problem/B

/* 
B. Bear and Tower of Cubes
Algorithm: Recursive backtracking with greedy choice optimization.
Time Complexity: O(log^3(m)) - Each recursive call reduces the problem size significantly due to cubic growth of block sizes.
Space Complexity: O(log^2(m)) - Depth of recursion is bounded by the number of cubes needed, and each level stores a few constants.

The solution uses a recursive backtracking approach:
- At each step, find the largest cube that fits into remaining volume.
- Try adding this cube (greedy choice).
- Also try a "second-best" option: using a block of size x and replacing it with two smaller blocks (x-1) and (x-1) if possible,
  but only if x >= 1 to avoid negative indices.

This aims to maximize the number of blocks while secondarily maximizing the total volume X.
*/ 

#include <stdint.h>
#include <cstdio>
#include <algorithm>
#include <utility>

int64_t cube(int64_t a) { return a * a * a; }

void rec(int64_t m, int64_t steps, int64_t sub,
         std::pair<int64_t, int64_t> &best) {
  if (m == 0) {
    // Base case: reached exact volume, update best with max number of steps and sum
    best = std::max(best, std::make_pair(steps, sub));
    return;
  }
  
  int64_t x = 1;
  // Find the largest cube that is <= m
  while (cube(x + 1) <= m) {
    ++x;
  }
  
  // Try taking the largest possible cube and proceed recursively
  rec(m - cube(x), steps + 1, sub + cube(x), best);
  
  // Try a greedy alternative: replace x^3 with (x-1)^3 + (x-1)^3 if valid, and continue
  if (x >= 1) {
    rec(cube(x) - 1 - cube(x - 1), steps + 1, sub + cube(x - 1), best);
  }
  
  return;
}

int main() {
  int64_t m;
  scanf("%lld", &m);
  std::pair<int64_t, int64_t> best{-1, 0}; // Initialize with invalid step count to ensure all valid updates
  rec(m, 0, 0, best);
  printf("%lld %lld\n", best.first, best.second);
  return 0;
}


// https://github.com/VaHiX/codeForces/