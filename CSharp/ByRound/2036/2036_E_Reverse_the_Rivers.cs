// Problem: CF 2036 E - Reverse the Rivers
// https://codeforces.com/contest/2036/problem/E

/*
 * Problem: E. Reverse the Rivers
 * 
 * Purpose: This program processes a 2D grid representing countries and regions,
 *          where each region has a value. After applying bitwise OR operations
 *          along rows (countries), it answers queries about which country satisfies
 *          given conditions on region values.
 *
 * Algorithms:
 *   - Preprocessing: Compute prefix ORs for each column to efficiently query
 *                     cumulative OR values per country.
 *   - Queries: For each query, perform binary search using LowerBound and UpperBound
 *              functions to find valid range of countries satisfying all constraints.
 * 
 * Time Complexity: O(n * k + q * m * log(n)) where:
 *   - n: number of countries
 *   - k: number of regions per country  
 *   - q: number of queries
 *   - m: average number of requirements per query
 *   
 * Space Complexity: O(n * k) for storing the grid and prefix ORs.
 */

using static System.Math;
using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    string[] line = Console.ReadLine().Trim().Split(' ');
    var h = int.Parse(line[0]); // number of countries
    var w = int.Parse(line[1]); // number of regions per country
    var q = int.Parse(line[2]); // number of queries
    getAns(h, w, q);
  }
  
  static void getAns(int h, int w, int q) {
    var aa = new int [w][]; // Transposed grid: rows = regions, cols = countries
    for (int i = 0; i < w; i++)
      aa[i] = new int[h];
    
    // Read input and populate transposed array
    for (int i = 0; i < h; i++) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      for (int j = 0; j < w; j++)
        aa[j][i] = int.Parse(line[j]); // Fill column-wise
    }
    
    // Preprocessing: Compute prefix OR for each region (column)
    for (int i = 0; i < w; i++) {
      for (int j = 1; j < h; j++) {
        aa[i][j] |= aa[i][j - 1]; // Build prefix OR from left to right
      }
    }
    
    // Process queries
    for (int i = 0; i < q; i++) {
      var m = int.Parse(Console.ReadLine().Trim()); // number of constraints
      var L = 0; // Lower bound of valid countries
      var r = h - 1; // Upper bound of valid countries
      
      for (int j = 0; j < m; j++) {
        string[] line = Console.ReadLine().Trim().Split(' ');
        var a = int.Parse(line[0]) - 1; // Region index (0-based)
        var b = line[1]; // Constraint operator ('<' or '>')
        var c = int.Parse(line[2]); // Value threshold
        
        if (b == ">") {
          // Find smallest country such that b[i][a] > c
          var p = UpperBound(aa[a], c); // Returns index of first element > c
          L = Max(L, p); // Adjust lower bound
        } else {
          // Find smallest country such that b[i][a] < c
          var p = LowerBound(aa[a], c); // Returns index of first element >= c
          r = Min(r, p - 1); // Adjust upper bound
        }
      }
      
      if (L > r)
        Console.WriteLine(-1);
      else
        Console.WriteLine(L + 1); // Output country number as 1-indexed
    }
  }
  
  static int LowerBound<T>(T[] arr, int start, int end, T value,
                           IComparer<T> comparer) {
    var low = start;
    var high = end;
    while (low < high) {
      var mid = (high + low) / 2; // Midpoint computation
      if (comparer.Compare(arr[mid], value) < 0)
        low = mid + 1; // Move to right half
      else
        high = mid; // Move to left half including mid
    }
    return low;
  }
  
  static int LowerBound<T>(T[] arr, T value)
      where T : IComparable => LowerBound(arr,
                0,
                arr.Length,
                value,
                Comparer<T>.Default);
                
  static int UpperBound<T>(T[] arr, int start, int end, T value,
                           IComparer<T> comparer) {
    var low = start;
    var high = end;
    while (low < high) {
      var mid = (high + low) / 2; // Midpoint computation
      if (comparer.Compare(arr[mid], value) <= 0)
        low = mid + 1; // Move to right half
      else
        high = mid; // Move to left half excluding mid
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