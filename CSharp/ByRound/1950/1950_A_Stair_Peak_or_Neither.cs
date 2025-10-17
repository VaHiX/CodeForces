// Problem: CF 1950 A - Stair, Peak, or Neither?
// https://codeforces.com/contest/1950/problem/A

/*
 * Problem: Determine if three digits form a stair, a peak, or neither.
 * 
 * Algorithms/Techniques: 
 * - Direct conditional checks based on the given definitions:
 *   - Stair: a < b < c
 *   - Peak: a < b > c
 * 
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), only using a fixed amount of variables.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Olympiad {
    internal class Program {
        static void Main(string[] args) {
            int a, b, c;
            int n = Convert.ToInt32(Console.ReadLine()); // Read number of test cases
            
            for (int i = 0; i < n; i++) {
                string[] s = Console.ReadLine().Split(' '); // Read the three digits
                a = int.Parse(s[0]); // Parse first digit
                b = int.Parse(s[1]); // Parse second digit
                c = int.Parse(s[2]); // Parse third digit
                
                // Check if the digits form a stair (strictly increasing)
                if (a < b && b < c) {
                    Console.WriteLine("STAIR");
                }
                // Check if the digits form a peak (increasing then decreasing)
                else if (a < b && b > c) {
                    Console.WriteLine("PEAK");
                }
                // Otherwise, it's neither
                else {
                    Console.WriteLine("NONE");
                }
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/