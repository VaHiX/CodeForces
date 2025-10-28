// Problem: CF 2051 C - Preparing for the Exam
// https://codeforces.com/contest/2051/problem/C

﻿/*
 * Problem: Preparing for the Exam
 * 
 * Purpose: Determine whether Monocarp can pass each exam list based on his known questions.
 * 
 * Approach:
 * - For each test case:
 *   - Read n (number of possible questions), m (number of lists), k (number of known questions)
 *   - Read the list of missing question indices (a_i)
 *   - Read the list of known questions (q_i)
 *   - Use a boolean array to mark known questions
 *   - For each list, check if the missing question is known:
 *     - If yes, he passes (output 1)
 *     - If no, he fails (output 0)
 * 
 * Time Complexity: O(n + m + k) per test case
 * Space Complexity: O(n) for the boolean array to store known questions
 * 
 * Algorithms/Techniques:
 * - Boolean array for fast lookup of known questions
 * - Single pass through lists to determine pass/fail
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

            for (int o = 0; o < t; o++) {
                string[] input = Console.ReadLine().Split(
                    new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                int n = int.Parse(input[0]); // Total number of questions
                int m = int.Parse(input[1]); // Number of lists
                int k = int.Parse(input[2]); // Number of known questions

                // Read the list of missing questions for each list
                input = Console.ReadLine().Split(new char[] { ' ' },
                                                 StringSplitOptions.RemoveEmptyEntries);
                int[] arrayA = new int[m]; // arrayA[i] is the missing question for list i
                for (int i = 0; i < m; i++) {
                    arrayA[i] = int.Parse(input[i]);
                }

                // Read the list of known questions
                input = Console.ReadLine().Split(new char[] { ' ' },
                                                 StringSplitOptions.RemoveEmptyEntries);
                int[] arrayQ = new int[k]; // arrayQ[i] is a known question
                for (int i = 0; i < k; i++) {
                    arrayQ[i] = int.Parse(input[i]);
                }

                // If k < n - 1, there are more questions in a list than known
                // so he cannot pass any list
                if (k < n - 1) {
                    for (int i = 0; i < m; i++) {
                        Console.Write("0");
                    }
                }
                // If k > n - 1, he knows more questions than are missing in a list
                // so he can pass all lists
                else if (k > n - 1) {
                    for (int i = 0; i < m; i++) {
                        Console.Write("1");
                    }
                }
                // If k == n - 1, he knows exactly the number of questions in a list
                // so we need to check each list individually
                else {
                    int wrongQuestion = -1;
                    bool[] know = new bool[n]; // Boolean array to mark known questions
                    for (int i = 0; i < k; i++) {
                        know[arrayQ[i] - 1] = true; // Mark question as known (0-indexed)
                    }
                    for (int i = 0; i < m; i++) {
                        // If the missing question is not known, he passes the list
                        if (!know[arrayA[i] - 1]) {
                            Console.Write("1");
                        } else {
                            // If he knows the missing question, he fails
                            Console.Write("0");
                        }
                    }
                }
                Console.WriteLine(); // End of line for current test case
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/