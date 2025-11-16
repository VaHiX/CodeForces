// Problem: CF 2062 B - Clockwork
// https://codeforces.com/contest/2062/problem/B

/*
B. Clockwork
Algorithms/Techniques: Greedy, Two pointers, Simulation analysis

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array

The problem involves determining whether it's possible to navigate through a sequence of time clocks such that 
none of them reaches zero, by moving between adjacent clocks and resetting the current clock's time.

Key insight:
- For each clock at position i, we can only reset it if we're on it (or adjacent to it).
- The minimum time required for a clock at index i to be safe is (n - 1 - i) * 2 seconds before it can be reset.
- Therefore, a clock's initial value must be strictly greater than (n - 1 - i) * 2 to be safe.

We check both ends of the array (since movement is allowed only adjacent), 
and ensure no element violates the safety condition.
*/

using System;
using System.IO.Pipes;

public class Program {
  public static void Main() {
    Program program = new Program();
    program.Task_B();
  }
  
  public void Task_A() {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      int ans = 0;
      string s = Console.ReadLine();
      foreach (char c in s) {
        if (c == '1')
          ans++;
      }
      Console.WriteLine(ans);
    }
  }
  
  public void Task_B() {
    int t = int.Parse(Console.ReadLine());
    for (int q = 0; q < t; q++) {
      int n = int.Parse(Console.ReadLine());
      string[] s = Console.ReadLine().Split(' ');
      int[] a = new int[s.Length];
      for (int i = 0; i < n; i++) {
        a[i] = int.Parse(s[i]);
      }
      int k = 0;
      bool f = true;
      if (n % 2 != 0)
        k++; // Handle odd-length arrays - middle element gets processed once
      for (int i = 0; i < n / 2 + k; i++) {
        // Check if the current element or its mirror (from end) is safe to use.
        // For a clock at index i, and one at index (n - 1 - i):
        // It must be strictly larger than twice its 'distance from edge' 
        // because the worst-case scenario requires two full cycles to pass before resetting.
        if (a[i] <= (n - 1 - i) * 2 || a[n - 1 - i] <= (n - 1 - i) * 2) {
          Console.WriteLine("NO");
          f = false;
          break;
        }
      }
      if (f)
        Console.WriteLine("YES");
    }
  }
}


// https://github.com/VaHiX/codeForces/