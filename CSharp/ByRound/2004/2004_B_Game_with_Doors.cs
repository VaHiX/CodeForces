// Problem: CF 2004 B - Game with Doors
// https://codeforces.com/contest/2004/problem/B

/*
 * Problem: Game with Doors
 * 
 * Description:
 * There are 100 rooms arranged in a row and 99 doors between them. Each door connects room i and i+1.
 * Alice is located in some room from segment [l, r], and Bob is in some room from segment [L, R].
 * We want to lock the minimum number of doors so that Alice and Bob cannot reach each other,
 * regardless of their exact starting positions within those segments.
 * 
 * Approach:
 * - The key insight is that Alice can reach Bob if there exists a path through unlocked doors between
 *   them. To prevent any such connection, we must block all potential paths.
 * - For two segments [l,r] and [L,R], the minimum number of doors to lock corresponds to:
 *   - If segments are disjoint: 1 door (the one between r and L or l and R)
 *   - If intervals overlap or touch: 
 *     o if they completely overlap: no doors needed
 *     o else, we evaluate overlapping ranges and determine the minimal set of doors to lock.
 * 
 * Time Complexity: O(1) - Constant time per test case as all operations depend only on fixed values.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameWithDoors {
  internal class Program {
    static void Main(string[] args) {
      int limit = int.Parse(Console.ReadLine());
      for (int i = 0; i < limit; i++) {
        Solve();
      }
    }

    static void Solve() {
      // Read Alice's segment [a, b]
      int[] input1 = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
      int a = input1[0];
      int b = input1[1];

      // Read Bob's segment [c, d]
      int[] input2 = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
      int c = input2[0];
      int d = input2[1];

      int answer = 0;

      // If Alice's last room is to the right of Bob's first room or
      // Bob's last room is to the right of Alice's first room, then
      // no doors between them can be unlocked — hence 1 door to lock
      if (a > d || c > b) {
        answer = 1;
      } 
      // If both segments touch at a point (i.e., boundary overlaps), 
      // one door suffices to stop movement unless there's more overlap
      else if (a == d || b == c) {
        answer = 2;
      } 
      // When Alice's start is greater than Bob's start 
      else if (a > c) {
        if (d < b)
          // Alice starts after Bob, and Bob ends before Alice finishes — locks from a to d
          answer = d - a + 2;
        else if (d == b)
          // Touching at edges — only a single path through
          answer = b - a + 1;
        else if (d > b)
          // Bob's range includes or exceeds Alice's — locks from a to b
          answer = b - a + 2;
      } 
      // When Alice's start is equal to Bob's start
      else if (a == c) {
        if (d < b)
          // Bob’s end is inside Alice’s range — lock d minus a
          answer = d - a + 1;
        else if (d == b)
          // Same range — no door needs to be locked
          answer = b - a;
        else if (d > b)
          // Bob’s range exceeds Alice's — locks from c to b
          answer = b - a + 1;
      } 
      // When Alice starts before Bob does
      else if (a < c) {
        if (d < b)
          // Bob ends before Alice – locks between c and d
          answer = d - c + 2;
        else if (d == b)
          // Just touching at edge — need one lock
          answer = d - c + 1;
        else if (d > b)
          // Bob extends beyond Alice's range — locks from c to b
          answer = b - c + 2;
      }

      Console.WriteLine(answer);
    }
  }
}


// https://github.com/VaHiX/codeForces/