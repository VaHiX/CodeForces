// Problem: CF 2136 A - In the Dream
// https://codeforces.com/contest/2136/problem/A

/*
 * Problem: A. In the Dream
 * 
 * Purpose:
 *   Determine if a given score distribution across two halves of a football match
 *   is possible under the constraint that no team can score three consecutive goals
 *   in either half.
 *   
 * Algorithm:
 *   The solution checks whether each half (first and second) of the match can have
 *   a valid goal sequence that produces the specified scores without violating the rule
 *   of no three consecutive goals for any team.
 *   
 *   For a given half with scores (a, b), it is valid if:
 *     1. The difference between the two teams' scores does not exceed twice the smaller score plus 2.
 *     2. If one score is zero, then the other must be at most 2.
 *   
 * Time Complexity: O(1) - Constant time for each test case since we perform a fixed number of operations.
 * Space Complexity: O(1) - Uses only a constant amount of extra space.
 */

namespace Problems {
public class P2136A {
  public static void Main(string[] args) {
    var numberOfTests = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < numberOfTests; i++) {
      var inputs = Console.ReadLine().Split(' ').Select(int.Parse).ToArray(); // Parse input scores
      var a = inputs[0];
      var b = inputs[1];
      var c = inputs[2];
      var d = inputs[3];
      var result = IsScorePossible(a, b, c, d); // Check if the overall score is possible
      Console.WriteLine(result ? "YES" : "NO"); // Output result
    }
  }
  
  public static bool IsScorePossible(int a, int b, int c, int d) {
    // Check if both halves are valid independently
    return IsScorePossible(a, b) && IsScorePossible(c - a, d - b);
  }
  
  public static bool IsScorePossible(int a, int b) {
    // Ensure a >= b for easier logic
    if (b > a)
      (a, b) = (b, a);
    if (b == 0) {
      // If one team didn't score at all, then the other team must have scored at most 2 goals
      return a <= 2;
    }
    // For non-zero scores, check if valid using formula derived from forbidden pattern constraints
    return (a - 2) <= (2 * b);
  }
}
}


// https://github.com/VaHiX/codeForces/