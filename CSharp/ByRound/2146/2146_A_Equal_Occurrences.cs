// Problem: CF 2146 A - Equal Occurrences
// https://codeforces.com/contest/2146/problem/A

/*
 * Problem: Equal Occurrences
 * Algorithm/Technique: Frequency counting and brute-force optimization
 * Time Complexity: O(n^2) where n is the length of array a
 * Space Complexity: O(n) for storing frequency map
 * 
 * Description:
 * Given a non-decreasing array of integers, find the length of the longest balanced subsequence.
 * A balanced subsequence is one where all elements appear with the same frequency.
 * 
 * Approach:
 * 1. Count the frequency of each element in the array.
 * 2. For each possible frequency k (from 1 to max frequency), count how many distinct elements have frequency >= k.
 * 3. The maximum value of (count * k) across all k gives the answer.
 * 
 * Example:
 * Input: [1, 1, 4, 4, 4]
 * Frequencies: {1: 2, 4: 3}
 * For k=1: count = 2 (elements 1 and 4 have frequency >= 1), score = 2*1 = 2
 * For k=2: count = 2 (elements 1 and 4 have frequency >= 2), score = 2*2 = 4
 * For k=3: count = 1 (only element 4 has frequency >= 3), score = 1*3 = 3
 * Answer = max(2,4,3) = 4
 */

using System;
using System.Linq;
using System.Collections.Generic;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray();
      Dictionary<int, int> freq = new Dictionary<int, int>();
      foreach (var x in a) {
        if (freq.ContainsKey(x)) // Check if element already exists in frequency map
          freq[x]++;
        else
          freq[x] = 1; // Initialize frequency of new element to 1
      }
      int maxFreq = freq.Values.Max(); // Find maximum frequency among all elements
      int ans = 0;
      for (int k = 1; k <= maxFreq; k++) {
        int cnt = freq.Values.Count(v => v >= k); // Count how many elements have frequency >= k
        ans = Math.Max(ans, cnt * k); // Update maximum score
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/