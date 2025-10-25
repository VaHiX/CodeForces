// Problem: CF 2114 C - Need More Arrays
// https://codeforces.com/contest/2114/problem/C

/*
 * Problem: C. Need More Arrays
 * Algorithm: Greedy approach to maximize number of arrays by removing elements.
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(1) excluding input storage.
 * 
 * The algorithm works by iterating through the sorted array and counting how many times
 * we need to start a new array. A new array starts when the current element is greater than
 * the previous element plus 1. This ensures that within each group, no two elements are consecutive,
 * thus maximizing the number of arrays formed.
 */

using System;
public class Program {
  static void Solve() {
    Console.ReadLine();
    string[] parts =
        Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
    int n = parts.Length;
    int temp = int.Parse(parts[0]); // Track the last element in current group
    int count = 1; // At least one array will be formed
    for (int i = 1; i < n; i++) {
      int current = int.Parse(parts[i]);
      if (current > temp + 1) { // If current is not consecutive to previous, start new group
        count++;
        temp = current;
      }
    }
    Console.WriteLine(count);
  }
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++)
      Solve();
  }
}


// https://github.com/VaHiX/CodeForces/