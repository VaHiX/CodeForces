// Problem: CF 526 C - Om Nom and Candies
// https://codeforces.com/contest/526/problem/C

/*
 * Problem: C. Om Nom and Candies
 * Algorithm: Enumeration with optimization
 * 
 * Purpose: Given two types of candies (red and blue) with different weights and joy values,
 *          determine the maximum joy Om Nom can get without exceeding a weight limit.
 *          Each candy must be eaten whole.
 * 
 * Time Complexity: O(min(Wr, Wb)) where Wr and Wb are the weights of red and blue candies.
 * Space Complexity: O(1)
 * 
 * Techniques:
 * - Optimization using sorting of weights to reduce search space
 * - Enumeration over possible number of candies of the heavier type
 * - Greedy choice for the optimal combination based on joy-to-weight ratio
 */

#include <algorithm>
#include <iostream>
#include <utility>

int main() {
  const long long bound = 1000; // Threshold to switch between approaches
  long long C, Hr, Hb, Wr, Wb;
  std::cin >> C >> Hr >> Hb >> Wr >> Wb;
  long long best = 0;
  
  // Ensure Wr >= Wb for consistent processing
  if (Wr < Wb) {
    std::swap(Wr, Wb);
    std::swap(Hr, Hb);
  }
  
  // If the heavier candy is too heavy, brute force over all possible counts
  if (Wr >= bound) {
    for (long long i = 0; i * Wr <= C; ++i) {
      best = std::max(best, i * Hr + ((C - i * Wr) / Wb) * Hb);
    }
  } else {
    // If the lighter candy is more efficient in terms of joy per weight, 
    // we try to enumerate over the lighter one's count and optimize accordingly
    if (Hr * Wb > Hb * Wr) {
      std::swap(Wr, Wb);
      std::swap(Hr, Hb);
    }
    // Brute force over small number of lighter candies
    for (long long i = 0; i <= bound; ++i) {
      if (i * Wr > C)
        continue;
      best = std::max(best, i * Hr + ((C - i * Wr) / Wb) * Hb);
    }
  }
  std::cout << best << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/