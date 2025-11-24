// Problem: CF 1676 H1 - Maximum Crossings (Easy Version)
// https://codeforces.com/contest/1676/problem/H1

﻿/*
 * Problem: Maximum Crossings (Easy Version)
 * 
 * Algorithm:
 * - This problem is about counting the maximum number of wire crossings when connecting segments
 *   from a top terminal to a bottom terminal.
 * - The key insight is that each wire from segment i to segment a[i] will cross all previous wires
 *   that go from a segment j such that j < i and a[j] > a[i]. This is a classic inversion counting problem.
 * - To efficiently count these inversions, a segment tree is used.
 * 
 * Time Complexity:
 * - For each element in the array, we perform two O(log n) operations on the segment tree:
 *   - Increment operation to update the count of segments used.
 *   - Sum query operation to count how many segments from a[i] onwards have been used.
 * - Total time complexity is O(n log n) per test case.
 * 
 * Space Complexity:
 * - O(n) for the segment tree and O(n) for the input array.
 * - Total space complexity is O(n).
 */

using System;
using System.Linq;
namespace ConsoleApp1 {
class Program {
  static void Main(string[] args) {
    var t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      var n = int.Parse(Console.ReadLine());
      var a = Console.ReadLine().Split().Select(int.Parse).ToArray();
      Console.WriteLine(Solve(a));
    }
  }
  private static long Solve(int[] array) {
    long result = 0;
    var segmentTree = new SegmentTree(array.Length);
    for (int start = 0; start < array.Length; start++) {
      var end = array[start] - 1; // Convert to 0-based index
      var sum = segmentTree.Sum(end, array.Length - 1); // Count segments from 'end' to end of array that are already used
      result += sum; // Add this to the total crossings
      segmentTree.Increment(end); // Mark this segment as used
    }
    return result;
  }
  class SegmentTree {
    private readonly int[] data;
    private readonly int k;
    private readonly int depth;
    public SegmentTree(int length) {
      k = 1;
      depth = 0;
      while (k < length) {
        depth++;
        k <<= 1;
      }
      data = new int[2 * k]; // Segment tree initialized with double size
    }
    public void Increment(int i) {
      var index = i + k; // Point to the leaf node
      data[index]++;
      while ((index /= 2) > 0) { // Update up to the root
        data[index]++;
      }
    }
    public int Sum(int left, int right) {
      var leftRes = 0;
      var rightRes = 0;
      left += k;
      right += k;
      while (left < right) {
        if (left % 2 == 1) // If left is a right child, add its value and move to the next
          leftRes += data[left];
        left = (left + 1) / 2;
        if (right % 2 == 0) // If right is a left child, add its value and move to the previous
          rightRes += data[right];
        right = (right - 1) / 2;
      }
      if (left == right)
        leftRes += data[left]; // If left and right are the same, add the value
      return leftRes + rightRes;
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/