// Problem: CF 878 A - Short Program
// https://codeforces.com/contest/878/problem/A

/*
 * Problem: Short Program in CALPAS language
 * 
 * Purpose: Given a sequence of bitwise operations (AND, OR, XOR) on integers,
 *          reduce the sequence to at most 5 operations such that the result
 *          is equivalent for all inputs from 0 to 1023.
 * 
 * Approach:
 * - For each bit position (0 to 10), determine the effect of the sequence of operations
 *   on that bit.
 * - Maintain three action arrays for each bit:
 *   - action[p] = 0 means AND operation with a 0 bit at that position
 *   - action[p] = 1 means OR operation with a 1 bit at that position
 *   - action[p] = 2 means XOR operation (toggle) at that position
 *   - action[p] = -1 means no effect (or default).
 * - Reconstruct final constants for AND, OR, and XOR based on these actions.
 * 
 * Time Complexity: O(n * log(max_value)) where n is the number of operations and log(max_value) = 10
 * Space Complexity: O(1) - fixed-size arrays (10 elements) used
 */
#include <cstdio>
int main() {
  const int N = 10; // Since values are up to 1023, we only need 10 bits
  long n;
  scanf("%ld\n", &n);
  int action[N]; // Array to store effect of each bit position
  for (int p = 0; p < N; p++) {
    action[p] = -1; // Initialize all positions as having no effect
  }
  while (n--) {
    char x;
    int u;
    scanf("%c %d\n", &x, &u);
    for (int p = 0; p < N; p++) {
      bool v = u & 1; // Check if the least significant bit of u is 1
      if (x == '&' && !v) {
        action[p] = 0; // For AND with 0, result always 0, regardless of input
      } else if (x == '|' && v) {
        action[p] = 1; // For OR with 1, result always 1, regardless of input
      } else if (x == '^' && v) {
        action[p] = 1 - action[p]; // For XOR with 1, flip the action state
      }
      u /= 2; // Move to next bit
    }
  }
  int andint(0); // Compute the AND constant
  for (int p = N - 1; p >= 0; p--) {
    andint *= 2;
    andint += 1 - (action[p] == 0); // Set bit if action is not AND with 0 (i.e., not forced to 0)
  }
  int orint(0); // Compute the OR constant
  for (int p = N - 1; p >= 0; p--) {
    orint *= 2;
    orint += (action[p] == 1); // Set bit if action is OR with 1 (i.e., always 1)
  }
  int xorint(0); // Compute the XOR constant
  for (int p = N - 1; p >= 0; p--) {
    xorint *= 2;
    xorint += (action[p] == 2); // Set bit if action is XOR operation
  }
  printf("3\n& %d\n| %d\n^ %d\n", andint, orint, xorint);
  return 0;
}


// https://github.com/VaHiX/CodeForces/