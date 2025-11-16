// Problem: CF 1972 A - Contest Proposal
// https://codeforces.com/contest/1972/problem/A

using System;
using System.Collections.Generic;
class Program {
  static void Solve() {
    int n = int.Parse(Console.ReadLine());
    List<int> a = new List<int>(n);
    List<int> b = new List<int>(n);
    SortedSet<int> s = new SortedSet<int>(); // Used to maintain current contest problems in sorted order
    string[] aInput = Console.ReadLine().Split();
    foreach (string num in aInput)
      a.Add(int.Parse(num));
    string[] bInput = Console.ReadLine().Split();
    foreach (string num in bInput)
      b.Add(int.Parse(num));
    int i = 0, j = 0;
    int answer = 0;
    while (j < n) {
      if (a[i] > b[j]) {
        // Remove the most difficult problem (max element)
        s.Remove(s.Max);
        // Add new problem with difficulty b[j]
        s.Add(b[j]);
        answer++;
        j++;
      } else {
        // No need to add a new problem; move to next problem
        i++;
        j++;
      }
    }
    Console.WriteLine(answer);
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0)
      Solve();
  }
}
/*
Algorithm: Two Pointers with SortedSet
Approach:
- Use two pointers i and j to traverse arrays a and b.
- When a[i] > b[j], it means the current problem in a is more difficult than expected.
  In this case, we need to insert a new problem with difficulty b[j] into the contest.
  Since inserting and removing elements from a sorted set maintains the order, we remove the largest element (s.Max) and add the new one.
  Increment the answer counter and the pointer j.
- Otherwise, if a[i] <= b[j], increment both pointers.

Time Complexity: O(n log n) per test case due to operations on SortedSet (insertion and deletion in log n time).
Space Complexity: O(n) for storing the problem difficulties in the sorted set.

*/

// https://github.com/VaHiX/CodeForces/