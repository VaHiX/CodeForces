// Problem: CF 1872 D - Plus Minus Permutation
// https://codeforces.com/contest/1872/problem/D

using System;
public class PlusMinusPermutation {
  /*
  **Problem Overview:**
  Given a permutation of integers from 1 to n, compute the score as the sum of elements at indices divisible by x, minus the sum of elements at indices divisible by y.
  
  **Algorithm Approach:**
  To maximize the score, we assign the largest elements to indices divisible by x (to increase the positive sum) and the smallest elements to indices divisible by y (to decrease the negative sum).
  
  **Key Observations:**
  - Use inclusion-exclusion principle to compute how many indices are divisible by x only, y only, or both.
  - For indices divisible by x only, assign the largest available numbers.
  - For indices divisible by y only, assign the smallest available numbers.
  - Use arithmetic progression formulas to compute sums efficiently.

  **Time Complexity:** O(t) where t is the number of test cases. GCD calculation is constant time.
  **Space Complexity:** O(1) - only using a constant amount of extra memory.
  */
  
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]); // Length of permutation
      int x = int.Parse(parts[1]); // First divisor
      int y = int.Parse(parts[2]); // Second divisor
      
      long lcm = (long)x * y / Gcd(x, y); // Compute LCM(x, y)
      
      // Count numbers divisible by both x and y
      int numDivXAndY = Convert.ToInt32(n / lcm);
      
      // Count numbers divisible by x only
      int numDivXOnly = n / x - numDivXAndY;
      
      // Count numbers divisible by y only
      int numDivYOnly = n / y - numDivXAndY;
      
      // Compute sum of largest 'numDivXOnly' numbers for positive contribution
      long sumPos = numDivXOnly > 0
                        ? (long)numDivXOnly * (2 * n - numDivXOnly + 1) / 2
                        : 0;
                        
      // Compute sum of smallest 'numDivYOnly' numbers for negative contribution  
      long sumNeg =
          numDivYOnly > 0 ? (long)numDivYOnly * (numDivYOnly + 1) / 2 : 0;
      
      long ans = sumPos - sumNeg; // Final score
      Console.WriteLine(ans);
    }
  }
  
  // Calculate greatest common divisor using Euclidean algorithm
  private static int Gcd(int x, int y) {
    while (y > 0) {
      int tmp = x % y;
      x = y;
      y = tmp;
    }
    return x;
  }
}

// https://github.com/VaHiX/CodeForces/