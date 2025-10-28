// Problem: CF 2026 D - Sums of Segments
// https://codeforces.com/contest/2026/problem/D

// *************************************************************************************
// * Problem: D. Sums of Segments                                                      *
// * Algorithm: Block-based preprocessing with prefix sums                             *
// * Time Complexity: O(n^2 + q*sqrt(n))                                               *
// * Space Complexity: O(n^2)                                                          *
// *                                                                                   *
// * Description:                                                                      *
// * Given a sequence of integers, we construct a new sequence 'b' where each element  *
// * is the sum of a subarray from index l to r (inclusive). The goal is to compute     *
// * the sum of elements in 'b' between indices l and r.                               *
// *                                                                                   *
// * Techniques:                                                                       *
// * - Binary indexed tree using block decomposition                                   *
// * - Preprocessing with prefix sums                                                  *
// * - Efficient querying by decomposing intervals into blocks                         *
// *************************************************************************************
using System;
using System.Collections.Generic;
using System.Linq;

public class Solution {
  private const int MOD = 998244353;
  private static int n;
  private static List<long> dataValues;
  private static List<long> prefixSums;
  private static List<long> doublePrefixSums; // Prefix sum of prefix sums
  private static List<long> blockStartIndices; // Start indices of each block
  private static List<long> segmentSums; // Sum of segments in each block
  private static List<long> cumulativeBlockSums; // Cumulative sum of block sums

  // Compute prefix sums for a given list
  private static List<long> CalculatePrefixSums(List<long> inputList) {
    int k = inputList.Count;
    List<long> result = new List<long>(k + 1);
    for (int i = 0; i <= k; i++) {
      result.Add(0);
    }
    for (int i = 0; i < k; i++) {
      result[i + 1] = result[i] + inputList[i];
    }
    return result;
  }

  // Helper function to calculate partial sums efficiently using precomputed values
  private static long GetPartialSum(int l, int r1, int r2) {
    if (r2 <= r1)
      return 0L;
    long count = r2 - r1;
    long remainder = prefixSums[l] * count;
    long addition = doublePrefixSums[r2 + 1] - doublePrefixSums[r1 + 1];
    return addition - remainder;
  }

  // Maps global index to block and offset within block
  private static Tuple<int, int> ConvertIndexToBlockAndOffset(long i) {
    int blockIndex = blockStartIndices.BinarySearch(i);
    if (blockIndex < 0) {
      blockIndex = ~blockIndex - 1;
    }
    // Calculate local offset from start of the block
    Tuple<int, int> result = Tuple.Create(
        blockIndex, (int)(i - blockStartIndices[blockIndex] + blockIndex));
    return result;
  }

  // Performs query to compute sum of b between l and r
  private static long PerformQuery(long l, long r) {
    Tuple<int, int> leftInfo = ConvertIndexToBlockAndOffset(l);
    Tuple<int, int> rightInfo = ConvertIndexToBlockAndOffset(r);

    // Total block-based sum
    long result = cumulativeBlockSums[rightInfo.Item1 + 1] -
                  cumulativeBlockSums[leftInfo.Item1];

    // Subtract over-counted parts if left is not at block start
    if (leftInfo.Item2 != leftInfo.Item1)
      result -= GetPartialSum(leftInfo.Item1, leftInfo.Item1, leftInfo.Item2);

    // Subtract over-counted parts if right is not at end of block
    if (rightInfo.Item2 != n - 1)
      result -= GetPartialSum(rightInfo.Item1, rightInfo.Item2 + 1, n);
    return result;
  }

  public static void Main(string[] args) {
    n = int.Parse(Console.ReadLine());
    dataValues = Console.ReadLine().Split().Select(long.Parse).ToList();
    prefixSums = CalculatePrefixSums(dataValues);
    doublePrefixSums = CalculatePrefixSums(prefixSums);
    blockStartIndices = new List<long> { 0 };
    for (int i = n; i >= 1; i--) {
      blockStartIndices.Add(blockStartIndices.Last() + i); // Build indices at start of each block
    }

    segmentSums = new List<long>(n);
    for (int i = 0; i < n; i++) {
      segmentSums.Add(GetPartialSum(i, i, n)); // Compute the initial segment sums
    }

    cumulativeBlockSums = CalculatePrefixSums(segmentSums); // Preprocessing of block sums

    int q = int.Parse(Console.ReadLine());
    for (int i = 0; i < q; i++) {
      long[] lr = Console.ReadLine().Split().Select(long.Parse).ToArray();
      long l = lr[0];
      long r = lr[1];
      Console.WriteLine(PerformQuery(l - 1, r - 1)); // Adjust for 0-based indexing
    }
  }
}


// https://github.com/VaHiX/codeForces/