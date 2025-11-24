// Problem: CF 2041 E - Beautiful Array
// https://codeforces.com/contest/2041/problem/E

/*
 * Problem: E. Beautiful Array
 * Purpose: Generate an array with specified mean 'a' and median 'b'.
 * Algorithms/Techniques:
 *   - Direct construction approach based on cases
 *   - Simple arithmetic manipulation to satisfy mean and median constraints
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - fixed size array used
 *
 * The solution constructs a 3-element array that satisfies:
 *   - Mean = a (sum/3 = a => sum = 3*a)
 *   - Median = b (middle element when sorted)
 *
 * Cases handled:
 *   - When a >= 0 and b < 0: uses b - delta, b, |b| + 2*delta
 *   - When delta < 0: uses b, b, -b + delta
 *   - Otherwise: uses b - 2*b, b, b + delta
 *
 * Delta = 3*a - b, which is derived from mean constraint.
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

public class Program
{
    public static void Main()
    {
        // Read input values a and b
        float[] nums = Console.ReadLine().Split(' ').Select(x => float.Parse(x)).ToArray();
        float a = nums[0];
        float b = nums[1];

        // Calculate delta based on mean constraint: 3*a = sum, so delta = 3*a - b
        float delta = a * 3 - b;

        float[] ans;

        // Case 1: When a >= 0 and b < 0
        // Construct array using: b - delta, b, |b| + 2*delta
        if (a >= 0 && b < 0)
            ans = new[] { b - delta, b, Math.Abs(b) + 2 * delta };
        // Case 2: When delta < 0
        // Construct array using: b, b, -b + delta
        else if (delta < 0)
            ans = new[] { b, b, -b + delta };
        // Case 3: Default case
        // Construct array using: b - 2*b, b, b + delta
        else
            ans = new[] { b - 2 * b, b, b + delta };

        // Output the length of the array (always 3)
        Console.WriteLine(3);

        // Output all elements of the array
        foreach (var elem in ans)
            Console.Write(elem + " ");
    }
}


// https://github.com/VaHiX/CodeForces/
