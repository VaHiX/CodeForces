// Problem: CF 2050 B - Transfusion
// https://codeforces.com/contest/2050/problem/B

/*
B. Transfusion
Algorithm: Greedy Simulation with Prefix Differences
Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input storage

The problem allows modifying elements at positions i-1 and i+1 relative to position i,
so the goal is to make all elements equal by ensuring that we can redistribute values
to balance out the array. The key idea is to simulate the process from left to right,
keeping track of how much each element needs to be adjusted with respect to a target value.

We check if total sum is divisible by n to determine if equal distribution is possible.
Then, for each index (except last two), we apply operations greedily to ensure
all elements eventually reach the target value. The final check validates whether 
the last two elements also match the target value.
*/

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read size of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements
      var a = Array.ConvertAll(line, long.Parse); // Convert to long array
      getAns(n, a); // Process the current test case
    }
  }
  static void getAns(int n, long[] a) {
    var asum = a.Sum(); // Calculate total sum of elements
    if (asum % n != 0) { // If sum is not divisible by n, impossible to equalize
      Console.WriteLine("NO");
      return;
    }
    var t = asum / n; // Target value for each element
    for (int i = 1; i < n - 1; i++) { // Traverse from index 1 to n-2
      if (a[i - 1] > t) { // If previous element exceeds target
        var d = a[i - 1] - t; // Compute deficit
        a[i - 1] = t; // Bring it down to target
        a[i + 1] += d; // Add deficit to next element
      } else if (a[i - 1] < t) { // If previous element is below target
        var d = t - a[i - 1]; // Compute surplus
        a[i - 1] = t; // Bring it up to target
        a[i + 1] -= d; // Subtract surplus from next element
      }
    }
    // Final check: last two elements should ideally be at the target value
    Console.WriteLine(a[n - 2] == t && a[n - 1] == t ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/