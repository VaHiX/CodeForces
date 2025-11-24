// Problem: CF 669 A - Little Artem and Presents
// https://codeforces.com/contest/669/problem/A

/*
 * Problem: Little Artem and Presents
 * Algorithm: Mathematical approach to find maximum number of presents
 * 
 * Approach:
 * - We want to maximize the number of times we can give stones to Masha
 *   such that no two consecutive gifts have the same amount.
 * - The optimal strategy is to alternate between giving 1 and 2 stones.
 * - If we have n stones:
 *   - We can give 2 stones, then 1 stone, and so on.
 *   - This pattern allows us to use 3 stones in total for 2 presents.
 *   - So, for every 3 stones, we get 2 presents.
 *   - If n % 3 == 0, we use up all stones in groups of 3.
 *   - If n % 3 == 1, we have 1 extra stone that can be used to give 1 more present.
 *   - If n % 3 == 2, we have 2 extra stones that can be used to give 2 more presents.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld\n", &n);
  printf("%ld\n", 2 * (n / 3) + (n % 3 > 0)); // Calculate maximum number of presents
  return 0;
}


// https://github.com/VaHiX/CodeForces/