// Problem: CF 2000 A - Primary Task
// https://codeforces.com/contest/2000/problem/A

/*
 * Problem: Determine if a given integer could represent 10^x where x >= 2,
 * but written without the '^' symbol (e.g., "105" instead of "10^5").
 *
 * Algorithm:
 * - For each input string:
 *   - If length <= 2, output "NO"
 *   - If first two characters are "10":
 *     - If third character is '0' OR if third character is '1' and length == 3, output "NO"
 *     - Else, output "YES"
 *   - Else, output "NO"
 *
 * Time Complexity: O(n), where n is the total number of characters across all inputs.
 * Space Complexity: O(1), excluding input storage.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PrimaryTask {
    internal class Program {
        static void Main(string[] args) {
            int limit = int.Parse(Console.ReadLine()); // Read number of test cases
            for (int i = 0; i < limit; i++) { // Process each test case
                Solve(); // Solve current test case
            }
        }

        static void Solve() {
            string input = Console.ReadLine(); // Read the input string

            if (input.Length <= 2) { // If length is less than or equal to 2, it can't be 10^x for x>=2
                Console.WriteLine("NO");
                return;
            }

            if (input.Substring(0, 2) == "10") { // Check if the string starts with "10"
                if (input[2] == '0' || (input[2] == '1' && input.Length == 3)) { // Special invalid cases
                    Console.WriteLine("NO");
                } else {
                    Console.WriteLine("YES"); // Valid case like "101", "102", etc.
                }
            } else {
                Console.WriteLine("NO"); // Not starting with "10" -> invalid
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/