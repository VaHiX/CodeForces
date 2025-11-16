// Problem: CF 2098 B - Sasha and the Apartment Purchase
// https://codeforces.com/contest/2098/problem/B

using System;
using System.Linq;
class Program {
  // Purpose: Determine the number of houses where Sasha can potentially buy an apartment.
  //          For each house, we check if it's possible to close at most k bars such that 
  //          the sum of distances to remaining bars is minimized.
  //          This is done by finding a subsegment of the sorted array of bar positions 
  //          that contains exactly (n - k) bars — i.e., we keep the optimal number of bars.
  //          The minimum possible sum f(x) for a house x is achieved when x is the median 
  //          of the kept bars. We compute the range [left, right] of such optimal positions.
  //          
  // Algorithm: 
  //   1. Sort the array of bar positions.
  //   2. Calculate how many bars must remain (rem = n - k).
  //   3. Find the leftmost and rightmost positions of the subarray of size rem.
  //   4. The difference between these positions gives the number of suitable houses.
  //          
  // Time Complexity: O(n log n) due to sorting; space complexity: O(1) (excluding input).
  static long ProcessTestCase(long n, long k, long[] arr) {
    Array.Sort(arr); // Sort the array to process bars in order
    long rem = n - k; // Number of bars that will remain open
    if (rem == 0)
      return 0; // No bars left to place => no valid houses
    // Calculate indices of the left and right bounds of the optimal subarray
    long leftIdx = (rem % 2 == 0) ? (rem / 2) - 1 : (rem - 1) / 2;
    long rightIdx = (rem % 2 == 0) ? (n - rem / 2) : (n - 1) - (rem - 1) / 2;
    return arr[rightIdx] - arr[leftIdx] + 1; // Count of valid houses
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      var nk = Console.ReadLine().Split().Select(long.Parse).ToArray();
      long n = nk[0], k = nk[1];
      long[] arr = Console.ReadLine().Split().Select(long.Parse).ToArray();
      long result = ProcessTestCase(n, k, arr);
      Console.WriteLine(result);
    }
  }
}

// https://github.com/VaHiX/CodeForces/