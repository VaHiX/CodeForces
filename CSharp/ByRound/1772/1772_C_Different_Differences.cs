// Problem: CF 1772 C - Different Differences
// https://codeforces.com/contest/1772/problem/C

// ------------------------------------------------------------------------------------------------
// Problem: Construct a strictly increasing array of k integers from 1 to n with maximum possible characteristic.
// Algorithm:
//   - Use a greedy approach to build an array with distinct differences.
//   - Generate a sequence of cumulative sums (1, 1+2, 1+2+3, ...) to maximize distinct differences.
//   - Adjust the array to fit within [1, n] and ensure exactly k elements.
// Time Complexity: O(k) per test case, due to the generation of cumulative sums and adjustments.
// Space Complexity: O(k) for storing the result and intermediate arrays.
// ------------------------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;

class prog
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        List<int> l = new List<int>(); // List to store cumulative sums (1, 3, 6, 10, ...)
        int p = 1,
            u = 1;
        while (p <= 400)
        { // Generate cumulative sums up to 400 (sufficient for k <= 40)
            l.Add(p);
            p += u;
            u++;
        }
        while (t-- > 0)
        {
            string[] s = Console.ReadLine().Split(' ');
            int k = int.Parse(s[0]); // Number of elements in the array
            int n = int.Parse(s[1]); // Upper bound of the array values
            List<int> o = new List<int>(); // Resulting array for current test case
            for (int i = 0; i < l.Count; i++)
            {
                if (l[i] >= n)
                { // If cumulative sum exceeds n, clamp to n
                    o.Add(n);
                    break;
                }
                else
                    o.Add(l[i]); // Otherwise, add the cumulative sum
            }
            int y = 1;
            if (k < o.Count)
            { // If more elements than needed, remove excess from the end
                while (o.Count > k)
                    o.RemoveAt(o.Count - 2);
            }
            else if (k > o.Count)
            { // If fewer elements than needed, pad with descending values
                while (o.Count < k)
                {
                    o.Add(n - (y++)); // Add values starting from n downwards
                    o = o.Distinct().ToList(); // Remove duplicates to maintain strict increase
                }
            }
            o.Sort(); // Sort the result to ensure strictly increasing order
            Console.Write(o[0]);
            o.RemoveAt(0);
            foreach (int i in o)
                Console.Write(" " + i);
            Console.WriteLine();
        }
    }
}


// https://github.com/VaHiX/CodeForces/
