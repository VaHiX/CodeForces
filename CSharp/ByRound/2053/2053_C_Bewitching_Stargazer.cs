// Problem: CF 2053 C - Bewitching Stargazer
// https://codeforces.com/contest/2053/problem/C

using System;
class Program {
  /// <summary>
  /// Calculates the final lucky value based on recursive star observation process.
  /// 
  /// Algorithm:
  /// 1. Recursively divides segments of stars based on their length.
  /// 2. If segment length is odd, observe middle star and split into two parts.
  /// 3. If segment length is even, split into two equal parts without observing a middle star.
  /// 4. Lazy observation: stop if segment length is less than threshold k.
  /// 
  /// Time Complexity: O(log n), due to recursive halving of segments.
  /// Space Complexity: O(log n), due to recursion depth.
  /// </summary>
  public static (long, int) LuckyValue(long left, long right, int threshold) {
    // Base case: if the segment is smaller than threshold, no further processing
    if (right - left + 1 < threshold) {
      return (0, 0);
    }
    // Base case: single star, observe it and return
    if (right - left + 1 == 1) {
      return (left, 1);
    }
    // Calculate the middle point
    long mid = left + (right - left) / 2;
    // If the segment length is odd
    if ((right - left + 1) % 2 == 1) {
      // Recursively process the left part (excluding middle)
      var leftResult = LuckyValue(left, mid - 1, threshold);
      // Accumulate lucky value: add middle star, add contributions from left, add contributions from right
      long totalLucky = mid + 2 * leftResult.Item1 + mid * leftResult.Item2;
      // Total segments is double the left segments plus the middle segment
      int totalSegments = 2 * leftResult.Item2 + 1;
      return (totalLucky, totalSegments);
    } else {
      // If segment length is even, split into two equal halves without observing a star
      var leftResult = LuckyValue(left, mid, threshold);
      // Accumulate lucky value: contributions from left, and left count multiplied by mid
      long totalLucky = 2 * leftResult.Item1 + mid * leftResult.Item2;
      // Total segments is double the left segments
      int totalSegments = 2 * leftResult.Item2;
      return (totalLucky, totalSegments);
    }
  }
  static void Main() {
    int test_cases = int.Parse(Console.ReadLine());
    while (test_cases-- > 0) {
      string[] input = Console.ReadLine().Split();
      long n = long.Parse(input[0]);
      int k = int.Parse(input[1]);
      var result = LuckyValue(1, n, k);
      Console.WriteLine(result.Item1);
    }
  }
}


// https://github.com/VaHiX/CodeForces/