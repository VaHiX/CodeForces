// Problem: CF 1993 B - Parity and Sum
// https://codeforces.com/contest/1993/problem/B

/*
 * Problem: B. Parity and Sum
 *
 * Algorithm:
 * - Separate all numbers into two groups: even and odd.
 * - If all numbers already have the same parity, return 0.
 * - Otherwise, determine the minimum operations needed:
 *   - If the largest odd number is greater than the largest even number,
 *     we can convert all even numbers into odd by pairing them with the largest odd.
 *   - If the largest even number is greater than or equal to the largest odd number,
 *     we must convert all odd numbers into even.
 *     This requires pairing each odd number with some even number.
 *
 * Time Complexity: O(n log n) due to sorting operations
 * Space Complexity: O(n) for storing even and odd numbers
 */

using System;
using System.Collections.Generic;

class HelloWorld
{
    static void Main()
    {
        string s;
        string[] mas;
        List<long> chetno = new List<long>(); // List to store even numbers
        List<long> nechetno = new List<long>(); // List to store odd numbers
        int x = 0;
        int n = int.Parse(Console.ReadLine());
        int test = 0;
        for (int i = 0; i < n; i++)
        {
            test = 0;
            chetno.Clear(); // Clear the list of even numbers
            nechetno.Clear(); // Clear the list of odd numbers
            s = Console.ReadLine();
            x = int.Parse(s);
            s = Console.ReadLine();
            mas = s.Split(' ');
            for (int j = 0; j < x; j++)
            {
                if (int.Parse(mas[j]) % 2 == 0)
                    chetno.Add(long.Parse(mas[j])); // Add even number
                else
                    nechetno.Add(long.Parse(mas[j])); // Add odd number
            }
            chetno.Sort(); // Sort even numbers
            chetno.Reverse(); // Reverse to get descending order
            nechetno.Sort(); // Sort odd numbers
            nechetno.Reverse(); // Reverse to get descending order
            if (chetno.Count == 0 || nechetno.Count == 0)
                Console.WriteLine(0); // All numbers have same parity
            else
            {
                if (nechetno[0] > chetno[0])
                    Console.WriteLine(chetno.Count); // If largest odd > largest even, convert all even to odd
                else
                {
                    chetno.Reverse(); // Reverse back to ascending order for processing
                    for (int j = 0; j < chetno.Count; j++)
                    {
                        if (nechetno[0] < chetno[j])
                        {
                            test = 1; // Mark if we need an extra operation
                        }
                        nechetno[0] += chetno[j]; // Accumulate sum of even numbers into the largest odd
                    }
                    Console.WriteLine(chetno.Count + test); // Return total operations
                }
            }
            Console.WriteLine(); // Print empty line after each test case
        }
    }
}


// https://github.com/VaHiX/CodeForces/
