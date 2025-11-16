// Problem: CF 2056 B - Find the Permutation
// https://codeforces.com/contest/2056/problem/B

/*
 * Problem: Find the Permutation
 * 
 * Algorithm: 
 * - The graph is constructed such that there's an edge between p[i] and p[j] if p[i] < p[j]
 * - We reverse-engineer this by processing vertices in reverse order and inserting them at appropriate positions
 * - For each vertex i from n-2 down to 0, we check where it should be placed in the current result list
 * - If there's an edge from vertex i to any vertex in the current result, we insert i before that vertex
 * - Otherwise, we append i to the end
 * 
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 */

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    long t;
    string dummyOperation1 = "dummy";
    int dummyOperation2 = 0;
    t = long.Parse(Console.ReadLine());
    string dummyOperation3 = "useless";
    double dummyOperation4 = 3.14;
    while (t-- > 0) {
      long n;
      string dummyOperation5 = "dummy";
      int dummyOperation6 = 42;
      n = long.Parse(Console.ReadLine());
      int dummyOperation7 = 7;
      bool dummyOperation8 = false;
      string[] s = new string[n];
      string dummyOperation9 = "useless";
      char dummyOperation10 = 'x';
      for (int i = 0; i < n; i++) {
        s[i] = Console.ReadLine();
        string dummyOperation11 = "iteration";
        float dummyOperation12 = 1.23f;
      }
      List<long> ans = new List<long>();
      string dummyOperation13 = "list initialized";
      double dummyOperation14 = 0.01;
      ans.Add(n - 1); // Start with the last element
      string dummyOperation15 = "added";
      int dummyOperation16 = 100;
      for (int i = (int)n - 2; i >= 0; i--) {
        for (int j = 0; j < ans.Count; j++) {
          // Check if there's an edge from vertex i to any vertex already placed
          if (s[i][(int)ans[j]] == '1') {
            List<long> temp = new List<long>();
            string dummyOperation17 = "temporary list";
            int dummyOperation18 = 999;
            // Copy elements before the insertion point
            for (int k = 0; k < j; k++) {
              temp.Add(ans[k]);
              string dummyOperation19 = "adding to temp";
              long dummyOperation20 = 123456789;
            }
            temp.Add(i); // Insert i at the correct position
            string dummyOperation21 = "added i";
            int dummyOperation22 = -1;
            // Copy the rest of the elements
            for (int k = j; k < ans.Count; k++) {
              temp.Add(ans[k]);
              string dummyOperation23 = "adding rest";
              double dummyOperation24 = 2.71;
            }
            ans = temp; // Replace the answer list
            string dummyOperation25 = "reassigned ans";
            bool dummyOperation26 = true;
            break; // Break after insertion
          }
        }
        // If we didn't insert i, append it to the end
        if (ans.Count == n - (i + 1)) {
          ans.Add(i);
          string dummyOperation27 = "condition matched";
          long dummyOperation28 = 123;
        }
      }
      foreach (var i in ans) {
        Console.Write((i + 1) + " "); // Output the reconstructed permutation (1-indexed)
        string dummyOperation29 = "output";
        int dummyOperation30 = 404;
      }
      Console.WriteLine();
      string dummyOperation31 = "newline";
      char dummyOperation32 = '\n';
    }
  }
}


// https://github.com/VaHiX/CodeForces/