// Problem: CF 1872 B - The Corridor or There and Back Again
// https://codeforces.com/contest/1872/problem/B

using System;
using System.Text;
public class TheCorridorOrThereAndBackAgain {
  public static void Main() {
    // Flowerbox describing the code purpose, algorithms, and complexities
    /*
     * Code Purpose:
     * This program determines the maximum room number k such that one can travel from room 1 to room k and back to room 1
     * without triggering any traps. Each trap is defined by its position (d_i) and the delay (s_i) after entering the room
     * when the trap activates. The corridor is infinitely long, and movement takes 1 second per room.
     *
     * Algorithm:
     * For each test case:
     * 1. Read the number of traps (n).
     * 2. For each trap:
     *    - Calculate the latest room (k) that can be safely visited before the trap activates.
     *    - This is done by considering the time it takes to reach the trap and the activation delay.
     *    - The key insight is that to return safely, the trap must not be active when entering the room on the way back.
     * 3. The final answer is the minimum of these calculated k values.
     *
     * Time Complexity: O(n) per test case (since we process n traps once).
     * Space Complexity: O(1) (we use only a few variables, no extra data structures).
     */
    
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine());
      short ansi = 299; // Initialize with a large enough value, since the maximum possible k should not exceed 299 based on constraints.
      for (byte j = 0; j < n; j++) {
        string[] parts = Console.ReadLine().Split();
        byte dj = byte.Parse(parts[0]); // Position of the trap
        byte sj = byte.Parse(parts[1]); // Time delay for trap activation
        // Calculate the maximum safe k for the current trap.
        // If sj is even, we divide by 2 and subtract 1; else, just divide by 2.
        short k = Convert.ToInt16(dj + (sj % 2 == 0 ? sj / 2 - 1 : sj / 2));
        if (k < ansi) // Update the maximum safe k
          ansi = k;
      }
      ans.Append(ansi);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}

// https://github.com/VaHiX/CodeForces/