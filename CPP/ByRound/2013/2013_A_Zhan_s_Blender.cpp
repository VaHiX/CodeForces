// Problem: CF 2013 A - Zhan's Blender
// https://codeforces.com/contest/2013/problem/A

/*
 * Problem: Zhan's Blender
 * Algorithm/Technique: Mathematical Optimization
 *
 * Description:
 * Zhan has n fruits to blend using a blender that can process min(x, c) fruits per second,
 * where c is the number of fruits currently in the blender. He can add up to y fruits per second.
 * The goal is to find the minimum time (in seconds) to blend all fruits.
 *
 * Approach:
 * - If n = 0, no time is needed.
 * - If n <= y, we can add all fruits in one go and blend them in ceil(n/x) seconds.
 * - Otherwise, we first fill the blender with up to y fruits (taking 1 second).
 *   Then we continue adding fruits at rate y per second, but must also account for
 *   blending. Since we get a new batch every second after initial setup,
 *   the time is determined by how many full batches we can form,
 *   which leads to: ceil(n / y) seconds of adding + (n % y) remaining fruits.
 *   But since we always take at least one second per batch, we optimize:
 *   - If n <= y, just ceil(n/x) seconds
 *   - Else, it's (n + y - 1) / y + (n % y == 0 ? 0 : 1) steps,
 *     but we already have a better formula: (n + z - 1) / z where z = min(x,y)
 *     This is a trick that simplifies the calculation when considering both rates.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x, y;
    scanf("%ld %ld", &x, &y);
    long z = (x < y ? x : y); // Take the smaller of the two - represents limiting factor
    printf("%ld\n", (n + z - 1) / z); // Mathematical shortcut to compute minimum time
  }
}


// https://github.com/VaHiX/codeForces/