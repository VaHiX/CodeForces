// Problem: CF 1985 G - D-Function
// https://codeforces.com/contest/1985/problem/G

using System;
using System.IO;

public class Program
{
    const long MOD = 1000000007;

    // Fast exponentiation function to compute (x^y) % mod
    static long Pow(long x, long y, long mod)
    {
        long res = 1;
        x = x % mod;
        if (x == 0)
            return 0;
        while (y > 0)
        {
            if ((y & 1) == 1) // If y is odd
                res = (res * x) % mod;
            y >>= 1; // Divide y by 2
            x = (x * x) % mod;
        }
        return res;
    }

    public static void Main(string[] args)
    {
        using (var r = new StreamReader(Console.OpenStandardInput()))
        using (var w = new StreamWriter(Console.OpenStandardOutput()))
        {
            int t = int.Parse(r.ReadLine());
            while (t-- > 0)
            {
                var s = r.ReadLine().Split();
                long a = long.Parse(s[0]); // l
                long b = long.Parse(s[1]); // r
                long c = long.Parse(s[2]); // k

                // If k >= 10, there are no valid numbers n in the range [10^l, 10^r)
                // because D(k*n) can't equal k*D(n) due to digit sum properties
                if (c >= 10)
                {
                    w.WriteLine(0);
                    continue;
                }

                // Compute d = floor(10 / k) + (10 % k != 0 ? 1 : 0)
                // This represents how many digits in base 10 can be used for valid n
                long d = 10 / c;
                d += 10 % c != 0 ? 1 : 0;

                // pow(d, b) and pow(d, a) give us the number of valid numbers for ranges [10^a, 10^b)
                long e = Pow(d, b, MOD); // Number of valid n in [10^0, 10^b)
                long f = Pow(d, a, MOD); // Number of valid n in [10^0, 10^a)

                // Subtract to get count in [10^a, 10^b)
                long g = (e - f + MOD) % MOD;
                w.WriteLine(g);
            }
        }
    }
}

// ### Complexity Analysis

// - **Time Complexity:**
//   - The `Pow` function runs in $ O(\log y) $ time.
//   - For each test case, we perform two exponentiations, which results in $ O(\log r + \log l) $ per test case.
//   - Since there are up to $ t = 10^4 $ test cases, total time complexity is $ O(t \cdot \log(\max(r, l))) $.

// - **Space Complexity:**
//   - The space usage is constant, $ O(1) $, as we use only a fixed number of variables regardless of input size.

// https://github.com/VaHiX/CodeForces/
