// Problem: CF 1313 A - Fast Food Restaurant
// https://codeforces.com/contest/1313/problem/A

/*
 * Problem: A. Fast Food Restaurant
 * Purpose: Determine the maximum number of visitors Denis can feed given constraints on portions of dishes.
 * 
 * Algorithm:
 *   - For each test case, we are given a, b, c representing the number of dumplings, cranberry juice,
 *     and pancakes available.
 *   - We want to maximize the number of visitors, where each visitor gets a unique combination of dishes
 *     (at least one dish, at most one portion per dish type).
 *   - This is essentially finding the maximum number of distinct non-empty subsets from {a, b, c} 
 *     under the constraint that we only use one portion per dish per visitor.
 *   - Strategy:
 *     1. Sort values to simplify logic: a >= b >= c
 *     2. Greedily assign dishes trying to maximize variety in combinations (unique sets)
 *     3. Use heuristics to try to match as many unique sets as possible within resource limits
 * 
 * Time Complexity: O(1) - Fixed number of operations regardless of input size.
 * Space Complexity: O(1) - Only a constant amount of extra space used.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    // Ensure a >= b >= c by swapping if necessary
    if (b > a) {
      long tmp = a;
      a = b;
      b = tmp;
    }
    if (c > a) {
      long tmp = a;
      a = c;
      c = tmp;
    }
    if (c > b) {
      long tmp = c;
      c = b;
      b = tmp;
    }
    // cnt counts how many visitors we can serve
    long cnt(0);
    // Start by giving one dish to as many people as possible
    if (a) {
      --a;
      ++cnt;
    }
    if (b) {
      --b;
      ++cnt;
    }
    if (c) {
      --c;
      ++cnt;
    }
    // Give pairs of dishes where possible
    if (a && b) {
      ++cnt;
      --a;
      --b;
    }
    if (a && c) {
      ++cnt;
      --a;
      --c;
    }
    if (b && c) {
      ++cnt;
      --b;
      --c;
    }
    // Give full triplicates where possible
    if (a && b && c) {
      ++cnt;
      --a;
      --b;
      --c;
    }
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/