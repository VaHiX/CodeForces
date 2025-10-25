// Problem: CF 2040 B - Paint a Strip
// https://codeforces.com/contest/2040/problem/B

/*
 * Problem: B. Paint a Strip
 * Algorithm: Precompute minimum operations needed for each n up to 10^5
 * Time Complexity: O(1) per query after O(n) preprocessing
 * Space Complexity: O(n)
 * 
 * The approach uses dynamic programming to precompute the minimal number of
 * Type-1 operations required for arrays of length up to 10^5.
 * 
 * For each position i, we compute the minimum number of Type-1 operations
 * such that we can fill an array of size i using the allowed operations.
 * The recurrence relation is based on how quickly we can cover a segment
 * using Type-2 operations after placing some initial(Type-1) 1s.
 * 
 * For small n, direct computation or lookup suffices.
 */

using System;
public class hello {
  public static int[] a; // Array to store precomputed values
  
  static void Main() {
    a = new int[17]; // Precompute up to index 16
    a[0] = 1; // Base case: 1 operation for n=1
    
    // Build the array using recurrence relation:
    // a[i] = 2*a[i-1] + 2
    for (int i = 1; i <= 16; i++) {
      a[i] = (a[i - 1] * 2 + 2);
    }
    
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read current n
      getAns(n); // Find and print result for this n
    }
  }
  
  // Method to find minimum operations for given n
  static void getAns(int n) {
    for (int i = 0; i < 17; i++) {
      if (a[i] >= n) { // Find first index where precomputed value >= n
        Console.WriteLine(i + 1); // Output number of operations needed
        return;
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/