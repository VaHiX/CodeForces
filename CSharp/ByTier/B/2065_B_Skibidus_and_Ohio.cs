// Problem: CF 2065 B - Skibidus and Ohio
// https://codeforces.com/contest/2065/problem/B

/*
 * Problem: B. Skibidus and Ohio
 * Purpose: Given a string of lowercase Latin letters, determine the minimum possible length
 *          after performing allowed operations. An operation allows replacing a character 
 *          at position i (where s[i] == s[i+1]) with any other lowercase letter and removing s[i+1].
 * 
 * Algorithm:
 * - For each test case, count how many adjacent duplicate characters exist.
 * - If there are duplicates, we can reduce the string to a single character by performing
 *   operations on adjacent duplicates. The minimum length will be 1 if any adjacent duplicates exist,
 *   otherwise it's the original string length.
 * 
 * Time Complexity: O(n) for each test case, where n is the length of the string.
 * Space Complexity: O(1), only using a few variables for counting and processing.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1 {
    internal class Program {
        static void Main(string[] args) {
            int i = int.Parse(Console.ReadLine()); // Read number of test cases
            string n;
            for (var j = 0; j < i; j++) {
                int coun = 0; // Counter for adjacent duplicates
                n = Console.ReadLine(); // Read the input string
                
                // Loop through the string to count adjacent duplicates
                for (var c = 0; c < n.Length - 1; c++) {
                    if (n[c] == n[c + 1]) { // If current and next characters are equal
                        coun++; // Increment counter
                    }
                }
                
                // If there is at least one pair of adjacent duplicates, we can reduce the string to length 1
                // Otherwise, the minimum possible length is the original string length
                Console.WriteLine(coun > 0 ? 1 : n.Length);
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/