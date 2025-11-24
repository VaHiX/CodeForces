// Problem: CF 1905 A - Constructive Problems
// https://codeforces.com/contest/1905/problem/A

/*
 * Problem: Gridlandia Reconstruction
 * 
 * Description:
 * Given an n×m matrix representing Gridlandia, where each cell is a city that can either be rebuilt or collapsed,
 * we need to find the minimum number of cities the government must initially rebuild so that, using the rules
 * of adjacent aid, all cities eventually become rebuilt.
 *
 * Rules for Aid:
 * - A collapsed city at position (i,j) becomes rebuilt if:
 *   - At least one of its vertically adjacent neighbors is rebuilt: (i+1,j) or (i−1,j)
 *   - At least one of its horizontally adjacent neighbors is rebuilt: (i,j+1) or (i,j−1)
 * 
 * Approach:
 * The key insight is that we can model this as a minimal dominating set problem on a grid graph.
 * However, due to the nature of how aid spreads, it's sufficient to place initial rebuilds such that
 * they form a pattern that allows full coverage. One efficient approach is to place cities in a checkerboard-like
 * pattern: if we place rebuilds at positions where (i + j) % 2 == 0 or (i + j) % 2 == 1, depending on configuration.
 *
 * Actually, optimal minimal solution uses placing one city per row and column ensuring that they are not directly
 * connected by horizontal/vertical adjacency and cover the grid efficiently. This leads to:
 * The minimum number of cities to rebuild is simply the maximum of n and m.
 * 
 * But let’s reconsider – the most efficient strategy is to realize that:
 * We can think of placing a set of cities such that each cell can be reached by at least one neighbor
 * from both direction. That leads us to a known result: The minimum number of initial cells needed
 * on an n×m board is floor((n + 1)/2) * floor((m + 1)/2), but that isn't right either.
 *
 * Correct approach:
 * In grid problems of this nature where adjacent neighbors can help rebuild,
 * it’s actually sufficient to build exactly one city in every other row and column or vice versa,
 * resulting in a minimum total of min(n, m) when n, m > 1.
 *
 * Wait - looking carefully at examples:
 * For case (2,2): answer 2 → which is 2
 * For (5,7): answer 7 → which is 7
 * For (3,2): answer 3 → which is 3
 *
 * It looks like result = max(n, m).
 *
 * But that doesn’t hold either for small cases...
 * Actually checking again:
 * (n=2,m=2) => 2. If we build the corner cities we could possibly do better.
 * Looking at example: Rebuilds at (1,2), (2,1). That's 2.
 * But (5,7) => 7 — we need 7 cities, so that’s not min(n,m).
 *
 * Let’s analyze:
 * In fact, minimal required number of cities is ceil(n/2) * ceil(m/2)
 * No! This too may be incorrect. Let's take example data:
 * n=5, m=7 answer = 7; but ceil(5/2)*ceil(7/2) = 3*4 = 12.
 * 
 * So actually it is min(n,m), but let’s see again — no, not matching.
 *
 * The best approach is to observe that minimum number of cities needed:
 * is the largest dimension — i.e., max(n,m).
 *
 * Algorithms/Techniques: Constructive Problems, Greedy Logic
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t); // Read number of test cases
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m); // Read dimensions
    printf("%ld\n", n > m ? n : m); // Output maximum of n and m
  }
}


// https://github.com/VaHiX/codeForces/