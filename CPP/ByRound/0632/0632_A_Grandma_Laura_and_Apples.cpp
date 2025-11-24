// Problem: CF 632 A - Grandma Laura and Apples
// https://codeforces.com/contest/632/problem/A

/*
 * Problem: Grandma Laura and Apples
 * 
 * Algorithm/Technique: Simulation with reverse reasoning
 * 
 * Time Complexity: O(n), where n is the number of buyers
 * Space Complexity: O(1), only using a few variables regardless of input size
 * 
 * Approach:
 * We simulate the process in reverse. At each step, we track how many apples
 * were sold and how many half-apples were given as gifts. The key insight is:
 * 
 * 1. Each buyer takes half of the apples available at the time of purchase.
 * 2. If the number of apples is odd, a half apple is given as a gift.
 * 3. We use a binary power to track apples at each step (2^i represents apples
 *    present at the i-th step from the end).
 * 4. Total money is calculated as: (total apples sold * price) - (half-apples given as gifts * price).
 * 
 * Example walkthrough for sample 1:
 * n=2, p=10, sequence: half, halfplus
 * - Step 1 (from end): buyer gets halfplus → gives 0.5 apple as gift, takes 1 apple.
 *   binPower = 1, so total += 1, gift += 0.5
 * - Step 2: buyer gets half → takes 0.5 apple.
 *   binPower = 2, so total += 2
 * Final: total = 3, gift = 0.5
 * Result = 10 * (3 - 0.5) = 25, but this is wrong; we must reconsider.
 *
 * Actually, reverse simulation:
 * At the end of day, there are 0 apples.
 * For the last buyer ('halfplus'):
 *   She gives 0.5 apple and takes 0.5 apple → total apples were 1.
 * For the second to last buyer ('half'):
 *   He takes 0.5 and gives 0.5 as gift → total apples were 2.
 * So total apples = 1 + 2 = 3.
 * But this is not accurate either.
 * 
 * Correctly:
 * Work backwards:
 * - At final step: 0 apples left
 * - Last buyer ('halfplus') took 0.5, gave 0.5 as gift.
 *   So before that step, she had 1 apple.
 * - Second to last buyer ('half') took half of 2 apples.
 *   So before that, she had 2 apples.
 * So 1 + 2 = 3 apples initially.
 * The total money is (2 + 1) * price = 3 * 10 = 30. But expected is 15.
 *
 * Re-analyzing:
 * Let's consider "binPower" = apple count at step, starting from 1 and doubling.
 * Let's assume we work from last to first.
 * When we see "halfplus", the number of apples before that buyer was 2*(apples_taken + 0.5) = 2*binPower.
 * When we see "half", the number of apples was 2*binPower.
 *
 * But it's easier to think in terms of "binary powers":
 * binPower = 2^i represents how many apples were sold in that step,
 * but the number of actual apples was determined by the step type.
 *
 * Revisited:
 * At the start of the day, some number of apples exists.
 * If at some buyer step, it's 'halfplus':
 *   that buyer gets (apples / 2) + 0.5, total apples are 2*(buyers_apple) = 2*(half + 0.5) = apple + 1.
 * If it's 'half':
 *   buyer gets apples / 2, so apples were 2 * (half) = 2 * buyers_apple.
 * 
 * But the code does something smart:
 * It accumulates binPower = the number of apples taken at each step, and keeps track of gifts.
 * Total apples = binPower for each 'halfplus' step.
 * Gift apples = 0.5 for each 'halfplus' step.
 * Then total money = (total apples - gift) * cost.
 * This works when we simulate from the end.
 */

#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long n, p;
  std::cin >> n >> p;
  int64_t total(0), binPower(1); // binPower keeps doubling every step
  double gift(0); // counts total gift apples given as half apples
  for (long q = 0; q < n; q++) {
    std::string s;
    std::cin >> s;
    if (s == "halfplus") {
      // If it's halfplus, the buyer receives full apple amount and an extra half apple as gift
      total += binPower; // Add apple amount taken (full)
      gift += 0.5;       // Add gift half apple
    }
    binPower *= 2;  // Next step has 2 times more apples than previous step
  }
  printf("%.0lf\n", (p * (total - gift)));  // Convert to total money
  return 0;
}


// https://github.com/VaHiX/CodeForces/