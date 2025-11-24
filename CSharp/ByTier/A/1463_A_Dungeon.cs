// Problem: CF 1463 A - Dungeon
// https://codeforces.com/contest/1463/problem/A

/*
 * Problem: Dungeon
 * 
 * Algorithm/Technique: Mathematical Analysis
 * 
 * Time Complexity: O(1) - Constant time operations for each test case
 * Space Complexity: O(1) - Only using a fixed amount of extra space regardless of input size
 * 
 * Approach:
 * - Each regular shot deals 1 damage to one monster.
 * - Every 7th shot is enhanced and deals 1 damage to all monsters.
 * - The goal is to kill all monsters with the same enhanced shot (i.e., the 7th, 14th, 21st, etc.).
 * - This means that the total damage dealt before the enhanced shot must be such that the final 
 *   enhanced shot kills all monsters.
 * 
 * Key Insight:
 * - For this to happen, each monster must have at least enough damage dealt to it by regular shots 
 *   before the enhanced shot, plus the damage from the enhanced shot.
 * - Let’s say we perform `k` shots, which include `k / 7` enhanced shots and `k - k / 7` regular shots.
 * - However, we are only interested in the moment when all monsters are killed by the same enhanced shot.
 * - That means, the total health points of the monsters divided by 9 (3 monsters * 3 regular shots each) 
 *   gives how many full cycles of 7 shots are required to kill monsters with one enhanced shot.
 * 
 * So, if (a + b + c) is divisible by 9 and:
 * - a >= (a + b + c) / 9,
 * - b >= (a + b + c) / 9, 
 * - c >= (a + b + c) / 9,
 * Then it is possible to do so.
 * 
 * The condition simplifies to checking whether the total health is divisible by 9,
 * and if each monster has at least (total_health / 9) health points.
 */

using System;
namespace _1463A_Dungeon {
internal class Program {
  static void Main(string[] args) {
    int[] array;        // Array to store the health points of three monsters
    int tmp;            // Variable to hold the required minimum damage per monster
    
    // Loop through the number of test cases
    for (int i = int.Parse(Console.ReadLine()); i > 0; i--) {
      // Read and parse the health points of the three monsters
      array = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
      
      // Check if total health is divisible by 9 (as each enhanced shot affects all monsters)
      if ((array[0] + array[1] + array[2]) % 9 != 0)
        Console.WriteLine("NO");
      else {
        // Calculate how much damage each monster should have had before the enhanced shot
        tmp = (array[0] + array[1] + array[2]) / 9;
        
        // Check if each monster's health is sufficient for the solution
        if (array[0] >= tmp && array[1] >= tmp && array[2] >= tmp)
          Console.WriteLine("YES");
        else
          Console.WriteLine("NO");
      }
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/