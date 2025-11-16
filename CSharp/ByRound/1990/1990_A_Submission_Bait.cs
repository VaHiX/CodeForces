// Problem: CF 1990 A - Submission Bait
// https://codeforces.com/contest/1990/problem/A

/*
 * Problem: A. Submission Bait
 *
 * Algorithm/Technique: Game Theory, Greedy
 *
 * Time Complexity: O(n), where n is the size of the array. We iterate through the array once to count frequencies,
 * and then iterate through the frequency array (size up to 51) which is constant time.
 *
 * Space Complexity: O(1), since we use a fixed-size array of size 51 to store frequencies, independent of input size.
 *
 * Approach:
 * - Count how many times each number appears in the array.
 * - The key insight is that the game is about parity (odd vs even) of counts of each number.
 * - Alice wins if there exists any number that appears an odd number of times.
 *   Because Bob will always mirror Alice's moves, and when it's Alice's turn to play, if the count of a number is odd,
 *   it means there's always at least one move available for Alice, ensuring she can win.
 */

using System;
using System.IO.Pipes;
using System.Security.Policy;

namespace CF_Practice
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            int T = int.Parse(Console.ReadLine()); // Read number of test cases
            for (int t = 0; t < T; t++)
            {
                int n = int.Parse(Console.ReadLine()); // Read size of array
                string[] token = Console.ReadLine().Split(); // Read array elements
                int[] indices = new int[51]; // Array to count frequency of each number (1 to 50)
                for (int i = 0; i < n; i++)
                {
                    int num = int.Parse(token[i]);
                    indices[num]++; // Increment count for the value
                }
                string ans = "NO"; // Default answer is No
                for (int i = indices.Length - 1; i >= 0; i--)
                {
                    if (indices[i] > 0)
                    { // If this number appears at least once
                        if (indices[i] % 2 != 0)
                        { // If the count is odd
                            ans = "YES"; // Alice wins
                            break;
                        }
                    }
                }
                Console.WriteLine(ans); // Output result for current test case
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/
