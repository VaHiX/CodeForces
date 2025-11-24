// Problem: CF 1742 F - Smaller
// https://codeforces.com/contest/1742/problem/F

﻿/*
 * Problem: F. Smaller - Determine if string s can be rearranged to be lexicographically smaller than string t after operations.
 * 
 * Approach:
 * - We maintain counts of 'a' characters in both strings s and t.
 * - We also track whether either string contains non-'a' characters.
 * - For each operation:
 *   - If t already has a non-'a' character, we can always make s smaller -> "YES"
 *   - Otherwise, update the counts based on the operation type and the characters in x.
 *   - If s has a non-'a' character, we cannot make it smaller -> "NO"
 *   - If both are made entirely of 'a's, check if s has fewer 'a's than t -> "YES" if true, else "NO"
 * 
 * Time Complexity: O(n) where n is the total length of all input strings
 * Space Complexity: O(1) as we only use a few variables regardless of input size
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LessThanString1742F {
    class Program {
        static void Main(string[] args) {
            int t = Int32.Parse(Console.ReadLine());
            for (int p = 0; p < t; p++) {
                int q = Int32.Parse(Console.ReadLine());
                long aCount1 = 1; // Count of 'a' in string s
                long aCount2 = 1; // Count of 'a' in string t
                bool word1HasNotA = false; // Whether string s has a non-'a' character
                bool word2HasNotA = false; // Whether string t has a non-'a' character
                
                for (int query = 0; query < q; query++) {
                    string[] input = Console.ReadLine().Split(' ');
                    byte op = Byte.Parse(input[0]); // Operation type: 1 for s, 2 for t
                    int amount = Int32.Parse(input[1]); // Number of times to append string x
                    
                    // If t already has a non-'a' character, we can rearrange s to be smaller
                    if (word2HasNotA) {
                        Console.WriteLine("YES");
                    } else {
                        // Process the operation based on type (1 for s, 2 for t)
                        if (op == 1) {
                            // For s: update counts for 'a' and check for other characters
                            foreach (char c in input[2]) {
                                if (c == 'a')
                                    aCount1 += amount;
                                else
                                    word1HasNotA = true;
                            }
                        } else {
                            // For t: update counts for 'a' and check for other characters
                            foreach (char c in input[2]) {
                                if (c == 'a')
                                    aCount2 += amount;
                                else
                                    word2HasNotA = true;
                            }
                        }
                        
                        // After updating, check if s can be made smaller than t
                        if (word2HasNotA) {
                            Console.WriteLine("YES");
                        } else if (word1HasNotA) {
                            Console.WriteLine("NO");
                        } else if (aCount1 < aCount2) {
                            Console.WriteLine("YES");
                        } else {
                            Console.WriteLine("NO");
                        }
                    }
                }
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/