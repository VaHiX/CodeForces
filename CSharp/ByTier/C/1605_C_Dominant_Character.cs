// Problem: CF 1605 C - Dominant Character
// https://codeforces.com/contest/1605/problem/C

﻿/*
Problem: Find the length of the smallest substring where 'a' occurs strictly more times than both 'b' and 'c', and substring length is at least 2.

Algorithms/Techniques:
- Pre-defined valid substrings approach
- Brute force checking against a predefined list of valid patterns

Time Complexity: O(n * m) where n is the length of input string and m is the number of predefined patterns (constant = 7)
Space Complexity: O(1) as we use only a fixed-size list of patterns

The solution uses a pre-computed list of valid substrings that satisfy the given conditions.
*/
using System;
using System.Collections.Generic;
using System.Linq;

namespace VaHiX
{
    class Program
    {
        static void Main()
        {
            int numberOfTestCases = Convert.ToInt32(Console.ReadLine());
            // Predefined list of valid substrings that satisfy the conditions
            var validTemp = new List<string>()
            {
                "aa",
                "aba",
                "aca",
                "abca",
                "acba",
                "abbacca",
                "accabba",
            };
            int lenghtOfString = 0;
            string inputString = "";
            var check = false;
            while (numberOfTestCases > 0)
            {
                lenghtOfString = Convert.ToInt32(Console.ReadLine());
                inputString = Console.ReadLine();
                // Check if any of the predefined valid substrings exist in the input
                for (var i = 0; i < validTemp.Count; i++)
                {
                    if (inputString.Contains(validTemp[i]))
                    {
                        check = true;
                        Console.WriteLine(validTemp[i].Length);
                        break;
                    }
                }
                // If no valid substring found, output -1
                if (!check)
                    Console.WriteLine(-1);
                check = false;
                numberOfTestCases--;
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/
