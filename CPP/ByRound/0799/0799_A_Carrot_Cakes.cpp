// Problem: CF 799 A - Carrot Cakes
// https://codeforces.com/contest/799/problem/A

/*
 * Problem: Carrot Cakes
 * Algorithm/Technique: Mathematical comparison to determine if building a second oven is beneficial.
 *
 * Time Complexity: O(1) - Only a few arithmetic operations and a single comparison.
 * Space Complexity: O(1) - Constant extra space used.
 *
 * The solution determines whether building a second oven reduces the time to bake 'n' cakes.
 * It compares the time it takes to build the second oven 'd' with the time needed to bake 
 * 'n' cakes using only the first oven, assuming the second oven is not built until after 'd' time.
 * 
 * Key idea:
 * If we can start baking with the second oven before the first oven finishes baking all cakes,
 * then it is beneficial. Otherwise, it's not reasonable.
 *
 * The condition checks:
 * - Whether the time to build the second oven (d) is less than the time it takes for 
 *   the first oven to bake (n-1)/k batches, each taking t minutes. 
 *   This is a mathematical way to estimate when the first oven finishes baking n cakes.
 *   Using integer division and floor of the ratio ensures correct batch counting.
 */
#include <cstdio>
int main() {
  int n, t, k, d;
  scanf("%d %d %d %d", &n, &t, &k, &d);
  puts((d < ((n - 1) / k) * t) ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/