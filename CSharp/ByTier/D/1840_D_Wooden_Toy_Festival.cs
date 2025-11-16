// Problem: CF 1840 D - Wooden Toy Festival
// https://codeforces.com/contest/1840/problem/D

/*
 * Problem: Wooden Toy Festival
 * 
 * Algorithm/Technique: Binary Search + Greedy
 * 
 * Time Complexity: O(n log n + n log MaxValue) where n is the number of people.
 *                  Sorting takes O(n log n), binary search iterates O(log MaxValue) times,
 *                  and each Check operation takes O(n).
 * Space Complexity: O(1) excluding input storage.
 * 
 * Approach:
 * - We want to assign 3 carvers to minimize the maximum waiting time.
 * - Waiting time for a carver with pattern x making toy pattern y is |x - y|.
 * - This problem reduces to finding 3 intervals such that all elements fall into these intervals,
 *   and the width (2*x) of the intervals is minimized.
 * - We use binary search on the answer (the maximum waiting time x).
 * - For a given x, we check if it's possible to cover all elements using at most 3 intervals of size 2*x.
 * - The Check function uses a greedy approach to count the minimum number of intervals needed.
 */

using System;
class Program {
  // Check if it's possible to cover all elements with at most 3 intervals of size 2*x
  static bool Check(int[] a, int x) {
    int cnt = 1, left = 0;
    for (int right = 1; right < a.Length; ++right) {
      // If current element is too far from the start of the current interval, start a new one
      if (a[right] - a[left] > 2 * x) {
        left = right;
        ++cnt;
      }
    }
    return cnt <= 3;
  }
  
  // Find the minimal maximum waiting time using binary search
  static int Solution() {
    int n = int.Parse(Console.ReadLine());
    int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    Array.Sort(a);  // Sort the patterns to allow greedy interval covering
    
    int left = 0, right = (int)1e9;  // Binary search on the answer
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (Check(a, mid)) {
        // If we can do it with 'mid' as max waiting time, try smaller value
        right = mid - 1;
      } else {
        // Otherwise, we need larger max waiting time
        left = mid + 1;
      }
    }
    return left;
  }
  
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Console.WriteLine(Solution());
    }
  }
}


// https://github.com/VaHiX/CodeForces/