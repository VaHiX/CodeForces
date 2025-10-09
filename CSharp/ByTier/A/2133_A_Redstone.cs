// Problem: CF 2133 A - Redstone?
// https://codeforces.com/contest/2133/problem/A

/*
 * Problem: Gear Arrangement for Satisfactory Contraption
 * 
 * Task: Determine if gears can be arranged in a row such that the rightmost gear spins at exactly 1 revolution per second.
 * 
 * Algorithm:
 * - The speed of each gear depends on the number of teeth of the previous and current gear, and the speed of the previous gear.
 * - For a valid arrangement, we must find an ordering where the final speed is 1.
 * - This is equivalent to checking if there exists at least one pair of gears with equal number of teeth.
 *   If so, they can be placed adjacent to each other to cancel out multiplication effect and maintain unit speed.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) due to input array storage
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Numerics;

public struct Point {
  public int x;
  public int y;
  public Point(int x, int y) {
    this.x = x;
    this.y = y;
  }
}

namespace CodeForce {
public class Solve {
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      solve(); // Process each test case
    }
  }
  
  public static void solve() {
    int n = int.Parse(Console.ReadLine()); // Read number of gears
    int[] arr = Console.ReadLine().Split(' ').Select(int.Parse).ToArray(); // Read gear teeth counts
    
    // If there are duplicate gear teeth values, then arrangement is possible
    // because we can place duplicates adjacent to make speed 1
    if (arr.Length != arr.Distinct().Count()) {
      Console.WriteLine("yes"); // At least one pair of gears with same teeth allows valid arrangement
    } else {
      Console.WriteLine("no"); // No duplicates means all gears are unique, which cannot form valid arrangement
    }
  }
}
}


// https://github.com/VaHiX/codeForces/