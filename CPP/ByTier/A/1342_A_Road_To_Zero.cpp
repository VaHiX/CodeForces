// Problem: CF 1342 A - Road To Zero
// https://codeforces.com/contest/1342/problem/A

/*
 * Problem: A. Road To Zero
 * Algorithms/Techniques: Greedy
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The problem involves finding the minimum cost to reduce two integers x and y to zero.
 * Two operations are available:
 * 1. Pay 'a' dollars to change either x or y by 1.
 * 2. Pay 'b' dollars to change both x and y by 1.
 *
 * Strategy:
 * - Always ensure x <= y by swapping if needed.
 * - Compare the cost of using operation 1 (a) versus operation 2 (b).
 * - If b > 2*a, it's better to use individual operations.
 * - Otherwise, use pairing operations as much as possible.
 */

#include <stdio.h>
#include <iostream>
#include <utility>

long long t, a, b, x, y;
int main() {
  for (scanf("%lld", &t); t--;
       printf("%lld\n", b > 2 * a ? (x + y) * a : (y - x) * a + x * b)) {
    std::cin >> x >> y >> a >> b;
    if (x > y)
      std::swap(x, y);
  }
}


// https://github.com/VaHiX/codeForces/