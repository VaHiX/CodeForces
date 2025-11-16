// Problem: CF 1770 C - Koxia and Number Theory
// https://codeforces.com/contest/1770/problem/C

/*
 * Problem: C. Koxia and Number Theory
 *
 * Purpose: Determine whether there exists a positive integer x such that
 *          gcd(a[i] + x, a[j] + x) = 1 for all 1 ≤ i < j ≤ n.
 *
 * Algorithm:
 * - For each pair (i, j), compute the difference d = |a[i] - a[j]|.
 * - For each such difference d > 1, find its prime divisors.
 * - For each prime p dividing d, we derive a modular constraint:
 *   if a[i] ≡ r (mod p), then a[j] ≡ (p - r) (mod p) for the condition to hold.
 * - Build buckets of constraints and check if any bucket has more elements than the modulus.
 *   If so, it's impossible to assign x such that all pairs are coprime.
 *
 * Time Complexity: O(n^2 * sqrt(max(a[i])) + P) where P is the number of primes up to sqrt(max(a[i]))
 * Space Complexity: O(n^2 + P) where P is the number of primes up to sqrt(max(a[i]))
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace Compete2
{
    partial class MainClass
    {
        public static List<long> primes = new List<long>();
        public static Dictionary<long, long[]> divisors = new Dictionary<long, long[]>();

        public static List<long> FindDivisors(long n)
        {
            long no = n;
            if (divisors.ContainsKey(n))
                return divisors[n].ToList();
            List<long> d = new List<long>();
            double l = Math.Min(10001, n) + 1;
            for (int i = 0; i < primes.Count; i++)
            {
                if (primes[i] > l)
                    break;
                if (n % primes[i] == 0)
                {
                    d.Add(primes[i]);
                }
            }
            divisors.Add(no, d.Distinct().OrderBy(t => t).ToArray());
            return divisors[no].ToList();
        }

        public static void Main(string[] args)
        {
            long[] ps = new long[10005];
            primes.Add(2);
            for (int i = 0; i < primes.Count; i++)
            {
                long np = primes[i];
                if (np > 10005)
                    break;
                for (int j = 1; j < 10005 / np; j++)
                {
                    ps[j * np] = 1;
                }
                np++;
                while (np < 10005 && ps[np] > 0)
                    np++;
                primes.Add(np);
            }
            int count = int.Parse(Console.ReadLine());
            List<string> output = new List<string>();
            for (int z = 0; z < count; z++)
            {
                var n = long.Parse(Console.ReadLine());
                var a = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
                bool can = true;
                Dictionary<long, List<long>> remainders = new Dictionary<long, List<long>>();
                for (int i = 0; i < n; i++)
                {
                    for (int j = i + 1; j < n; j++)
                    {
                        long delta = Math.Abs(a[i] - a[j]);
                        if (delta == 1)
                            continue;
                        if (delta == 0)
                        {
                            can = false;
                            break;
                        }
                        var ds = FindDivisors(delta);
                        for (int k = 0; k < ds.Count; k++)
                        {
                            if (!remainders.ContainsKey(ds[k]))
                                remainders.Add(ds[k], new List<long>());
                            long r = ds[k] - (a[i] % ds[k]); // Compute the remainder needed for a[j] to satisfy gcd condition
                            remainders[ds[k]].Add(r);
                        }
                    }
                    if (!can)
                        break;
                }
                if (can)
                {
                    var ks = remainders.Keys.ToList();
                    for (int i = 0; i < ks.Count; i++)
                    {
                        var k = ks[i];
                        if (remainders[k].Distinct().Count() >= k)
                        {
                            can = false;
                            break;
                        }
                    }
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
