// Problem: CF 2022 B - Kar Salesman
// https://codeforces.com/contest/2022/problem/B

/*
 * Problem: B. Kar Salesman
 * Purpose: Determine the minimum number of customers needed to sell all cars,
 *          where each customer can buy at most x cars from different models.
 * 
 * Algorithm:
 * - For each test case, calculate two values:
 *   1. Minimum customers based on total cars and x (ceiling division).
 *   2. Minimum customers based on the maximum number of cars for any single model.
 * - Return the maximum of these two values.
 * 
 * Time Complexity: O(n) per test case, where n is the number of car models.
 * Space Complexity: O(1), excluding input storage.
 */

using System;
using System.Linq;
public static class Solution {
  public static long MinCustomers(int n, int x, long[] a) {
    // Calculate total number of cars across all models
    long totalCars = a.Sum();
    
    // Minimum customers needed if we distribute all cars optimally (ceiling of total / x)
    long minCustomersFromTotal = (long)Math.Ceiling((double)totalCars / x);
    
    // Minimum customers needed if one customer can only buy up to x cars, 
    // so the model with the most cars dictates at least one customer per max model
    long minCustomersFromMaxModel = a.Max();
    
    // Return the larger of the two values as the final answer
    return Math.Max(minCustomersFromTotal, minCustomersFromMaxModel);
  }
}
public class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      string[] header = Console.ReadLine().Split(
          new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
      int n = int.Parse(header[0]);
      int x = int.Parse(header[1]);
      string[] parts = Console.ReadLine().Split(
          new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
      long[] a = Array.ConvertAll(parts, long.Parse);
      long result = Solution.MinCustomers(n, x, a);
      Console.WriteLine(result);
    }
  }
}


// https://github.com/VaHiX/codeForces/