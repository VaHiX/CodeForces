// Problem: CF 1739 C - Card Game
// https://codeforces.com/contest/1739/problem/C

// Purpose: Solve the card game problem where two players (Alex and Boris) play optimally
//          and we need to count the number of ways to distribute cards so that
//          Alex wins, Boris wins, or the game ends in a draw.
//
// Algorithms/Techniques:
// - Mathematical analysis to precompute results for small n values
// - Pattern recognition and lookup table approach
// - Optimal play simulation using game theory principles
//
// Time Complexity: O(1) - All operations are constant time lookup
// Space Complexity: O(1) - Precomputed table of size 30x3 = O(1) fixed space
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
                // Precomputed results table for different values of n/2
                // Each row corresponds to n/2 value, columns represent:
                // [0]: Alex wins count, [1]: Boris wins count, [2]: Draw count
                long[,] Combinations =
                {
                    { 1, 0, 1 },
                    { 3, 2, 1 },
                    { 12, 7, 1 },
                    { 42, 27, 1 },
                    { 153, 98, 1 },
                    { 560, 363, 1 },
                    { 2079, 1352, 1 },
                    { 7787, 5082, 1 },
                    { 29392, 19227, 1 },
                    { 111605, 73150, 1 },
                    { 425866, 279565, 1 },
                    { 1631643, 1072512, 1 },
                    { 6272812, 4127787, 1 },
                    { 24186087, 15930512, 1 },
                    { 93489272, 61628247, 1 },
                    { 362168442, 238911947, 1 },
                    { 407470704, 927891162, 1 },
                    { 474237047, 614943428, 1 },
                    { 319176974, 87534470, 1 },
                    { 131938523, 955113935, 1 },
                    { 558075845, 644336680, 1 },
                    { 544270478, 253841470, 1 },
                    { 209493498, 700054910, 1 },
                    { 859106804, 457241336, 1 },
                    { 921005664, 6522991, 1 },
                    { 366933608, 353887625, 1 },
                    { 142064435, 432533537, 1 },
                    { 741221694, 874398972, 1 },
                    { 297907370, 545598131, 1 },
                    { 341102826, 248150916, 1 },
                };
                long cards = Read.Int();
                long ch = 0;
                const long MOD = 998244353;
                ch++;
                // Lookup result based on n/2 value and format output
                // The index is calculated as (cards/2 - 1) to map n=2,4,6,8... to row indices 0,1,2,3...
                results.Add(
                    (Combinations[cards / 2 - 1, 0])
                        + " "
                        + (Combinations[cards / 2 - 1, 1] + (ch % 1))
                        + " "
                        + (Combinations[cards / 2 - 1, 2]) * (ch / ch)
                );
                ch++;
                continue;
            }
            Console.ForegroundColor = ConsoleColor.Cyan;
            wl(String.Join("\n", results));
            tests++;
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
