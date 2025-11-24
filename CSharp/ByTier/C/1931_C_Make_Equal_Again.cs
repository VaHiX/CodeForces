// Problem: CF 1931 C - Make Equal Again
// https://codeforces.com/contest/1931/problem/C
/*
Purpose: The code solves the problem of making all elements of an array equal by applying one operation that replaces a subarray with a value. The goal is to minimize the cost of this operation.

Algorithms/Techniques:
- Greedy approach with prefix and suffix counting.
- Identification of leftmost and rightmost equal elements to determine minimal cost.

Time Complexity: O(n) for each test case, where n is the size of the array. Each element is visited at most twice (once for left side, once for right side).
Space Complexity: O(n) for storing the input array.
*/

using System;

public class MakeEqualAgain
{
    public static void Main()
    {
        short t = short.Parse(Console.ReadLine());
        for (short i = 0; i < t; i++)
        {
            int n = int.Parse(Console.ReadLine());
            string[] parts = Console.ReadLine().Split();
            int[] a = new int[n];
            for (int j = 0; j < n; j++)
                a[j] = int.Parse(parts[j]);
            int countLeftEqu = 1;
            for (int j = 1; j < n && a[j] == a[0]; j++)
                countLeftEqu++; // Count leftmost equal elements from index 0
            int ans = 0;
            if (countLeftEqu < n)
            { // If not all elements are equal
                int countRightEqu = 1;
                for (int j = n - 2; j > -1 && a[j] == a[n - 1]; j--)
                    countRightEqu++; // Count rightmost equal elements from index n-1
                ans = (
                    a[0] == a[n - 1]
                        ? n - (countLeftEqu + countRightEqu)
                        : n - Math.Max(countLeftEqu, countRightEqu)
                ); // Calculate minimum cost
            }
            Console.WriteLine(ans);
        }
    }
}


// https://github.com/VaHiX/CodeForces/
