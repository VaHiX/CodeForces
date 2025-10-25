// Problem: CF 1873 F - Money Trees
// https://codeforces.com/contest/1873/problem/F

/*
 * Problem: F. Money Trees
 * Algorithm: Sliding Window + Segmentation
 * Time Complexity: O(n) for each test case, where n is the number of trees.
 * Space Complexity: O(n) for storing the input arrays and temporary subarrays.
 *
 * Approach:
 * 1. For each valid contiguous subarray where every height is divisible by the next,
 *    we compute the maximum fruits that can be collected without exceeding k.
 * 2. We use a sliding window technique to find the maximum length of such subarrays.
 * 3. We segment the array into valid contiguous subarrays based on divisibility condition,
 *    then apply sliding window on each segment to maximize the length under fruit constraint.
 */

using System;
using System.Collections.Generic;
using System.Linq;

class Program {
  // Function to find maximum length of subarray with sum <= x using sliding window
  static int FindSubarrayLength(List<long> arr, long x) {
    int left = 0, right = 0;
    long currentSum = 0;
    int result = 0;
    
    while (right < arr.Count) {
      currentSum += arr[right]; // Add current element to window
      
      // Shrink window from left while sum exceeds x
      while (currentSum > x) {
        currentSum -= arr[left];
        left += 1;
      }
      
      right += 1;
      result = Math.Max(result, right - left); // Update maximum length
    }
    
    return result;
  }
  
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    
    while (t > 0) {
      t--;
      
      string[] input = Console.ReadLine().Split();
      long n = long.Parse(input[0]);
      long k = long.Parse(input[1]);
      
      List<long> appleArr = Console.ReadLine().Split().Select(long.Parse).ToList();
      List<long> heightArr = Console.ReadLine().Split().Select(long.Parse).ToList();
      
      long pr = 0; // Start index of current valid segment
      long result = 0;
      long hPrev = -1; // Previous height to check divisibility
      
      for (long i = 0; i < n; i++) {
        long current = heightArr[(int)i];
        long next = (i == n - 1) ? (current + 1) : heightArr[(int)(i + 1)];
        
        // If current height is not divisible by next height, end current segment
        if (current % next != 0) {
          List<long> sub = appleArr.GetRange((int)pr, (int)(i - pr + 1));
          pr = i + 1;
          long temp = FindSubarrayLength(sub, k);
          result = Math.Max(result, temp);
        }
      }
      
      // Handle the last segment
      if (pr < n) {
        List<long> lastSub = appleArr.GetRange((int)pr, (int)(n - pr));
        long temp = FindSubarrayLength(lastSub, k);
        result = Math.Max(result, temp);
      }
      
      Console.WriteLine(result);
    }
  }
}


// https://github.com/VaHiX/CodeForces/