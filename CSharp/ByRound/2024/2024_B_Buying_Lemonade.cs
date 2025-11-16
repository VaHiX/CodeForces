// Problem: CF 2024 B - Buying Lemonade
// https://codeforces.com/contest/2024/problem/B

/*
 * Problem: Buying Lemonade
 * 
 * Purpose:
 *   Given a vending machine with 'n' slots and initial amounts of lemonade cans in each slot,
 *   determine the minimum number of button presses to guarantee at least 'k' cans.
 * 
 * Algorithm:
 *   - Sort the array of can counts in ascending order.
 *   - Use a greedy approach to calculate how many total presses are needed to guarantee
 *     enough cans, based on the smallest available slots first.
 * 
 * Time Complexity: O(n log n) due to sorting, where n is the number of slots.
 * Space Complexity: O(n) for storing auxiliary arrays.
 */

using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n and k
      var n = int.Parse(line[0]);
      var k = int.Parse(line[1]);
      line = Console.ReadLine().Trim().Split(' '); // Read array of cans per slot
      var a = Array.ConvertAll(line, long.Parse); // Convert to long array
      getAns(n, k, a); // Call solver function
    }
  }

  static void getAns(int n, int k, long[] a) {
    Array.Sort(a); // Sort the array in ascending order to apply greedy approach
    
    var b = new long[n]; // b[i] represents how many additional cans we can get if we press button i
    b[0] = a[0] * n; // For first element: all buttons pressable, so multiply by n
    for (int i = 1; i < n; i++)
      b[i] = (a[i] - a[i - 1]) * (n - i); // Contribution to unique cans from this slot difference
    
    var c = new long[n]; // Cumulative sum of b array to track total cans obtained
    c[0] = b[0];
    if (c[0] >= k) {
      Console.WriteLine(k); // Early return if first group already suffices
      return;
    }
    for (int i = 1; i < n; i++) {
      c[i] = c[i - 1] + b[i]; // Accumulating the number of cans guaranteed
      if (c[i] >= k) {
        Console.WriteLine(k + i); // Minimum presses needed to guarantee k cans
        return;
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/