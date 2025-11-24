// Problem: CF 1955 A - Yogurt Sale
// https://codeforces.com/contest/1955/problem/A

/*
 * Problem: A. Yogurt Sale
 * Purpose: Determine the minimum cost to buy exactly n yogurts,
 *          where individual yogurts cost 'a' burles and pairs cost 'b' burles.
 * Algorithm: Greedy approach.
 *            For each pair of yogurts, decide whether buying them at promotion price (b)
 *            or regular price (2*a) is cheaper.
 *            Then handle the remaining single yogurt if n is odd.
 *
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), constant extra space used.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b;
    scanf("%ld %ld %ld", &n, &a, &b);
    // Calculate the minimum cost for each pair of yogurts
    long d = (2 * a < b ? (2 * a) : b);
    // For n yogurts: (n / 2) pairs and possibly one leftover yogurt
    printf("%ld\n", (n / 2) * d + (n % 2) * a);
  }
}


// https://github.com/VaHiX/codeForces/