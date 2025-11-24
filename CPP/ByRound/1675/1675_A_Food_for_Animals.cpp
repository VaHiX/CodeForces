// Problem: CF 1675 A - Food for Animals
// https://codeforces.com/contest/1675/problem/A

/*
 * Problem: A. Food for Animals
 * Purpose: Determine if there is enough food packs (dog, cat, universal) to feed all dogs and cats.
 * Algorithm:
 *   - For each test case, calculate how many packs are needed for dogs and cats.
 *   - Use available packs of dog food (a) and cat food (b) first.
 *   - Then use universal food (c) to cover any remaining needs.
 *   - Check if total required packs fit within the available universal food.
 *
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), only using a fixed amount of variables.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, x, y;
    scanf("%ld %ld %ld %ld %ld", &a, &b, &c, &x, &y);
    // Reduce x by the amount of dog food available (a), but not more than x
    x -= (a < x ? a : x);
    // Reduce y by the amount of cat food available (b), but not more than y
    y -= (b < y ? b : y);
    // Check if remaining x + y can be covered by universal food c
    bool res = (x + y <= c);
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/