// Problem: CF 2000 B - Seating in a Bus
// https://codeforces.com/contest/2000/problem/B

/*
B. Seating in a Bus
Algorithms/Techniques: Simulation with boolean array tracking seat occupancy.
Time Complexity: O(n) per test case, where n is the number of seats.
Space Complexity: O(n) for the boolean array s.

The problem simulates seating rules on a bus:
- If no seats are occupied, any passenger can sit anywhere.
- Otherwise, a passenger must sit in a seat adjacent to an already occupied seat.

This solution uses a boolean array 's' to track which seats are occupied.
For each passenger in order:
- If the current seat has no neighbors occupied, output "NO".
- Mark the seat as occupied.
- Continue until all passengers are processed, then output "YES" if no violations occurred.
*/

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read number of seats
      string[] line = Console.ReadLine().Trim().Split(' '); // Read the seating order
      var a = Array.ConvertAll(line, int.Parse); // Convert to int array
      getAns(n, a); // Process the seating sequence
    }
  }
  static void getAns(int n, int[] a) {
    var s = new bool[n + 2]; // Boolean array to track seat occupancy (1-indexed, with padding)
    s[a[0]] = true; // First passenger sits anywhere, mark their seat as occupied
    for (int i = 1; i < n; i++) { // Process remaining passengers
      if (!s[a[i] - 1] && !s[a[i] + 1]) { // Check if neither neighbor is occupied
        Console.WriteLine("NO"); // Violation found
        return;
      }
      s[a[i]] = true; // Mark current seat as occupied
    }
    Console.WriteLine("YES"); // All passengers followed the rules
  }
}


// https://github.com/VaHiX/codeForces/