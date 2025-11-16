// Problem: CF 2053 B - Outstanding Impressionist
// https://codeforces.com/contest/2053/problem/B

/*
 * Problem: B. Outstanding Impressionist
 * 
 * Purpose: Determine for each impression whether it can be made unique,
 *          i.e., there exists a way to assign values such that the value
 *          of this impression is distinct from all others.
 *
 * Algorithm:
 * - For each test case, we analyze intervals [l_i, r_i] representing possible values.
 * - For a single interval [l,r], if l == r, it's a fixed value and needs special handling.
 * - We maintain a count array to track how many times a value appears in any of the fixed intervals.
 * - To check uniqueness for impression i, we consider whether its range covers
 *   any value that is already used (by fixed intervals) and can be assigned uniquely.
 * - A range [l,r] contains a unique value if the number of fixed values in that range
 *   is less than the size of the range (r - l + 1).
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */
using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int testCases = int.Parse(Console.ReadLine());
    const int MaxLimit = 400005;
    int[] valueCount = new int[MaxLimit];
    while (testCases-- > 0) {
      int numRanges = int.Parse(Console.ReadLine());
      var intervals = new List<(int First, int Second)>(numRanges);
      for (int i = 0; i < numRanges; i++) {
        var input = Console.ReadLine().Split();
        intervals.Add((int.Parse(input[0]), int.Parse(input[1])));
      }
      var fixedFrequency = new Dictionary<int, int>();
      foreach (var interval in intervals) {
        if (interval.First == interval.Second) {
          // If the interval is a single point, store it as a fixed value
          if (!fixedFrequency.ContainsKey(interval.First)) {
            fixedFrequency[interval.First] = 0;
          }
          fixedFrequency[interval.First]++;
        }
      }
      var distinctFixedValues = fixedFrequency.Keys.ToList();
      foreach (var kvp in fixedFrequency) {
        // Increment the count of how many times this value is used
        valueCount[kvp.Key] += kvp.Value;
      }
      distinctFixedValues.Sort();
      var result = new System.Text.StringBuilder(numRanges);
      foreach (var interval in intervals) {
        int left = interval.First;
        int right = interval.Second;
        if (left < right) {
          // Binary search to find how many fixed values are within [left, right]
          int lowerBoundIdx = distinctFixedValues.BinarySearch(left);
          if (lowerBoundIdx < 0)
            lowerBoundIdx = ~lowerBoundIdx;
          int upperBoundIdx = distinctFixedValues.BinarySearch(right + 1);
          if (upperBoundIdx < 0)
            upperBoundIdx = ~upperBoundIdx;
          int countInRange = upperBoundIdx - lowerBoundIdx;
          int rangeSize = right - left + 1;
          // If not all values in range are already occupied, it's unique
          if (countInRange < rangeSize) {
            result.Append('1');
          } else {
            result.Append('0');
          }
        } else {
          // For a fixed value (single point), check whether it is used more than once
          int singleValue = left;
          if (valueCount[singleValue] <= 1) {
            result.Append('1');
          } else {
            result.Append('0');
          }
        }
      }
      Console.WriteLine(result.ToString());
      // Reset the count array for next test case
      foreach (var kvp in fixedFrequency) {
        valueCount[kvp.Key] -= kvp.Value;
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/