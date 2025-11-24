// Problem: CF 1971 A - My First Sorting Problem
// https://codeforces.com/contest/1971/problem/A

/*
 * Problem: A. My First Sorting Problem
 * 
 * Purpose: This program takes pairs of integers and outputs them in sorted order (minimum followed by maximum).
 * 
 * Algorithms/Techniques: 
 *   - Simple comparison and sorting logic
 *   - Iteration over test cases and processing of each pair
 * 
 * Time Complexity: O(t), where t is the number of test cases. Each test case involves a constant-time operation.
 * Space Complexity: O(1), as we use only a fixed amount of extra space regardless of input size.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Contest_NO2 {
    class Program {
        static void Main(string[] args) {
            int cases = int.Parse(Console.ReadLine()); // Read number of test cases
            for (int i = 0; i < cases; i++) {
                string[] nums = Console.ReadLine().Split(' '); // Split input line into two strings
                int mayor = 0; // Variable to store maximum value
                int menor = 0; // Variable to store minimum value
                for (int j = 0; j < nums.Length - 1; j++) {
                    int chain0 = Convert.ToInt32(nums[0]); // Convert first number to integer
                    int chain1 = Convert.ToInt32(nums[1]); // Convert second number to integer
                    if (chain0 > chain1) {
                        mayor = chain0; // Assign larger value to mayor
                        menor = chain1; // Assign smaller value to menor
                    } else {
                        mayor = chain1; // Assign larger value to mayor
                        menor = chain0; // Assign smaller value to menor
                    }
                    Console.WriteLine(menor + " " + mayor); // Output the minimum followed by maximum
                }
            }
            Console.ReadLine(); // Wait for user input before closing
        }
    }
}


// https://github.com/VaHiX/CodeForces/