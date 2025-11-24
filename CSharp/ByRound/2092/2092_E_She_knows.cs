// Problem: CF 2092 E - She knows...
// https://codeforces.com/contest/2092/problem/E

/*
 * Problem: D. Pippy is preparing for a "black-and-white" party at his home.
 *          He wants to repaint the floor of an n×m board such that the number of 
 *          adjacent cells with different colors is even.
 *          
 *          The board has k fixed cells already painted (either black or white).
 *          The remaining cells must be painted either black or white.
 *          
 *          The task is to count valid ways to repaint all the green cells,
 *          such that the number of adjacent cells with differing colors is even.
 * 
 *          This problem can be solved using the principle of inclusion-exclusion
 *          and modular exponentiation over a finite field (Fermat's little theorem).
 * 
 * Algorithm:
 *  - For each test case, count how many border cells are fixed and their parity sum.
 *  - Compute the total number of odd-degree nodes in the board.
 *  - The result is based on power of 2 raised to an exponent derived from the board dimensions and fixed points.
 * 
 * Time Complexity: O(T * K), where T is number of test cases and K is sum of fixed cells across all cases.
 * Space Complexity: O(1) - Only using a constant amount of extra space.
 */

using System;
using System.Numerics;
class Program {
  private static long N_global, M_global;
  private static int K_global;
  private const long MOD = 1_000_000_007;
  private const long MOD_PHI = 1_000_000_006; // φ(MOD) = MOD - 1
  static long Power(long baseValue, long exp) {
    long result = 1;
    baseValue %= MOD;
    while (exp > 0) {
      if (exp % 2 == 1)
        result = (result * baseValue) % MOD;
      baseValue = (baseValue * baseValue) % MOD;
      exp /= 2;
    }
    return result;
  }
  static long ComputeExponent(long nVal, long mVal, int kVal, bool minusOne) {
    // Reduce exponents using Euler's theorem: a^φ(n) ≡ 1 mod n
    long nMod = nVal % MOD_PHI;
    long mMod = mVal % MOD_PHI;
    long nmMod = (nMod * mMod) % MOD_PHI;
    long kMod = kVal % MOD_PHI;
    if (kMod < 0)
      kMod += MOD_PHI;
    long expBase = (nmMod - kMod + MOD_PHI) % MOD_PHI;
    return minusOne ? (expBase - 1 + MOD_PHI) % MOD_PHI : expBase;
  }
  static bool IsBorderNonCorner(long r, long c) {
    if (r < 1 || r > N_global || c < 1 || c > M_global)
      return false;
    bool onBorder = (r == 1 || r == N_global || c == 1 || c == M_global);
    bool isCorner = (r == 1 && c == 1) || (r == 1 && c == M_global) ||
                    (r == N_global && c == 1) ||
                    (r == N_global && c == M_global);
    return onBorder && !isCorner;
  }
  static void Main() {
    int T = int.Parse(Console.ReadLine()!);
    while (T-- > 0) {
      long[] dimensions =
          Array.ConvertAll(Console.ReadLine()!.Split(), long.Parse);
      N_global = dimensions[0];
      M_global = dimensions[1];
      K_global = (int)dimensions[2];
      long fixedOddCount = 0;
      int fixedOddSumParity = 0;
      for (int i = 0; i < K_global; i++) {
        long[] inputs =
            Array.ConvertAll(Console.ReadLine()!.Split(), long.Parse);
        long r = inputs[0];
        long c = inputs[1];
        int color = (int)inputs[2];
        if (IsBorderNonCorner(r, c)) {
          fixedOddCount++;
          fixedOddSumParity = (fixedOddSumParity + color) % 2;
        }
      }
      // Total number of border non-corner cells
      long totalOddCount = (N_global >= 2 && M_global >= 2)
                               ? 2L * N_global + 2L * M_global - 8L
                               : 0;
      long variableOddCount = totalOddCount - fixedOddCount;
      long ans;
      if (variableOddCount > 0) {
        // When we have more free variables, power of 2 with exponent calculated
        long exp = ComputeExponent(N_global, M_global, K_global, true);
        ans = Power(2, exp);
      } else {
        // If no variable degrees are left, check parity of fixed degrees
        ans =
            fixedOddSumParity == 0
                ? Power(2, ComputeExponent(N_global, M_global, K_global, false))
                : 0;
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/codeForces/