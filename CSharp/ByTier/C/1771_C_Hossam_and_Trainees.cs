// Problem: CF 1771 C - Hossam and Trainees
// https://codeforces.com/contest/1771/problem/C

﻿/*
 * Problem: C. Hossam and Trainees
 *
 * Purpose: Determine if there exists a pair of trainees whose assigned numbers have a common divisor greater than 1.
 *
 * Algorithm:
 * - For each number, we find its prime factors.
 * - We use a sorted set to keep track of already seen prime factors.
 * - If a prime factor is already in the set, then we found a successful pair.
 * - This avoids checking all pairs directly, which would be too slow.
 *
 * Time Complexity: O(n * sqrt(max_a) + π(max_a) * sqrt(max_a)) where π(max_a) is the number of primes up to sqrt(max_a)
 * Space Complexity: O(π(max_a) + n) for storing primes and the input array
 *
 * Techniques:
 * - Precomputed primes up to 32000 using Sieve of Eratosthenes
 * - Prime factorization with early termination
 * - SortedSet to efficiently check for duplicates
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace Compete2
{
    partial class MainClass
    {
        public static void Main(string[] args)
        {
            int count = int.Parse(Console.ReadLine());
            List<string> output = new List<string>();
            List<int> primes = new List<int>();
            primes.Add(2);
            for (int i = 3; i < 32000; i++)
            {
                bool add = true;
                for (int j = 0; j < primes.Count; j++)
                {
                    if (i % primes[j] == 0)
                    {
                        add = false;
                        break;
                    }
                }
                if (add)
                    primes.Add(i);
            }
            for (int z = 0; z < count; z++)
            {
                var n = int.Parse(Console.ReadLine());
                var a = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
                bool can = false;
                SortedSet<long> div = new SortedSet<long>();
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < primes.Count; j++)
                    {
                        long k = primes[j];
                        if (a[i] < k)
                        {
                            break;
                        }
                        if (a[i] % k == 0)
                        {
                            if (div.Contains(k))
                            {
                                can = true;
                                break;
                            }
                            else
                                div.Add(k);
                            a[i] /= k;
                            while (a[i] % k == 0)
                                a[i] /= k;
                        }
                    }
                    if (a[i] > 1)
                    {
                        if (div.Contains(a[i]))
                        {
                            can = true;
                        }
                        else
                            div.Add(a[i]);
                    }
                    if (can)
                        break;
                }
                if (can)
                    output.Add("YES");
                else
                    output.Add("NO");
            }
            string on = string.Join("\n", output);
            Console.WriteLine(on);
        }
    }
}


// https://github.com/VaHiX/CodeForces/
