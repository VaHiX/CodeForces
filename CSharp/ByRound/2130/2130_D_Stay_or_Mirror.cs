// Problem: CF 2130 D - Stay or Mirror
// https://codeforces.com/contest/2130/problem/D

/*
D. Stay or Mirror
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

You are given a permutation p_1, p_2, ..., p_n of length n.
You have to build an array a_1, a_2, ..., a_n in the following way:

 for each 1 <= i <= n, set either a_i = p_i or a_i = 2n - p_i. 
Find the minimum possible number of inversions in the array a_1, a_2, ..., a_n.
An inversion in the array a_1, a_2, ..., a_n is a pair of indices (i, j) such that 1 <= i < j <= n and a_i > a_j.

Algorithms/Techniques: 
- For each element, we decide whether to keep it as p[i] or change it to 2*n - p[i]
- Precompute prefix and suffix count of elements that are less/greater respectively
- Dynamic decision making based on these counts to minimize inversions

Time Complexity: O(n^2) per test case
Space Complexity: O(n) for storing arrays and intermediate results
*/
using System;
using System.Linq;
using System.Collections.Generic;
class Program {
  public static void Main() {
    int testCase = Convert.ToInt32(Console.ReadLine());
    while (testCase-- > 0) {
      int n = Convert.ToInt32(Console.ReadLine());
      var v = Console.ReadLine().Split().Select(int.Parse).ToList();
      var pre = new List<int> { 0 }; // prefix count of elements smaller than current element
      var suff = new List<int>();   // suffix count of elements greater than current element
      for (int i = 1; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < i; j++) {
          if (v[i] < v[j])
            cnt++;
        }
        pre.Add(cnt);
      }
      for (int i = 0; i < n - 1; i++) {
        int cnt = 0;
        for (int j = i + 1; j < n; j++) {
          if (v[j] > v[i])
            cnt++;
        }
        suff.Add(cnt);
      }
      suff.Add(0); // Last element has no suffix
      var arr = new List<int>();
      for (int i = 0; i < n; i++)
        if (pre[i] > suff[i]) { // Choose value that reduces inversions
          arr.Add((2 * n) - v[i]);
        } else {
          arr.Add(v[i]);
        }
      int ans = 0;
      for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
          if (arr[i] > arr[j])
            ans++;
        }
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/codeForces/