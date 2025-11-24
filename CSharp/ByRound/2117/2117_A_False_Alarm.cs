// Problem: CF 2117 A - False Alarm
// https://codeforces.com/contest/2117/problem/A

/*
 * Problem: A. False Alarm
 * Purpose: Determine if Yousef can pass through all doors in a hallway,
 *          given that he can use a special button once to open all closed doors for x seconds.
 * 
 * Algorithm:
 * - Use two pointers from the start and end of the door sequence.
 * - Move inward until both pointers find an open door (0) or reach the same point.
 * - The window between these pointers represents the minimum span that needs to be covered
 *   without using the button.
 * - If this span exceeds x, then it's impossible even with the button; otherwise, YES.
 * 
 * Time Complexity: O(n) for each test case, where n is the number of doors.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

using System;
namespace Problem_Solving {
class Program {
  static void Main(string[] args) {
    int t = Convert.ToInt32(Console.ReadLine()); // Read number of test cases
    for (int k = 0; k < t; k++) {
      int[] s = Array.ConvertAll(Console.ReadLine().Split(), int.Parse); // Read n and x
      int[] d = Array.ConvertAll(Console.ReadLine().Split(), int.Parse); // Read door states
      
      int ch = 0; // Variable to store the maximum window of consecutive closed doors
      for (int i = 0, j = s[0] - 1; i <= j;) {
        if (d[i] != 1) { // If current left door is open
          i++; // Move pointer forward
        }
        if (d[j] != 1) { // If current right door is open
          j--; // Move pointer backward
        }
        if (d[i] == 1 && d[j] == 1) { // Both sides point to closed doors
          ch = j - i + 1; // Calculate the subarray length with all closed doors
          break;
        }
      }
      if (ch > s[1]) { // If required time exceeds available button duration
        Console.WriteLine("NO");
      } else {
        Console.WriteLine("YES");
      }
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/