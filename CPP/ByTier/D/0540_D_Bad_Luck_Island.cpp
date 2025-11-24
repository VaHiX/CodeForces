// Problem: CF 540 D - Bad Luck Island
// https://codeforces.com/contest/540/problem/D

/*
 * Problem: Bad Luck Island
 * Algorithm: Dynamic Programming with Reverse Calculation
 * 
 * Purpose: This program calculates the probability that each of the three species
 * (rocks, scissors, papers) will be the only one surviving on the island.
 *
 * The solution uses dynamic programming by working backwards from the final state
 * where one species dominates. At each step, we calculate how the probability
 * propagates from a state with r, s, p individuals to states with one less
 * individual of a specific species. The transitions are based on which two
 * individuals meet and which one kills the other.
 *
 * Time Complexity: O(r * s * p * (r + s + p))
 * Space Complexity: O(r * s * p)
 */

#include <cstdio>
int main() {
  int r, s, p;
  scanf("%d %d %d\n", &r, &s, &p);
  // prob[a][b][c] stores the probability that the system ends with a rocks, b scissors, c papers
  double prob[r + 1][s + 1][p + 1];
  // Initialize all probabilities to 0
  for (int a = 0; a <= r; a++) {
    for (int b = 0; b <= s; b++) {
      for (int c = 0; c <= p; c++) {
        prob[a][b][c] = 0;
      }
    }
  }
  // Base case: when only one species remains, probability is 1
  prob[r][s][p] = 1;
  // Iterate backwards through possible total populations
  for (int sum = r + s + p; sum >= 0; sum--) {
    for (int remR = r; remR >= 0; remR--) {
      for (int remS = s; remS >= 0; remS--) {
        int remP = sum - remR - remS;
        if (remP < 0 || remP > p) {
          continue; // Skip invalid states
        }
        // Skip if all but one species are zero (we don't process these)
        if (remR == 0 && remS == 0) {
          continue;
        }
        if (remP == 0 && remS == 0) {
          continue;
        }
        if (remR == 0 && remP == 0) {
          continue;
        }
        double current = prob[remR][remS][remP];
        // Number of ways each pair can meet
        long waysS = remR * remS; // Rock vs Scissors
        long waysP = remS * remP; // Scissors vs Paper
        long waysR = remP * remR; // Paper vs Rock
        long totalWays = waysR + waysS + waysP;
        // Distribute probability to next states based on which species is eliminated
        if (remR > 0) {
          prob[remR - 1][remS][remP] += current * waysR / totalWays;
        }
        if (remS > 0) {
          prob[remR][remS - 1][remP] += current * waysS / totalWays;
        }
        if (remP > 0) {
          prob[remR][remS][remP - 1] += current * waysP / totalWays;
        }
      }
    }
  }
  // Sum up probabilities of ending in a specific species
  double ansR(0), ansS(0), ansP(0);
  for (int remR = 1; remR <= r; remR++) {
    ansR += prob[remR][0][0];
  }
  for (int remS = 1; remS <= s; remS++) {
    ansS += prob[0][remS][0];
  }
  for (int remP = 1; remP <= p; remP++) {
    ansP += prob[0][0][remP];
  }
  printf("%.10lf %.10lf %.10lf\n", ansR, ansS, ansP);
  return 0;
}


// https://github.com/VaHiX/CodeForces/