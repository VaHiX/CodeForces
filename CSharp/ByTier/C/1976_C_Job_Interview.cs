// Problem: CF 1976 C - Job Interview
// https://codeforces.com/contest/1976/problem/C

/*
Algorithm: Two-pass greedy assignment with precomputation
- First pass (mark1): Assign candidates to programmer or tester based on higher skill, prioritizing available slots
- Second pass (mark2): Assign candidates to programmer or tester with opposite strategy (swap roles)
- For each candidate, calculate team skill when they are excluded:
  - If candidate was assigned as programmer, subtract their programming skill from first pass total
  - If candidate was assigned as tester, subtract their testing skill from second pass total

Time Complexity: O(n + m) per test case, as we make two passes through all candidates
Space Complexity: O(n + m) for storing mark arrays and input arrays

Techniques: Greedy assignment, two-pass preprocessing, prefix/suffix computation optimization
*/
using System;
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      string[] nm = Console.ReadLine().Split();
      int n = int.Parse(nm[0]);
      int m = int.Parse(nm[1]);
      int[] a = new int[n + m + 1];
      int[] b = new int[n + m + 1];
      Action<int[], int> fill = (arr, size) => {
        string[] elements = Console.ReadLine().Split();
        for (int i = 0; i < size; ++i) {
          arr[i] = int.Parse(elements[i]);
        }
      };
      fill(a, n + m + 1);
      fill(b, n + m + 1);
      long ed = 0, et = 0;
      int cd = 0, ct = 0;
      int[] mark1 = new int[a.Length];
      int[] mark2 = new int[a.Length];
      // First pass: assign candidates as programmers or testers based on higher skill
      for (int i = 0; i < a.Length; ++i) {
        if (a[i] > b[i] && cd <= n) {
          ed += a[i];
          cd += 1;
          mark1[i] = 1; // Mark candidate i as programmer
        } else if (a[i] < b[i] && ct < m) {
          ed += b[i];
          ct += 1;
          mark1[i] = 0; // Mark candidate i as tester
        } else if (cd <= n) {
          ed += a[i];
          cd += 1;
          mark1[i] = 1;
        } else {
          ed += b[i];
          ct += 1;
          mark1[i] = 0;
        }
      }
      ct = 0;
      cd = 0;
      // Second pass: assign candidates with swapped strategy
      for (int i = 0; i < a.Length; ++i) {
        if (a[i] < b[i] && ct <= m) {
          et += b[i];
          ct += 1;
          mark2[i] = 0; // Mark candidate i as tester
        } else if (a[i] > b[i] && cd < n) {
          et += a[i];
          cd += 1;
          mark2[i] = 1; // Mark candidate i as programmer
        } else if (ct <= m) {
          et += b[i];
          ct += 1;
          mark2[i] = 0;
        } else {
          et += a[i];
          cd += 1;
          mark2[i] = 1;
        }
      }
      // Calculate final result for each candidate
      for (int i = 0; i < a.Length; ++i) {
        long v1 = 0;
        if (mark1[i] == 1) {
          // Candidate was assigned as programmer, subtract programming skill
          v1 = ed - a[i];
        } else if (mark2[i] == 0) {
          // Candidate was assigned as tester in second pass, subtract testing skill
          v1 = et - b[i];
        }
        Console.Write(v1 + " ");
      }
      Console.WriteLine();
    }
  }
}


// https://github.com/VaHiX/CodeForces/