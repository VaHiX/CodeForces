// Problem: CF 2116 A - Gellyfish and Tricolor Pansy
// https://codeforces.com/contest/2116/problem/A

/*
 * Problem: A. Gellyfish and Tricolor Pansy
 * 
 * Game Rules:
 * - Gellyfish has 'a' HP, Flower has 'b' HP.
 * - Gellyfish's knight has 'c' HP, Flower's knight has 'd' HP.
 * - Players alternate turns (k=1,2,...), with odd k for Gellyfish and even k for Flower.
 * - On odd k: Gellyfish can attack either Flower (reducing b by 1) or Flower's knight (reducing d by 1).
 * - On even k: Flower can attack either Gellyfish (reducing a by 1) or Gellyfish's knight (reducing c by 1).
 * - Optimal play assumed.
 * 
 * Algorithm:
 * - Key insight: The outcome depends on the minimum of max HPs each player can sustain before losing their knight.
 * - If the minimum HP a player can withstand is less than or equal to the minimum of the opponent's knight HP,
 *   then that player will lose, as they cannot survive long enough to win.
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read input line and split by space
      var a = int.Parse(line[0]); // Gellyfish's HP
      var b = int.Parse(line[1]); // Flower's HP
      var c = int.Parse(line[2]); // Gellyfish's knight HP
      var d = int.Parse(line[3]); // Flower's knight HP
      getAns(a, b, c, d); // Compute and output result
    }
  }
  static void getAns(int a, int b, int c, int d) {
    var gf = Min(a, c); // Minimum of Gellyfish's HP and her knight's HP
    var fL = Min(b, d); // Minimum of Flower's HP and her knight's HP
    Console.WriteLine(fL <= gf ? "Gellyfish" : "Flower"); // Output the winner based on logic
  }
}


// https://github.com/VaHiX/CodeForces/