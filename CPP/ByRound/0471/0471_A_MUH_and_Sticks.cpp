// Problem: CF 471 A - MUH and Sticks
// https://codeforces.com/contest/471/problem/A

/*
 * Purpose: Determine whether the given 6 sticks can form a bear or an elephant
 *          based on specific stick length rules.
 *
 * Algorithm:
 * 1. Count frequency of each stick length (1 to 9).
 * 2. Sort the frequency counts in ascending order.
 * 3. Analyze the highest and second-highest frequencies to determine:
 *    - If 4 or more sticks have the same length -> legs for an animal
 *    - If 2 sticks of same length are left over -> head and body for elephant (equal)
 *    - If 1 stick of same length is left over -> head and body for bear (different)
 *
 * Time Complexity: O(1) - Fixed input size (6 sticks) and fixed array size (10).
 * Space Complexity: O(1) - Fixed-size array of 10 integers and small vectors.
 */
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  const int N = 10;  // Array size to store counts of stick lengths 1-9
  const int S = 6;   // Number of sticks
  std::vector<int> counts(N, 0);  // Count of each stick length (index 0 unused)
  for (int p = 0; p < S; p++) {   // Read all 6 stick lengths
    int temp;
    scanf("%d", &temp);
    ++counts[temp];  // Increment count for the corresponding stick length
  }
  std::sort(counts.begin(), counts.end());  // Sort frequencies in ascending order

  // If the most frequent length appears less than 4 times, not enough for legs
  if (counts[N - 1] < 4) {
    puts("Alien");
  } else if (counts[N - 2] == 2 || counts[N - 1] == 6) {
    // If second highest count is 2 (i.e., 2 sticks left), or all 6 are same -> elephant
    puts("Elephant");
  } else if (counts[N - 2] == 1 || counts[N - 1] == 5) {
    // If second highest count is 1 (i.e., 1 stick left), or 5 sticks same -> bear
    puts("Bear");
  } else {
    puts("Error");  // Should not occur given constraints
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/