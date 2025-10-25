// Problem: CF 2092 C - Asuna and the Mosquitoes
// https://codeforces.com/contest/2092/problem/C

/*
C. Asuna and the Mosquitoes

Problem Description:
Asuna receives n towers with heights a[i]. She can perform operations where she takes two towers i and j such that a[i] + a[j] is odd and a[i] > 0, then decreases a[i] by 1 and increases a[j] by 1. The goal is to maximize the maximum height among all towers after any number of such operations.

Algorithm:
- Count how many numbers are odd in the array.
- If all elements are even or all are odd, the maximum value cannot be increased further; return max element.
- Otherwise, we can perform operations to transfer values between towers, and the new maximum becomes sum - number of odds + 1.

Time Complexity: O(n)
Space Complexity: O(1)

*/

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read number of towers
      string[] line = Console.ReadLine().Trim().Split(' '); // Read tower heights
      var a = Array.ConvertAll(line, long.Parse); // Convert to long array
      getAns(n, a); // Process and output the result
    }
  }
  
  static void getAns(int n, long[] a) {
    var odd = a.Count(x => x % 2 == 1); // Count how many numbers are odd
    
    if (odd == 0 || odd == n) { // If all even or all odd
      Console.WriteLine(a.Max()); // Return maximum directly
      return;
    }
    
    // Otherwise, compute based on sum and count of odds
    Console.WriteLine(a.Sum() - odd + 1);
  }
}


// https://github.com/VaHiX/codeForces/