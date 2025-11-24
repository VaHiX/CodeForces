// Problem: CF 2112 C - Coloring Game
// https://codeforces.com/contest/2112/problem/C

/*
C. Coloring Game
Algorithm: Three-pointer technique with binary search and lower bound search
Time Complexity: O(n^3) per test case due to nested loops and binary search
Space Complexity: O(n) for storing the input array

The problem involves determining how many ways Alice can choose 3 elements such that no matter which element Bob chooses to color blue (including recoloring a red one), the sum of the red elements remains strictly greater than the blue element.

Approach:
1. For each possible pair (i, j) where i < j, we compute their sum.
2. Using binary search, find the smallest index k such that nums[k] > sum.
3. Find valid third element in range [k, n-1] such that red sum > blue element value.
4. Count valid combinations using lower bound and binary search techniques.

The code uses a combination of brute-force for the first two elements and efficient searching for valid third element to ensure all cases are covered.
*/

using System;
using System.Linq;
using System.Collections.Generic;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = (int.Parse)(Console.ReadLine());
      var nums = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
      long ans = 0;
      for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
          int val = nums[i] + nums[j];
          int lower = GetLowerBound(nums, j + 1, n - 1, val);
          if (lower == j)
            continue;
          // Binary search for valid third element to ensure sum > blue element
          int k = BinarySearch(nums, val, j + 1, lower, nums[n - 1]);
          if (k <= lower) {
            ans += lower - k + 1;
          }
        }
      }
      Console.WriteLine(ans);
    }
  }
  static int GetLowerBound(int[] nums, int low, int high, int tar) {
    int ans = low - 1;
    while (low <= high) {
      int mid = (low + high) / 2;
      if (nums[mid] < tar) {
        ans = mid;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
    return ans;
  }
  static int BinarySearch(int[] nums, int sum, int low, int high, int max) {
    int ans = high + 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (nums[mid] + sum > max) { // Adjusted condition to check valid configuration
        ans = mid;
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }
    return ans;
  }
}


// https://github.com/VaHiX/codeForces/