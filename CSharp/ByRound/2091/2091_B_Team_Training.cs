// Problem: CF 2091 B - Team Training
// https://codeforces.com/contest/2091/problem/B

/* 
 * Problem: B. Team Training
 * Purpose: Maximize the number of strong teams where each team's strength (number of members * min skill) is at least x.
 * Algorithm: Greedy approach with sorting.
 *          - Sort students in descending order of skills.
 *          - For each student, decide whether to form a new team or add to an existing group.
 * Time Complexity: O(n log n) due to sorting.
 * Space Complexity: O(1) excluding input storage.
 */
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n and x
      var n = int.Parse(line[0]);
      var x = int.Parse(line[1]);
      line = Console.ReadLine().Trim().Split(' '); // Read student skills
      var a = Array.ConvertAll(line, int.Parse);
      getAns(n, x, a); // Process current test case
    }
  }
  static void getAns(int n, int x, int[] a) {
    Array.Sort(a); // Sort in ascending order
    Array.Reverse(a); // Reverse to get descending order (highest first)
    var ans = 0; // Count of strong teams
    var w = 0; // Current number of members in a potential team
    foreach (var z in a) { // Iterate through sorted skills
      if (z >= x) // If skill is already sufficient for a single-member team
        ans++;
      else {
        w++; // Add current student to group
        if (z * w >= x) { // Check if group strength meets requirement
          ans++; // Form a new strong team
          w = 0; // Reset member count
        }
      }
    }
    Console.WriteLine(ans); // Output result for this test case
  }
}


// https://github.com/VaHiX/codeForces/