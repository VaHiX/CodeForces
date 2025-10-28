// Problem: CF 1851 A - Escalator Conversations
// https://codeforces.com/contest/1851/problem/A

/*
 * Problem: A. Escalator Conversations
 * 
 * Purpose: Given n people with different heights, determine how many of them
 *          can have a conversation with Vlad on an escalator with m steps,
 *          where each step has height i*k and Vlad's height is H.
 *          
 * Algorithm:
 *   - For each person, compute the required step position to match their height difference with Vlad.
 *   - A valid conversation occurs if both people are on different steps, and the height difference
 *     equals k * number_of_steps_between_them.
 *   - We iterate over all people and count those for which such a step exists within [1, m].
 *   
 * Time Complexity: O(n) per test case, since we process each person once.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k, H;
    scanf("%ld %ld %ld %ld", &n, &m, &k, &H);
    long cnt(0);
    for (long p = 0; p < n; p++) {
      long u;
      scanf("%ld", &u);
      long diff = H - u; // Height difference between Vlad and current person
      if (!diff || diff % k) {
        // If no difference or difference not divisible by step height k, skip
        continue;
      }
      if (diff < 0) {
        diff = -diff; // Ensure positive difference
      }
      // Check if the required step difference fits within [1, m]
      cnt += (diff < m * k);
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/