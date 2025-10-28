// Problem: CF 2038 L - Bridge Renovation
// https://codeforces.com/contest/2038/problem/L

/*
L. Bridge Renovation
Purpose:
This program calculates the minimum number of 60-unit long planks needed to cover three bridges of widths 18, 21, and 25 units,
with n planks required for each bridge. The algorithm uses a greedy approach to pack the required planks into as few standard
60-unit planks as possible.

Algorithms/Techniques:
- Greedy packing algorithm: For each new plank, attempt to fit as many of the required plank lengths (18, 21, 25) as possible
  in order of decreasing size to minimize waste and total planks used.
- Modular arithmetic and min() functions are used for efficient fitting.

Time Complexity: O(n) - Each unit of length is processed a constant number of times.
Space Complexity: O(1) - Only a fixed amount of integer variables are used.
*/

using System;
class Program {
  static void Main() {
    int n = int.Parse(Console.ReadLine()); // Read the number of planks needed for each bridge
    int total_18 = 18 * n;                 // Total length needed for 18-unit planks
    int total_21 = 21 * n;                 // Total length needed for 21-unit planks  
    int total_25 = 25 * n;                 // Total length needed for 25-unit planks
    int planksRequired = 0;                // Counter for number of standard planks used
    
    while (total_18 > 0 || total_21 > 0 || total_25 > 0) { // While we still have plank lengths to place
      planksRequired++;                    // Use another standard plank (60 units)
      int remainingLength = 60;            // Start with full plank length
      
      // Fit as many 25-unit planks as possible into the remaining space
      if (total_25 > 0) {
        int fit25 = Math.Min(total_25 / 25, remainingLength / 25); 
        total_25 -= fit25 * 25;            // Reduce the number of 25-unit planks needed
        remainingLength -= fit25 * 25;     // Reduce the available space
      }
      
      // Fit as many 21-unit planks as possible into the remaining space  
      if (total_21 > 0) {
        int fit21 = Math.Min(total_21 / 21, remainingLength / 21);
        total_21 -= fit21 * 21;
        remainingLength -= fit21 * 21;
      }
      
      // Fit as many 18-unit planks as possible into the remaining space
      if (total_18 > 0) {
        int fit18 = Math.Min(total_18 / 18, remainingLength / 18);
        total_18 -= fit18 * 18;
        remainingLength -= fit18 * 18;
      }
    }
    
    Console.WriteLine(planksRequired); // Output the minimum number of standard planks required
  }
}


// https://github.com/VaHiX/codeForces/