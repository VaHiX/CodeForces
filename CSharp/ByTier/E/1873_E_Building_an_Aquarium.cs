// Problem: CF 1873 E - Building an Aquarium
// https://codeforces.com/contest/1873/problem/E

/*
 * Problem: Building an Aquarium
 * 
 * Algorithm: Binary Search on Answer
 * 
 * Time Complexity: O(n * log(max_height)) where n is the number of columns and max_height is up to 10^9
 * Space Complexity: O(n) for storing the column heights
 * 
 * The approach uses binary search on the possible height values of the tank.
 * For each candidate height h, we compute how much water is needed to fill all columns up to height h,
 * unless the column is already taller than h.
 * We then decide whether to increase or decrease the height based on whether the water requirement
 * exceeds the allowed limit x.
 */

using System;
using System.IO;
using System.Linq;
class Program {
  // Function to check if we can build a tank of height h using at most W units of water
  static bool CanTake(int[] vec, int h, long W) {
    long ct = 0;
    for (int i = 0; i < vec.Length; i++) {
      if (vec[i] < h) {
        ct += h - vec[i];
        if (ct > W)
          return false;
      }
    }
    return ct <= W;
  }
  
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    while (t > 0) {
      t--;
      string[] input = Console.ReadLine().Split();
      int n = int.Parse(input[0]);
      long W = long.Parse(input[1]);
      int[] vec = Console.ReadLine().Split().Select(int.Parse).ToArray();
      int low = 1, high = int.MaxValue;
      while (low <= high) {
        int mid = low + (high - low) / 2;
        if (CanTake(vec, mid, W)) {
          low = mid + 1;
        } else {
          high = mid - 1;
        }
      }
      Console.WriteLine(high);
    }
  }
}


// https://github.com/VaHiX/CodeForces/