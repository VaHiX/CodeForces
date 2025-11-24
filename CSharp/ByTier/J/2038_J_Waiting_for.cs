// Problem: CF 2038 J - Waiting for...
// https://codeforces.com/contest/2038/problem/J

/*
 * Code Purpose: Simulates a bus stop scenario where people arrive and buses with available seats arrive.
 *               For each bus event, determines whether Monocarp can board the bus based on:
 *               - If there are enough seats for all people (except Monocarp), they all enter.
 *               - The remaining seats allow Monocarp to enter if any are left.
 *
 * Algorithms/Techniques: Simulation, Parsing
 *
 * Time Complexity: O(n), where n is the number of events — each event is processed once.
 * Space Complexity: O(1) — only using a fixed amount of variables, not dependent on input size.
 */

using System;
class demo {
  static void Main() {
    int q;
    q = int.Parse(Console.ReadLine()); // Read number of events
    long sum = 0; // Tracks total number of people waiting at the bus stop
    while (q > 0) {
      q--;
      string a;
      long b;
      a = Console.ReadLine(); // Read the event line
      string[] parts = a.Split(' '); // Split into command and value
      
      if (parts.Length == 2 && parts[0] == "P" &&
          long.TryParse(parts[1], out b)) {
        // Process 'P' (people arrived) event
        sum += b; // Add people to waiting count
      } else if (parts.Length == 2 && parts[0] == "B" &&
                 long.TryParse(parts[1], out b)) {
        // Process 'B' (bus arrived) event
        if (sum >= b) {
          // Not enough seats for everyone, so cannot board
          Console.WriteLine("NO");
          sum -= b; // Reduce sum by bus capacity (effectively removing people who boarded)
        } else {
          // There are enough seats to accommodate everyone and Monocarp
          Console.WriteLine("YES");
          sum = 0; // Reset waiting count after boarding
        }
      } else {
        // Invalid input format
        Console.WriteLine("Định dạng đầu vào không hợp lệ");
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/