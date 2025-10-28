// Problem: CF 2062 A - String
// https://codeforces.com/contest/2062/problem/A

/*
 * Problem: Minimum Operations to Convert String to All Zeros
 * 
 * Purpose: Given a binary string of '0's and '1's, determine the minimum number
 *          of operations needed to convert all characters to '0'. Each operation
 *          allows selecting a subsequence where no two adjacent characters are the same,
 *          then flipping all those characters (0->1, 1->0).
 * 
 * Algorithm/Techniques:
 *   - Greedy approach: Count the number of groups of consecutive '1's.
 *     Each group requires exactly one operation to flip all its '1's to '0'.
 *     This is because we can always select a subsequence that includes only
 *     one character from each contiguous block of '1's.
 *
 * Time Complexity: O(n), where n is the length of the input string.
 * Space Complexity: O(1), only using constant extra space.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1 {
    class A2026_String {
        static void Main(string[] args) {
            int t, n, m, result = 0;
            t = int.Parse(Console.ReadLine()); // Read number of test cases
            string input;
            while (t-- > 0) { // Process each test case
                n = 0; // Initialize count of 1s
                input = Console.ReadLine(); // Read the input string
                for (int i = 0; i < input.Length; i++) { // Iterate through the string
                    if (input[i] == '1') // If current character is '1'
                        n++; // Increment counter
                }
                Console.WriteLine(n); // Output number of 1s (minimum operations needed)
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/