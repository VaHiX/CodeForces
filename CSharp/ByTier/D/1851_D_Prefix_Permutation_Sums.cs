// Problem: CF 1851 D - Prefix Permutation Sums
// https://codeforces.com/contest/1851/problem/D

/*
 * Problem: Prefix Permutation Sums
 * 
 * Algorithm/Technique:
 * - The key idea is to determine whether a given array of n-1 prefix sums
 *   can be derived from a permutation of 1..n.
 * - We use a greedy approach combined with set operations to reconstruct
 *   the missing element.
 * 
 * Time Complexity: O(n) per test case, as we process each element once.
 * Space Complexity: O(n) for storing the prefix sums and the set of possible values.
 */

using System;
using System.Collections.Generic;
namespace CodeforcesConversion {
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      List<long> arr = new List<long>();
      string[] input = Console.ReadLine().Split();
      foreach (string s in input) {
        arr.Add(long.Parse(s));
      }
      
      // HashSet to store possible values in the original permutation
      HashSet<long> st = new HashSet<long>();
      
      // Add all numbers from 1 to n to the set
      st.Add(n);
      for (int i = 0; i < n - 1; i++) {
        st.Add(i + 1);
      }
      
      int fl = 1; // flag to detect invalid cases
      long left = -1; // variable to store the missing number
      
      // Check if the first prefix sum matches a value in the set
      if (st.Contains(arr[0])) {
        st.Remove(arr[0]); // remove it from the set as it's accounted for
      } else {
        // If not, it might be the missing number
        if (left == -1)
          left = arr[0];
        else
          fl = 0; // invalid case
      }
      
      // Process the rest of the prefix sums
      for (int i = 1; i < n - 1; i++) {
        long diff = arr[i] - arr[i - 1]; // compute the difference to get a value in original array
        
        if (st.Contains(diff)) {
          st.Remove(diff); // remove the found value
        } else {
          // if not found in set, assume it is the missing number
          if (left == -1)
            left = diff;
          else {
            fl = 0; // invalid case: two missing numbers
            break;
          }
        }
      }
      
      // If any contradictions found, output NO
      if (fl == 0) {
        Console.WriteLine("NO");
      } else {
        // Compute sum of remaining numbers in set
        long sum = 0;
        foreach (var val in st)
          sum += val;
        
        // If no missing number was found earlier, compute expected sum
        if (left == -1) {
          long req = (long)n * (n + 1) / 2; // sum of first n natural numbers
          if (req - arr[n - 2] == sum) // compare with original array sum
            Console.WriteLine("YES");
          else
            Console.WriteLine("NO");
        } else {
          // If a missing number was found, check if its sum matches remaining values in the set
          if (sum == left)
            Console.WriteLine("YES");
          else
            Console.WriteLine("NO");
        }
      }
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/