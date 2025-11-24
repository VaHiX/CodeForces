// Problem: CF 1676 H2 - Maximum Crossings (Hard Version)
// https://codeforces.com/contest/1676/problem/H2

/* 
 * Problem: Maximum Crossings (Hard Version)
 * 
 * Purpose: 
 *   This solution computes the maximum number of crossings between wires connecting 
 *   segments of two terminals. Each wire connects from segment i of the top terminal 
 *   to segment a[i] of the bottom terminal. The optimal placement of wires maximizes 
 *   the number of intersections.
 * 
 * Algorithm:
 *   - Use a segment tree to efficiently track and query counts of segments that 
 *     have been used in previous connections.
 *   - For each wire starting at position `start`, compute how many previously 
 *     placed wires cross with it by counting those that end at or after 
 *     position `a[start] - 1`.
 *   - Update the segment tree to mark that this segment is now used.
 * 
 * Time Complexity: O(n log n)
 *   - For each of the n elements, we perform a sum query and an increment operation, 
 *     both taking O(log n) time in a segment tree.
 * 
 * Space Complexity: O(n)
 *   - The segment tree requires space proportional to n (specifically 2 * k where k 
 *     is the smallest power of 2 greater than or equal to n).
 * 
 * Techniques:
 *   - Segment Tree with point updates and range queries
 *   - Efficient counting of inversions using data structures
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
      var sum = segmentTree.Sum(end, array.Length - 1); // Count of wires ending after 'end'
      result += sum; // Add crossings for current wire
      segmentTree.Increment(end); // Mark segment as used
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
      data = new int[2 * k]; // Initialize segment tree
    }
    public void Increment(int i) {
      var index = i + k; // Point to leaf node
      data[index]++;
      while ((index /= 2) > 0) { // Propagate up
        data[index]++;
      }
    }
    public int Sum(int left, int right) {
      var leftRes = 0;
      var rightRes = 0;
      left += k;
      right += k;
      while (left < right) {
        if (left % 2 == 1)
          leftRes += data[left];
        left = (left + 1) / 2;
        if (right % 2 == 0)
          rightRes += data[right];
        right = (right - 1) / 2;
      }
      if (left == right)
        leftRes += data[left];
      return leftRes + rightRes;
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/