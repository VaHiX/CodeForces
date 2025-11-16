// Problem: CF 1991 B - AND Reconstruction
// https://codeforces.com/contest/1991/problem/B

/*
 * Problem: AND Reconstruction
 * Purpose: Given an array b of n-1 integers, construct an array a of n integers such that 
 *          b[i] = a[i] & a[i+1] for all valid i. If no such array exists, return -1.
 * 
 * Algorithm:
 * - Start with the first element of array a as the first element of b.
 * - For each subsequent element, compute it as the bitwise OR of consecutive elements in b.
 * - Finally, verify if the reconstructed array satisfies the condition b[i] = a[i] & a[i+1].
 * 
 * Time Complexity: O(n) per test case, as we iterate through the array a twice (once to construct, once to validate).
 * Space Complexity: O(n) for storing the result array a.
 */

using System;
using System.Collections;
using System.Collections.Generic;
class Program {
  static void Solve() {
    int n = Convert.ToInt32(Console.ReadLine());
    var arr = new List<string>(Console.ReadLine().Split(' '))
                  .ConvertAll(a => Convert.ToInt32(a));
    var ans = new List<int>() { arr[0] }; // Initialize first element of a with first element of b
    
    // Compute the rest of the elements of array a
    for (int i = 0; i < n - 2; i++) {
      ans.Add(arr[i] | arr[i + 1]); // Bitwise OR of consecutive elements in b
    }
    
    ans.Add(arr[n - 2]); // Last element of a is the last element of b
    
    bool flag = true;
    // Validate that the constructed array a satisfies the condition
    for (int i = 0; i < n - 1; i++) {
      if ((ans[i] & ans[i + 1]) != arr[i]) {
        flag = false;
        break;
      }
    }
    
    if (flag) {
      Console.WriteLine(string.Join(" ", ans));
    } else {
      Console.WriteLine(-1);
    }
  }
  static void Main() {
    int T = Convert.ToInt32(Console.ReadLine());
    while (T-- > 0)
      Solve();
  }
}


// https://github.com/VaHiX/CodeForces/