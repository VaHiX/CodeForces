// Problem: CF 2106 B - St. Chroma
// https://codeforces.com/contest/2106/problem/B

/*
B. St. Chroma
Algorithms/Techniques: Greedy approach to maximize occurrences of a specific MEX value by constructing a permutation strategically.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the result array

Given a permutation p of length n that contains every integer from 0 to n-1,
and a strip of n cells, St. Chroma will paint the i-th cell of the strip in 
the color MEX(p1, p2, ..., pi). The task is to construct a permutation such that
the number of cells painted with color x is maximized.
*/

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) { // Process each test case
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n and x
      var n = int.Parse(line[0]);
      var x = int.Parse(line[1]);
      getAns(n, x); // Compute and output the result
    }
  }
  
  static void getAns(int n, int x) {
    if (x == 0) { // Special case: if we want to maximize color 0
      // We need to ensure that MEX starts with 0 as early as possible,
      // which can be achieved by placing 0 at the beginning.
      var ans = Enumerable.Range(0, n).ToArray(); // Create range [0,1,...,n-1]
      Array.Reverse(ans); // Reverse it to get [n-1,n-2,...,0]
      Console.WriteLine(string.Join(" ", ans));
    } else { // General case: maximize color x where x > 0
      var ans = Enumerable.Range(0, x).ToList(); // Start with [0,1,...,x-1]
      for (int i = n - 1; i >= x; i--) // Then append from n-1 down to x
        ans.Add(i);
      Console.WriteLine(string.Join(" ", ans));
    }
  }
}


// https://github.com/VaHiX/codeForces/