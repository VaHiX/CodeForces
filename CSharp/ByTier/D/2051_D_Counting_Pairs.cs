// Problem: CF 2051 D - Counting Pairs
// https://codeforces.com/contest/2051/problem/D

/*
 * Problem: Counting Pairs
 * 
 * Purpose: 
 *   Given a sequence of integers and two bounds x and y,
 *   count the number of pairs (i,j) such that removing elements at positions i and j
 *   results in a sum of remaining elements between x and y inclusive.
 * 
 * Algorithms/Techniques:
 *   - Sorting + Binary Search for efficient range counting
 *   - Two-pointer technique with prefix sums
 * 
 * Time Complexity: O(n log n) per test case due to sorting and binary search operations.
 * Space Complexity: O(1) additional space, not counting input arrays.
 */

using System;
using System.Linq;
class Program {
  static string MyInput() { return Console.ReadLine().Trim(); }
  static long CountEle(long[] arr, int imax, long x, long y) {
    long i = Array.BinarySearch(arr, x);
    if (i < 0)
      i = ~i;
    if (i < arr.Length && arr[i] == x) {
      while (i > 0) {
        if (arr[i - 1] == x) {
          i = i - 1;
        } else
          break;
      }
    }
    long j = Array.BinarySearch(arr, y);
    if (j < 0)
      j = ~j;
    {
      while (j < arr.Length && arr[j] == y)
        j++;
    }
    return Math.Max(imax, j) - Math.Max(imax, i);
  }
  static void PairsOpt(long[] list, long x, long y) {
    long count = 0;
    int i = 0;
    Array.Sort(list); // Sort the array to enable binary search
    long sn = list.Sum(); // Total sum of all elements
    while (i < list.Length - 1) {
      long k = sn - list[i]; // Sum after removing element at index i
      // Count valid pairs where second element's value lies in range [k-y, k-x]
      long c1 = CountEle(list, i + 1, k - y, k - x);
      count += c1; // Add the number of such pairs to total count
      i++;
    }
    Console.WriteLine(count);
  }
  static void Main(string[] args) {
    long T = long.Parse(MyInput());
    for (long t = 0; t < T; t++) {
      long[] list1 = MyInput().Split().Select(long.Parse).ToArray();
      long[] list2 = MyInput().Split().Select(long.Parse).ToArray();
      PairsOpt(list2, list1[1], list1[2]); // Pass x and y as parameters
    }
  }
}


// https://github.com/VaHiX/codeForces/