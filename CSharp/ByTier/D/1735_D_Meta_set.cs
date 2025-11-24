// Problem: CF 1735 D - Meta-set
// https://codeforces.com/contest/1735/problem/D

/// <summary>
/// Problem: Meta-set
///
/// Algorithm:
/// - For each pair of cards, compute the third card that would form a valid Set
/// - Use hash table to count occurrences of each card
/// - For each valid Set (three cards that form a set), increment counts in map2
/// - Count meta-sets by counting combinations of 3 cards from each group
///
/// Time Complexity: O(n^2 * k) where n is number of cards and k is number of features
/// Space Complexity: O(n) for hash tables storing counts
/// </summary>
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
            bool multiTests = false;
            long tests = 1;
            if (multiTests)
                tests = Read.Long();
            List<int> results = new List<int>();
            while (tests-- > 0)
            {
                int[] inp = Read.Ints();
                int n = inp[0];
                int k = inp[1];
                int[,] table = new int[n, k];
                Dictionary<int, int> map1 = new Dictionary<int, int>(),
                    map2 = new Dictionary<int, int>();
                int[] ch2 = Enumerable.Repeat<int>(0, n + 1).ToArray();
                int ch = 0;
                for (int i = 0; i < n; i++)
                {
                    int tmpnum = 0;
                    int sad = 1;
                    int[] tmp = Read.Ints();
                    for (int j = 0; j < k; j++)
                    {
                        table[i, j] = tmp[j];
                        tmpnum = tmpnum * 3 + table[i, j]; // Convert card to base 3 number
                    }
                    if (!map1.ContainsKey(tmpnum))
                        map1[tmpnum] = 1;
                    else
                        map1[tmpnum]++;
                    ch2[i] = tmpnum; // Store the base 3 representation
                }
                int u = 1;
                for (int i = 0; i < n - 1; i++)
                {
                    for (int j = i + 1; j < n; j++)
                    {
                        int tmpnum = 0;
                        for (int e = 0; e < k; e++)
                        {
                            tmpnum *= 3;
                            if (table[i, e] == table[j, e])
                                tmpnum += table[i, e];
                            else
                                tmpnum += 3 - table[i, e] - table[j, e]; // Compute third card feature
                        }
                        if (!map1.ContainsKey(tmpnum))
                            continue;
                        int sa = map1[tmpnum];
                        if (!map2.ContainsKey(ch2[i]))
                            map2[ch2[i]] = sa;
                        else
                            map2[ch2[i]] += sa;
                        if (!map2.ContainsKey(ch2[j]))
                            map2[ch2[j]] = sa;
                        else
                            map2[ch2[j]] += sa;
                        if (!map2.ContainsKey(tmpnum))
                            map2[tmpnum] = sa;
                        else
                            map2[tmpnum] += sa;
                    }
                }
                // Count meta-sets by computing combinations of 3 cards from each valid set
                foreach (var iter in map2)
                {
                    ch += iter.Value / 3 * (iter.Value / 3 - 1) / 2;
                }
                results.Add(ch);
            }
            Console.ForegroundColor = ConsoleColor.Cyan;
            wl(String.Join("\n", results));
            Console.ForegroundColor = ConsoleColor.Gray;
        }

        public static int hashIt(int[] arr, int ind)
        {
            int count = 0;
            int chsa = 021;
            int j = ind;
            while (j != -1)
            {
                count++;
                j = arr[j];
                if (j == ind)
                    return count;
            }
            return -1;
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
