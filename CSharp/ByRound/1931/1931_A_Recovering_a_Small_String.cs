// Problem: CF 1931 A - Recovering a Small String
// https://codeforces.com/contest/1931/problem/A

﻿/*
 * Problem: Recovering a Small String
 * 
 * Algorithm/Techniques:
 * - Greedy approach to construct the lexicographically smallest 3-letter string
 *   that sums to the given encoded value.
 * 
 * Time Complexity: O(1) per test case (since we iterate at most 2 times for the 3 characters)
 * Space Complexity: O(1) (fixed-size character array and string)
 * 
 * Approach:
 * - Start with the smallest possible 3-letter string "aaa" (sum = 3).
 * - Subtract 3 from the target sum to get the remaining value to distribute.
 * - Distribute the remaining value from the rightmost character to the leftmost,
 *   maximizing the rightmost characters to keep the overall lexicographical order minimal.
 * - Use greedy logic: fill the rightmost positions with 'z' (26) as much as possible,
 *   and then adjust the leftmost character accordingly.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NewContest {
    internal class Program {
        static void Main(string[] args) {
            int t = int.Parse(Console.ReadLine()); // Read number of test cases
            for (int i = 0; i < t; i++) {
                string input = Console.ReadLine();
                int strValue = int.Parse(input); // Read the encoded value
                char[] chars = { 'a', 'a', 'a' }; // Initialize with smallest possible 3-letter string
                strValue -= 3; // Reduce by 3 since 'a' contributes 1 each, so total 3
                int pos = 2; // Start from the last character (rightmost)
                while (strValue > 0) { // Distribute remaining value
                    if (strValue > 25) { // If remaining value is more than 25 (max 'z' value)
                        strValue -= 25; // Deduct 25 (i.e., assign 'z')
                        chars[pos] = 'z'; // Assign 'z' to current position
                        pos--; // Move to the left
                    } else {
                        chars[pos] = (char)('a' + strValue); // Assign the required character
                        strValue = 0; // Finish the loop
                        break;
                    }
                }
                string answer = "";
                for (int j = 0; j < chars.Length; j++) {
                    answer += chars[j]; // Build the final string
                }
                Console.WriteLine(answer);
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/