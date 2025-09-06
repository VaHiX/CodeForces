using System;
using System.Collections.Generic;
using System.Linq;

public static class CompatibilityAnalyzer
{
    public static long[] CountPrimeCompatibility(int[] n)
    {
        long[] results = new long[n.Length];
        int maxN = n.Max();
        List<int> primes = SieveOfEratosthenes(maxN);

        for (int i = 0; i < n.Length; ++i)
        {
            results[i] = CountPairs(n[i], primes);
        }

        return results;
    }

    private static List<int> SieveOfEratosthenes(int limit)
    {
        bool[] isPrime = new bool[limit + 1];
        for (int i = 2; i <= limit; i++)
        {
            isPrime[i] = true;
        }

        for (int p = 2; p * p <= limit; p++)
        {
            if (isPrime[p])
            {
                for (int i = p * p; i <= limit; i += p)
                    isPrime[i] = false;
            }
        }

        List<int> primes = new List<int>();
        for (int p = 2; p <= limit; p++)
        {
            if (isPrime[p])
            {
                primes.Add(p);
            }
        }
        return primes;
    }

    private static long CountPairs(int n, List<int> primes)
    {
        long count = 0;
        foreach (int p in primes)
        {
            if (p > n)
                break;

            // Case 1: x = 1, y = p^k <= n for k >= 1
            long pk = p;
            while (pk <= n)
            {
                count++;
                if ((double)pk * p > n)
                    break;
                pk *= p;
            }

            // Case 2: x = a, y = a * p^k <= n where gcd(a, p) = 1 and k >= 1
            for (int a = 2; a <= n / p; ++a)
            {
                if (a % p != 0)
                {
                    long ap = (long)a * p;
                    if (ap <= n)
                    {
                        count++;
                        long apk = ap * p;
                        while (apk <= n)
                        {
                            count++;
                            if ((double)apk * p > n)
                                break;
                            apk *= p;
                        }
                    }
                }
            }
        }
        return count;
    }
}

class Solution
{
    static void Main()
    {
        // Read number of test cases
        int t = int.Parse(Console.ReadLine());
        
        // Read all n values
        int[] nValues = new int[t];
        for (int i = 0; i < t; i++)
        {
            nValues[i] = int.Parse(Console.ReadLine());
        }
        
        // Compute results
        long[] results = CompatibilityAnalyzer.CountPrimeCompatibility(nValues);
        
        // Print each result on its own line
        for (int i = 0; i < results.Length; i++)
        {
            Console.WriteLine(results[i]);
        }
    }
}
