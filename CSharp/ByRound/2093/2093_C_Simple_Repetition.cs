// Problem: CF 2093 C - Simple Repetition
// https://codeforces.com/contest/2093/problem/C

/*
C. Simple Repetition
time limit per test1 second
memory limit per test256 megabytes

Pasha loves prime numbers! Once again, in his attempts to find a new way to generate prime numbers, he became interested in an algorithm he found on the internet:
To obtain a new number y, repeat k times the decimal representation of the number x (without leading zeros).
For example, for x=52 and k=3, we get y=525252, and for x=6 and k=7, we get y=6666666.

The task is to determine if the resulting number y is prime.

Algorithm:
- For each test case:
  - If x == 1, then:
    - If k == 2, output "YES" (since 11 is prime)
    - Else, output "NO"
  - Otherwise:
    - Check if x is prime.
    - If x is prime AND k == 1, output "YES", otherwise "NO"

Time Complexity: O(sqrt(x) * t) where x is the maximum value of x and t is number of test cases.
Space Complexity: O(1) - only using constant extra space (excluding input/output).

*/

using System;
public class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      string[] s = Console.ReadLine().Split(); // Read x and k from input
      int x = int.Parse(s[0]); // Parse x
      int k = int.Parse(s[1]); // Parse k
      if (x == 1)
        Console.WriteLine((k == 2) ? "YES" : "NO"); // Special case: only 11 is prime in form 11..1
      else
        Console.WriteLine((k == 1 && IsPrime(x)) ? "YES" : "NO"); // If k=1 and x is prime, result is prime
    }
  }
  static bool IsPrime(int x) { // Function to check if a number is prime
    if (x == 1)
      return false; // 1 is not considered prime
    for (int i = 2; i * i <= x; i++) // Check divisibility up to sqrt(x)
      if (x % i == 0)
        return false;
    return true;
  }
}


// https://github.com/VaHiX/codeForces/