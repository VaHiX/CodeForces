// Problem: CF 2014 B - Robin Hood and the Major Oak
// https://codeforces.com/contest/2014/problem/B

/*
B. Robin Hood and the Major Oak

Purpose:
This program determines whether the number of leaves on the Major Oak tree in year n is even or odd.
The tree grows i new leaves in the i-th year, and each leaf lasts for k years.
We are to check if the total number of leaves in year n is even.

Algorithms/Techniques:
- Mathematical analysis of leaf growth pattern
- Modular arithmetic to determine parity (even/odd)
- Optimization to avoid simulating all years due to large constraints (n up to 10^9)

Time Complexity: O(1) - Constant time per test case, as we directly compute the result using mathematical formula.
Space Complexity: O(1) - Only constant extra space is used.

Input Format:
- First line contains t (number of test cases)
- Each test case has two integers n and k

Output Format:
- "YES" if number of leaves in year n is even, otherwise "NO"
*/

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n and k from input
      var n = int.Parse(line[0]); // Current year
      var k = int.Parse(line[1]); // Number of years leaves last
      // Calculate number of odd years in the range [max(1, n-k+1), n]
      // This is the count of years where leaves were born and are still alive in year n
      var odd = n % 2 == 0 ? k / 2 : (k + 1) / 2; 
      Console.WriteLine(odd % 2 == 0 ? "YES" : "NO"); // Output YES if count of odd years is even, otherwise NO
    }
  }
}


// https://github.com/VaHiX/codeForces/