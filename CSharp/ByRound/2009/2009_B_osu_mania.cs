// Problem: CF 2009 B - osu!mania
// https://codeforces.com/contest/2009/problem/B

/*
 * Problem: B. osu!mania
 * Purpose: Process a rhythm game beatmap with n rows and 4 columns, where each row contains exactly one note ('#').
 *          Output the column number (1-indexed) of each note in order from bottom to top.
 * 
 * Algorithms/Techniques:
 * - Iterative parsing of input rows
 * - Linear search for '#' character in each row
 * - Reverse order output using list traversal
 * 
 * Time Complexity: O(n * m) where n is the number of rows and m is the number of columns (fixed at 4)
 * Space Complexity: O(n) for storing the column positions of notes
 */

using System;
using System.Collections.Generic;

namespace HelloWorld {
    public class Program {
        public static void Main() {
            int a = int.Parse(Console.ReadLine()); // Read number of test cases
            for (int i = 0; i < a; i++) {
                int b = int.Parse(Console.ReadLine()); // Read number of rows for current test case
                List<int> list = new List<int>(); // Store column positions of notes
                
                for (int j = 0; j < b; j++) {
                    string s = Console.ReadLine(); // Read each row
                    for (int k = 0; k < s.Length; k++) { // Scan through each character in the row
                        if (s[k] == '#') { // If we find a note
                            list.Add(k + 1); // Add its 1-indexed column position to the list
                        }
                    }
                }
                
                // Print results in reverse order (since last row processed is first in output)
                for (int t = list.Count - 1; t >= 0; t--) {
                    if (t == 0) {
                        Console.WriteLine(list[t]);
                    } else {
                        Console.Write(list[t] + " ");
                    }
                }
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/