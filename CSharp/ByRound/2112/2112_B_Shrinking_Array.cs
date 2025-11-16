// Problem: CF 2112 B - Shrinking Array
// https://codeforces.com/contest/2112/problem/B

/*
B. Shrinking Array
Algorithm: Greedy + Simulation
Time Complexity: O(n^2) in worst case due to list operations and nested loops
Space Complexity: O(n) for storing the array and auxiliary lists

The problem involves making an array "beautiful" by performing operations that reduce its size.
An array is beautiful if there exists a position i such that |b[i] - b[i+1]| <= 1.

Approach:
1. First check if the array is already beautiful (if adjacent elements differ by at most 1).
2. If not, and n == 2, it's impossible to make it beautiful since operation reduces size to 1.
3. Otherwise:
   - Try removing elements from left to right using greedy approach.
   - Check if any operation makes the array beautiful.
   - If not, try reversing the array and perform same steps.
   - Return the number of operations needed or -1 if impossible.

Techniques:
- Simulate operations on arrays with deletion and insertion.
- Greedy selection of elements to remove based on value range.
*/

using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Numerics;
namespace _ {
class Program {
  static void Main(string[] args) {
    Console.SetOut(
        new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false });
    if (File.Exists("input.txt")) {
      Console.SetIn(new StreamReader("input.txt"));
    }
    solve_B();
    Console.Out.Flush();
  }
  public static void solve_B() {
    int t = Convert.ToInt32(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      int n = Convert.ToInt32(Console.ReadLine()); // Read size of array
      int[] ar = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse); // Read array elements
      List<int> a = new List<int>(ar); // Convert to list for easier manipulation
      bool ok0 = false; // Check if array is already beautiful
      for (int i = 0; i < n - 1; i++) {
        if (Math.Abs(a[i] - a[i + 1]) <= 1) { // If adjacent elements differ by at most 1
          ok0 = true;
          break;
        }
      }
      if (ok0) {
        Console.WriteLine(0); // Already beautiful, no operations needed
      } else if (n == 2) {
        Console.WriteLine(-1); // Impossible to make beautiful with 2 elements
      } else {
        for (int i = 0; i < n - 2; i++) { // Try to find a valid operation
          int min = Math.Min(a[i + 1], a[i + 2]); // Find min of two adjacent elements
          int max = Math.Max(a[i + 1], a[i + 2]); // Find max of two adjacent elements
          if (a[i] >= min && a[i] <= max) { // If current element fits in range
            a.RemoveAt(i + 1); // Remove second element
            a.RemoveAt(i + 1); // Remove third element (already shifted)
            a.Insert(i + 1, a[i]); // Insert the value of first element back
            break;
          }
        }
        bool ok1 = false; // Check again if new array is beautiful
        for (int i = 0; i < n - 1; i++) {
          if (Math.Abs(a[i] - a[i + 1]) <= 1) {
            ok1 = true;
            break;
          }
        }
        if (!ok1) { // If still not beautiful
          List<int> rev = new List<int>(a); // Create reverse copy of array
          rev.Reverse(); // Reverse the list
          for (int i = 0; i < n - 2; i++) {
            int min = Math.Min(rev[i + 1], rev[i + 2]);
            int max = Math.Max(rev[i + 1], rev[i + 2]);
            if (rev[i] >= min && rev[i] <= max) {
              rev.RemoveAt(i + 1);
              rev.RemoveAt(i + 1);
              rev.Insert(i + 1, rev[i]);
              break;
            }
          }
          for (int i = 0; i < n - 1; i++) {
            if (Math.Abs(rev[i] - rev[i + 1]) <= 1) {
              ok1 = true;
              break;
            }
          }
        }
        Console.WriteLine(ok1 ? 1 : -1); // Output result
      }
    }
  }
  public static void solve_A() {
    int t = Convert.ToInt32(Console.ReadLine());
    while (t-- > 0) {
      int[] axy = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
      int a = axy[0];
      int x = axy[1];
      int y = axy[2];
      int m = (x + y) / 2;
      Console.WriteLine(Math.Abs(x - m) + Math.Abs(y - m) <
                                Math.Abs(x - a) + Math.Abs(y - a)
                            ? "YES"
                            : "NO");
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/