// Problem: CF 875 A - Classroom Watch
// https://codeforces.com/contest/875/problem/A

/*
 * Purpose: This program finds all possible values of x such that x plus the sum of its digits equals a given number n.
 * Algorithm: 
 *   - For a given n, we iterate through potential values of x from n down to a calculated lower bound.
 *   - For each x, compute the sum of its digits.
 *   - Check if x + digitSum == n.
 *   - Collect all valid x values.
 * 
 * Time Complexity: O(d * sqrt(n)) where d is the number of digits in n.
 * Space Complexity: O(k) where k is the number of valid x values found.
 */
using System;
using System.Collections.Generic;
public class Program {
  public static void Main(string[] args) {
    int n = Convert.ToInt32(Console.ReadLine());
    List<int> results = new List<int>();
    int checks = 0;
    int digits = n.ToString().Length;
    for (int i = 1; i <= digits; i++) {
      checks += 9; // Estimate upper bound for digit sum
    }
    if (n - checks < 0)
      checks = 1; // Set lower bound to 1 if calculated value is less than 1
    else
      checks = n - checks; // Calculate a reasonable starting point to reduce search space
    
    for (int i = n; i >= checks; i--) {
      int b = n - i; // b represents the digit sum we're checking for
      string number = i.ToString();
      int sum = 0;
      for (int j = 0; j < number.Length; j++) {
        sum += (Convert.ToInt32(number[j] - 48)); // Extract digit and add to sum
      }
      if (sum == b)
        results.Add(i); // If match, add to results
    }
    Console.WriteLine(results.Count);
    results.Sort();
    foreach (int result in results)
      Console.WriteLine(result);
  }
}


// https://github.com/VaHiX/CodeForces/