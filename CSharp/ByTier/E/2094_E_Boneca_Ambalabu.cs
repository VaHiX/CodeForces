// Problem: CF 2094 E - Boneca Ambalabu
// https://codeforces.com/contest/2094/problem/E

/* 
E. Boneca Ambalabu
Purpose: Find the maximum value of sum of XORs (a[k] XOR a[i]) for all i in the array,
         where k ranges from 1 to n. This is solved using bit manipulation and greedy approach.
Algorithms/Techniques: Bitwise manipulation, prefix counting, greedy selection.
Time Complexity: O(30 * n) per test case, where n is the size of array.
Space Complexity: O(30) for auxiliary array b, i.e., O(1) since 30 is constant.

The approach:
- For each bit position (from 0 to 29), count how many numbers in the array have that bit set.
- For each element in the array, compute a score by trying to maximize the sum of XORs,
  by deciding whether to set or unset each bit in the XOR result, based on counts from b[].
This greedy choice is made by evaluating contribution of each bit:
- If setting bit leads to higher sum (by maximizing number of 1s), we prefer that.
*/

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read size of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read the array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      getAns(n, a); // Process and find answer
    }
  }
  
  static long calc(int n, int t, int[] b) {
    var res = 0L;
    for (int i = 0; i < 30; i++) {
      // If the i-th bit is set in current number 't'
      if (((t >> i) & 1) == 1)
        // Add contribution of setting this bit: (n - b[i]) gives count where other numbers don't have this bit
        res += (n - b[i]) * (1L << i);
      else
        // Otherwise, add contribution where we expect the bit to be set in result
        res += b[i] * (1L << i);
    }
    return res;
  }
  
  static void getAns(int n, int[] a) {
    var b = new int[30]; // Count of numbers having each bit set at index i
    
    foreach (var x in a) {
      for (int i = 0; i < 30; i++) {
        if (((x >> i) & 1) == 1)
          b[i]++; // Increment count for this bit position
      }
    }
    
    var ans = 0L;
    foreach (var x in a)
      ans = Max(ans, calc(n, x, b)); // Try every element as k and compute max sum
    
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/