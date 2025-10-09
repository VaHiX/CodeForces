// Problem: CF 2014 C - Robin Hood in Town
// https://codeforces.com/contest/2014/problem/C

/*
 * Problem: C. Robin Hood in Town
 * 
 * Purpose:
 *   Given an array of wealth values for n people, we need to find the minimum amount of gold 
 *   that must be added to the richest person to make more than half of the population unhappy.
 *   A person is unhappy if their wealth is strictly less than half of the average wealth.
 *   The solution uses binary search on the answer combined with a greedy check function.
 *
 * Algorithm:
 *   - For each test case, sort the array.
 *   - Binary search on the value of x (extra gold added to the richest).
 *   - For a given x, simulate the increase in wealth and compute whether more than n/2 people are unhappy.
 *   - The check function uses upper/lower bound operations to efficiently determine if a valid configuration exists.
 *
 * Time Complexity:
 *   O(n log(max_a) * log n), where max_a is the maximum wealth value (up to 10^6).
 *   Sorting dominates in many cases, but binary search over x with check function costs log n per step.
 *
 * Space Complexity:
 *   O(n) due to storage of input and sorting operations.
 */

using System.Collections.Generic;
using System.Linq;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, long.Parse);
      getAns(n, a);
    }
  }

  // Check if adding 't' gold to the richest person makes over half the population unhappy
  static bool check(int n, long[] a, long sum, long t) {
    a[n - 1] += t; // Add extra gold to the richest person
    var w = (sum + t) / (2 * n); // Half of the average wealth 
    var p = UpperBound(a, w); // Find first index where value > w
    a[n - 1] -= t; // Restore original wealth

    if (p > 0) {
      if (sum + t == n * 2 * a[p - 1]) { // If balance is exact
        var p2 = LowerBound(a, a[p - 1]); // First occurrence of that value
        return p2 > n - p2; // Check condition for unhappy count
      }
    }
    return p > n - p; // Check if more than half are unhappy
  }

  static void getAns(int n, long[] a) {
    Array.Sort(a); // Sort array to facilitate binary search and bound operations
    var sum = a.Sum(); // Total wealth 
    var t = check(n, a, sum, 0); // Check base case (no extra gold)
    if (t) {
      Console.WriteLine(0);
      return;
    }
    
    var tt = long.MaxValue - sum - a[n - 1]; // Max possible increase
    var t2 = check(n, a, sum, tt); // Check upper bound 
    if (!t2) {
      Console.WriteLine(-1);
      return;
    }

    var ok = tt; // Binary search range
    var ng = 0L;
    while (ok - ng > 1) {
      var mid = ng + (ok - ng) / 2;
      if (check(n, a, sum, mid)) // If this x works, try smaller
        ok = mid;
      else
        ng = mid; // Otherwise, we need to go larger
    }
    Console.WriteLine(ok);
  }

  // Generic lower bound implementation for sorted array
  static int LowerBound<T>(T[] arr, int start, int end, T value,
                           IComparer<T> comparer) {
    var low = start;
    var high = end;
    while (low < high) {
      var mid = (high + low) / 2;
      if (comparer.Compare(arr[mid], value) < 0)
        low = mid + 1;
      else
        high = mid;
    }
    return low;
  }

  static int LowerBound<T>(T[] arr, T value)
      where T : IComparable => LowerBound(arr,
                0,
                arr.Length,
                value,
                Comparer<T>.Default);

  // Generic upper bound implementation for sorted array
  static int UpperBound<T>(T[] arr, int start, int end, T value,
                           IComparer<T> comparer) {
    var low = start;
    var high = end;
    while (low < high) {
      var mid = (high + low) / 2;
      if (comparer.Compare(arr[mid], value) <= 0)
        low = mid + 1;
      else
        high = mid;
    }
    return low;
  }

  static int UpperBound<T>(T[] arr, T value)
      where T : IComparable => UpperBound(arr,
                0,
                arr.Length,
                value,
                Comparer<T>.Default);
}


// https://github.com/VaHiX/codeForces/