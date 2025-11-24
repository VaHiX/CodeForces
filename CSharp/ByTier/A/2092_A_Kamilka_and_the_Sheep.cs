// Problem: CF 2092 A - Kamilka and the Sheep
// https://codeforces.com/contest/2092/problem/A

/*
Problem: A. Kamilka and the Sheep
Algorithm/Techniques: Brute force with GCD calculation
Time Complexity: O(n^2 * log(max_val)) per test case, where n is the number of sheep and max_val is the maximum beauty level.
Space Complexity: O(n) for storing the array of sheep beauty levels.

The problem involves choosing a value d such that when added to all sheep's beauty levels,
the GCD of any two sheep's final beauty levels is maximized. 
Since we can choose d optimally, we explore different values of d and compute the maximum GCD.
However, given the constraints, the approach described here does not require choosing d explicitly;
it just computes the difference between max and min in the original array to determine an optimal scenario,
as the problem reduces to finding two numbers whose GCD is maximized after adding a fixed constant d.

In this code, we read input, compute minimum and maximum of the array (which represents one possible best case),
and output the difference.
*/

using System;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()!); // Read number of test cases
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()!); // Read number of sheep
      int[] numbers = 
          Console.ReadLine()!.Split(' ', StringSplitOptions.RemoveEmptyEntries)
              .Select(int.Parse)
              .ToArray(); // Read beauty levels and convert to integer array
      var (minVal, maxVal) = (numbers.Min(), numbers.Max()); // Find min and max values
      Console.WriteLine(maxVal - minVal); // Output the difference (max GCD achieved in optimal d case)
    }
  }
}


// https://github.com/VaHiX/codeForces/