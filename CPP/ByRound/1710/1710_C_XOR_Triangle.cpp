// Problem: CF 1710 C - XOR Triangle
// https://codeforces.com/contest/1710/problem/C

/*
 * Problem: XOR Triangle
 * 
 * Purpose:
 *   This program calculates the number of triples (a, b, c) with 0 <= a, b, c <= n
 *   such that a⊕b, b⊕c, and a⊕c form the sides of a non-degenerate triangle,
 *   where n is given in binary representation.
 * 
 * Approach:
 *   The solution uses dynamic programming with digit DP (digit dynamic programming).
 *   It processes the binary representation of n bit by bit and keeps track of
 *   constraints on XOR values using a state machine.
 *   
 *   Key Idea:
 *   - We are counting valid triples (a,b,c) such that:
 *     - a⊕b, b⊕c, a⊕c are sides of a valid triangle (triangle inequality)
 *   - We build a DP state that tracks valid combinations of bits and their relation to triangle inequality constraints.
 * 
 * Time Complexity: O(k * 64 * 2^3) where k = number of digits in binary representation of n.
 * Space Complexity: O(k * 64) for storing the DP states.
 * 
 * The DP state represents bit combinations of (a,b,c) up to position i in the binary string n,
 * with 64 possible internal states encoding certain constraints.
 */
#include <stdio.h>
#include <string.h>

const int K = 2e5 + 3, M = 998244353;
int k, f[K][64], s;
char a[K];

int main() {
  // Read the binary string representation of n
  scanf("%s", a + 1), k = strlen(a + 1);
  
  // Initialize the DP state for the first character (base case)
  f[0][63] = 1;
  
  // Loop through each bit position of n
  for (int i = 1; i <= k; i++)
    // Iterate over all current states (64 possible states)
    for (int O = 0; O < 64; O++)
      // Loop over possible values for a[i], b[i], c[i] (each is a binary digit 0 or 1)
      for (int k = 0; k < 2; k++)
        for (int u = 0; u < 2; u++)
          for (int v = 0; v < 2; v++) {
            // Skip if this selection violates the constraints imposed by the binary string n
            if (a[i] == '0' &&
                (O & 1 & k | O >> 1 & 1 & (u ^ k) | O >> 2 & 1 & (v ^ k)))
              continue;
            
            // Compute new state encoding properties of triangle inequality
            int OO = 0;
            
            // Bit 0: Check if a[i] == 1 when k==0 and a[i] == '0', else 0
            OO |= (O & 1 << 0) * (k || a[i] == '0');
            
            // Bit 1: Check if (b[i] ^ a[i]) == 1 when k==0 and a[i] == '0', else 0
            OO |= (O & 1 << 1) * ((u ^ k) || a[i] == '0');
            
            // Bit 2: Check if (c[i] ^ a[i]) == 1 when k==0 and a[i] == '0', else 0
            OO |= (O & 1 << 2) * ((v ^ k) || a[i] == '0');
            
            // Bit 3: Check if (b[i] | c[i]) == b[i] (i.e., b[i] is subset of b[i]|c[i])
            OO |= (O & 1 << 3) * ((u | v) == u);
            
            // Bit 4: Check if (b[i] | c[i]) == c[i] (i.e., c[i] is subset of b[i]|c[i])
            OO |= (O & 1 << 4) * ((u | v) == v);
            
            // Bit 5: Check if (b[i] & c[i]) == 0 (i.e., b[i] and c[i] are disjoint)
            OO |= (O & 1 << 5) * ((u & v) == 0);
            
            // Update the DP table with count
            f[i][OO] = (f[i][OO] + f[i - 1][O]) % M;
          }
  
  // Sum over all final valid states (first 8 valid combinations of triangle constraints)
  for (int O = 0; O < 8; O++)
    s = (s + f[k][O]) % M;
  
  // Output the final answer
  printf("%d\n", s);
  return 0;
}


// https://github.com/VaHiX/CodeForces/