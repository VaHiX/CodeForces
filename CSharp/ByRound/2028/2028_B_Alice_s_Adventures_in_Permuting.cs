// Problem: CF 2028 B - Alice's Adventures in Permuting
// https://codeforces.com/contest/2028/problem/B

/*
B. Alice's Adventures in Permuting
Algorithms/Techniques: Mathematical analysis, simulation with optimization

Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem involves transforming an array defined by a formula into a permutation.
The key observations are:
- The array starts as [c, b+c, 2*b+c, ..., (n-1)*b+c]
- Each operation replaces the maximum element with the MEX of the array
- We analyze when this transformation is possible and how many operations are needed

For small n or special cases like b=0, we handle directly.
Otherwise, we compute based on the arithmetic progression nature of the array,
determining how many steps it takes to convert into a permutation.

*/

using System;
class Program {
  static void Main() {
    long t = long.Parse(Console.ReadLine());
    while (t-- > 0) {
      string[] input = Console.ReadLine().Split();
      long n = long.Parse(input[0]);
      long b = long.Parse(input[1]);
      long c = long.Parse(input[2]);
      
      if (c >= n) { // If c is large enough, the first element is >= n
        Console.WriteLine(n); // Already invalid permutation
        continue;
      }
      
      if (b == 0) { // Special case: all elements are same
        if (n - c > 2)
          Console.WriteLine(-1); // Impossible to form a valid permutation
        else
          Console.WriteLine(n - 1); // Only one operation needed if n-c <= 2
        continue;
      }
      
      // Calculate the number of operations needed using arithmetic progression logic
      long last = (n - 1 - c) / b; // How many elements before reaching n
      Console.WriteLine(n - 1 - last); // Final result
    }
  }
}


// https://github.com/VaHiX/codeForces/