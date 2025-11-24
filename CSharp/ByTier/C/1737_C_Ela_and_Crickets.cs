// Problem: CF 1737 C - Ela and Crickets
// https://codeforces.com/contest/1737/problem/C

// Problem: C. Ela and Crickets
// Algorithm: Check if a cricket can reach a target square based on L-shape configuration and movement rules.
// Time Complexity: O(1) per test case - constant time operations.
// Space Complexity: O(1) - only using a fixed-size hash set and a few variables.
using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO.Pipes;
using System.Linq;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CodeForces
{
    internal class Program
    {
        public static long lux(long num)
        {
            if (num == 0)
                return 0;
            long ch = 0;
            long sqr = (long)Math.Sqrt(num) * (long)Math.Sqrt(num);
            ch = ((long)Math.Sqrt(num) - 1) * 3;
            ch += ((num - sqr) / (long)Math.Sqrt(num));
            return ++ch;
        }

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
                int[] arr = Read.Ints();
                int[] inp = Read.Ints();
                int x = inp[0];
                int y = inp[1];
                int[] r = new int[3];
                int[] c = new int[3];
                r[0] = arr[0];
                r[1] = arr[2];
                r[2] = arr[4];
                c[0] = arr[1];
                c[1] = arr[3];
                c[2] = arr[5];
                HashSet<KeyValuePair<int, int>> ch = new HashSet<KeyValuePair<int, int>>();
                for (int i = 0; i < 3; i++)
                    ch.Add(new KeyValuePair<int, int>(r[i], c[i]));
                int ans = 0;
                // Check if all three crickets are at the corner (1,1)
                if (ch.Contains(new KeyValuePair<int, int>(1, 1)))
                    ans++;
                if (ch.Contains(new KeyValuePair<int, int>(1, 2)))
                    ans++;
                if (ch.Contains(new KeyValuePair<int, int>(2, 1)))
                    ans++;
                if (ans == 3)
                {
                    // If so, we can reach squares at the edge of the board
                    if (x - 1 == 0 || y - 1 == 0)
                        results.Add("YES");
                    else
                        results.Add("NO");
                    continue;
                }
                int pro = 9;
                // Check if all three crickets are at the corner (1,n)
                if (ch.Contains(new KeyValuePair<int, int>(1, n)))
                    ans++;
                if (ch.Contains(new KeyValuePair<int, int>(1, n - 1)))
                    ans++;
                if (ch.Contains(new KeyValuePair<int, int>(2, n)))
                    ans++;
                if (ans == 3)
                {
                    // If so, we can reach squares at the edge of the board
                    if (x - 1 == 0 || y - n == 0)
                        results.Add("YES");
                    else
                        results.Add("NO");
                    continue;
                }
                pro++;
                // Check if all three crickets are at the corner (n,1)
                if (ch.Contains(new KeyValuePair<int, int>(n, 1)))
                    ans++;
                if (ch.Contains(new KeyValuePair<int, int>(n, 2)))
                    ans++;
                if (ch.Contains(new KeyValuePair<int, int>(n - 1, 1)))
                    ans++;
                if (ans == 3)
                {
                    // If so, we can reach squares at the edge of the board
                    if (x - n == 0 || y - 1 == 0)
                        results.Add("YES");
                    else
                        results.Add("NO");
                    continue;
                }
                int calc = 0;
                // Check if all three crickets are at the corner (n,n)
                if (ch.Contains(new KeyValuePair<int, int>(n, n)))
                    ans++;
                if (ch.Contains(new KeyValuePair<int, int>(n, n - 1)))
                    ans++;
                if (ch.Contains(new KeyValuePair<int, int>(n - 1, n)))
                    ans++;
                calc++;
                if (ans == 3)
                {
                    // If so, we can reach squares at the edge of the board
                    if (x - n == 0 || y - n == 0)
                        results.Add("YES");
                    else
                        results.Add("NO");
                    continue;
                }
                calc++;
                int ch1 = 0,
                    ch2 = 0;
                // Determine which row has two identical crickets
                if (r[0] == r[1])
                    ch1 = r[0];
                else
                    ch1 = r[2];
                // Determine which column has two identical crickets
                if (c[0] == c[1])
                    ch2 = c[0];
                else
                    ch2 = c[2];
                // If the target square has the same parity as the unique cricket's position, then it's reachable
                if (x % 2 != ch1 % 2 && y % 2 != ch2 % 2)
                {
                    results.Add("NO");
                    continue;
                }
                results.Add("YES");
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
