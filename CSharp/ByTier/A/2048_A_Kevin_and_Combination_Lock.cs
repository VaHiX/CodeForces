// Problem: CF 2048 A - Kevin and Combination Lock
// https://codeforces.com/contest/2048/problem/A

﻿/*
 * Problem: Kevin and Combination Lock
 * Algorithm/Technique: Mathematical Analysis
 * 
 * The problem involves determining whether a number x can be reduced to 0 using two allowed operations:
 * 1. If x ≠ 33, remove two consecutive '3's (e.g., "33" from "13323" becomes "123").
 * 2. If x ≥ 33, subtract 33 from x.
 * 
 * Key Insight:
 * - Operation 1 allows removing pairs of '3's.
 * - Operation 2 reduces the number by 33.
 * 
 * Observation:
 * A number can be reduced to zero if:
 * 1. It is divisible by 33 (so we can repeatedly apply operation 2).
 * OR  
 * 2. After removing all possible pairs of '3's, the resulting number is divisible by 33.
 * 
 * However, in this implementation, a simplified version works:
 * Since operation 1 essentially removes any two consecutive 3s and reduces the sum of digits,
 * and operation 2 subtracts 33 each time, a simpler check is sufficient.
 * 
 * The key simplification:
 * Any number that is divisible by 33 can be reduced to 0 using these rules.
 * This holds due to mathematical properties of numbers and modular arithmetic.
 * 
 * Time Complexity: O(1) - constant time for each test case.
 * Space Complexity: O(1) - constant space used.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp1 {
    class A2048_Kevin_and_Combination_Lock {
        static void Main(string[] args) {
            int t, n;
            t = int.Parse(Console.ReadLine()); // Read number of test cases
            while (t-- > 0) { // Process each test case
                n = int.Parse(Console.ReadLine()); // Read the current number x
                if (n % 33 == 0) { // Check if divisible by 33
                    Console.WriteLine("YES"); // If yes, it's possible to reduce to 0
                } else {
                    Console.WriteLine("NO"); // Otherwise not possible
                }
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/