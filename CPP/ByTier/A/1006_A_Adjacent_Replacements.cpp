// Problem: CF 1006 A - Adjacent Replacements
// https://codeforces.com/contest/1006/problem/A

/*
 * Code Purpose: 
 *   This code implements Mishka's Adjacent Replacements Algorithm on an array of integers.
 *   For each element in the array, it applies a transformation such that:
 *   - Odd numbers (1, 3, 5, ...) are replaced by (number + 1)
 *   - Even numbers (2, 4, 6, ...) are replaced by (number - 1)
 *   The transformation effectively swaps adjacent pairs of integers (1<->2, 3<->4, ..., (10^9-1)<->10^9).
 *
 * Algorithms/Techniques:
 *   - Simple array traversal with transformation logic
 *   - Bit manipulation trick: k + k % 2 - 1
 *     - For even k: k % 2 = 0, so result = k - 1
 *     - For odd k: k % 2 = 1, so result = k + 1
 *
 * Time Complexity: O(n)
 *   - Single pass through the array of size n.
 *
 * Space Complexity: O(1)
 *   - Only a constant amount of extra space used (variables k and n).
 */

#import <cstdio>
int k, n;
int main() {
  // Read the number of elements
  for (scanf("%d", &n); n--; printf("%d ", k + k % 2 - 1))
    // Read each element and immediately transform and print it
    scanf("%d", &k);
}


// https://github.com/VaHiX/CodeForces/