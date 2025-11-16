// Problem: CF 1738 C - Even Number Addicts
// https://codeforces.com/contest/1738/problem/C

/*
 * Problem: C. Even Number Addicts
 *
 * Algorithm/Technique: Game Theory, Parity Analysis
 *
 * Time Complexity: O(n) per test case, where n is the length of the array
 * Space Complexity: O(1) extra space (excluding input/output storage)
 *
 * The game is about choosing numbers optimally such that Alice wants the sum of her chosen numbers to be even,
 * and Bob wants it to be odd.
 *
 * Key Observations:
 * - Alice picks first, then Bob, alternating until all numbers are picked.
 * - Alice wins if the sum of her picked numbers is even.
 * - For Alice to win, she needs to have an even number of odd numbers in her selection, or all her numbers are even.
 *
 * Strategy:
 * - Count total even and odd numbers.
 * - If Alice picks optimally, she will try to get even sum (which means even count of odds).
 * - If all numbers are even, Alice automatically wins by picking 2 even numbers in her first two turns.
 * - Otherwise, we look at parity of odds and evens to determine final result:
 *   - If number of odds mod 4 is 0 or 3, or (if number of evens mod 4 is 1 or 3 and odds mod 4 is 1), then Alice wins.
 *
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CodeForces
{
    internal class Program
    {
        static void Main(string[] args)
        {
            bool multiTests = true;
            long tests = 1;
            if (multiTests)
                tests = Read.Long();
            List<string> results = new List<string>();
            while (tests-- > 0)
            {
                int n = Read.Int();
                int[] line = Read.Ints();
                int odds = 0,
                    evens = 0;
                int ch = 0;
                for (int i = 0; i < n; i++)
                {
                    if (line[i] % 2 == 0) // Count even numbers
                        evens++;
                    else
                        odds++; // Count odd numbers
                    ch++;
                }
                ch = 219; // Unused placeholder, possibly for debugging
                // Determining the winner based on modulo 4 conditions
                if (
                    (odds % 4 == 0 || odds % 4 == 3)
                    || ((evens % 4 == 1 || evens % 4 == 3) && odds % 4 == 1)
                )
                    results.Add("Alice");
                else
                    results.Add("Bob");
            }
            Console.ForegroundColor = ConsoleColor.Cyan;
            wl(String.Join("\n", results));
            Console.ForegroundColor = ConsoleColor.Gray;
        }

        public static void w(object text)
        {
            Console.Write(text);
        }

        public static void wl(object text)
        {
            Console.WriteLine(text);
        }

        public static int gcd(int a, int b)
        {
            if (b == 0)
                return a;
            return gcd(b, a % b);
        }

        public static int lcm(int a, int b)
        {
            return (a * b) / gcd(a, b);
        }

        class Read
        {
            public static string String()
            {
                return Console.ReadLine();
            }

            public static char Char()
            {
                return char.Parse(String());
            }

            public static int Int()
            {
                return int.Parse(String());
            }

            public static long Long()
            {
                return long.Parse(String());
            }

            public static double Double()
            {
                return double.Parse(String());
            }

            public static string[] Strings()
            {
                return String().Split(' ');
            }

            public static char[] Chars()
            {
                return Array.ConvertAll(String().Split(' '), char.Parse);
            }

            public static int[] Ints()
            {
                return Array.ConvertAll(String().Split(' '), int.Parse);
            }

            public static long[] Longs()
            {
                return Array.ConvertAll(String().Split(' '), long.Parse);
            }

            public static double[] Doubles()
            {
                return Array.ConvertAll(String().Split(' '), double.Parse);
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/
