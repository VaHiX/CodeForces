// Problem: CF 2148 D - Destruction of the Dandelion Fields
// https://codeforces.com/contest/2148/problem/D

/*
 * Problem: D. Destruction of the Dandelion Fields
 * 
 * Purpose:
 *   Farmer John wants to maximize the number of dandelions he cuts by visiting n fields in an optimal order.
 *   The lawnmower toggles its state when visiting a field with an odd number of dandelions.
 *   If the lawnmower is on, all dandelions in that field are cut; otherwise, none are cut.
 * 
 * Algorithm:
 *   - Separate even and odd numbers from input.
 *   - For even numbers: sum them all (they contribute directly to result since lawnmower state doesn't affect).
 *   - For odd numbers:
 *     - Sort in descending order.
 *     - Take the first (count + 1) / 2 elements (this ensures maximum contribution to total while keeping the lawnmower on).
 *   - Add even sum + odd sum (maximized odd subset).
 * 
 * Time Complexity: O(n log n) due to sorting odd numbers; overall due to multiple test cases.
 * Space Complexity: O(n) for storing odds list and input array.
 */

using System;
using System.Collections.Generic;
using System.Linq;

public class Solution {
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      var numbers = Console.ReadLine().Split().Select(long.Parse).ToArray();
      
      long sumEven = 0; // Sum of all even numbers
      var odds = new List<long>(); // Store all odd numbers
      
      foreach (var a in numbers) {
        if (a % 2 == 0)
          sumEven += a;
        else
          odds.Add(a);
      }
      
      if (odds.Count == 0) {
        Console.WriteLine(0);
        continue;
      }
      
      // Sort odd numbers in descending order to maximize contribution
      odds.Sort((x, y) => y.CompareTo(x));
      
      // Take ceil(count / 2) elements of biggest odds to ensure lawnmower turns on and stays on
      int take = (odds.Count + 1) / 2;
      long sumOdd = 0;
      
      for (int i = 0; i < take; i++) {
        sumOdd += odds[i];
      }
      
      Console.WriteLine(sumEven + sumOdd);
    }
  }
}


// https://github.com/VaHiX/codeForces/