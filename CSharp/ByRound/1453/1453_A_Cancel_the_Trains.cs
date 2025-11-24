// Problem: CF 1453 A - Cancel the Trains
// https://codeforces.com/contest/1453/problem/A

/*
Algorithm: Greedy + Hash Set
Approach:
- For each test case, we are given two arrays: one of trains departing from the bottom (a) and another from the left (b).
- Each train from the bottom starts at position (i, 0) and moves to (i, T) after T minutes.
- Each train from the left starts at position (0, i) and moves to (T, i) after T minutes.
- A crash occurs if a train from the bottom and a train from the left are at the same point (x, y) at the same time.
- This happens when: 
  - Train from bottom at (i, 0) and train from left at (0, j) meet at (i, j) at time T = i = j.
- Thus, a crash occurs when the train numbers (i.e. train IDs) match between the two arrays.
- So, the problem becomes counting how many elements are common in the two arrays — these are the trains causing crashes.
- To minimize cancellation, we cancel one of the two trains in each conflicting pair. 
  So, the minimal number of cancellations is equal to the count of common elements.

Time Complexity: O(n + m)
Space Complexity: O(1) (since the boolean array f is fixed size of 101)

*/
using System;
public class hello {
  static void Main() {
    var t = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (t-- > 0) {
      Console.ReadLine(); // Skip the line with n and m (not needed in implementation)
      string[] line = Console.ReadLine().Trim().Split(' '); // Read train numbers from bottom
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      line = Console.ReadLine().Trim().Split(' '); // Read train numbers from left
      var b = Array.ConvertAll(line, int.Parse); // Convert to integer array
      getAns(a, b); // Compute and print result
    }
  }
  static void getAns(int[] a, int[] b) {
    var f = new bool[101]; // Boolean array to mark presence of train IDs from left side (1-based indexing)
    foreach (var x in b)
      f[x] = true; // Mark each train ID from the left side
    var count = 0; // Counter for overlapping train IDs
    foreach (var x in a)
      if (f[x])
        count++; // If train ID from bottom exists in left side, increment counter
    Console.WriteLine(count); // Output minimum number of trains to cancel
  }
}


// https://github.com/VaHiX/CodeForces/