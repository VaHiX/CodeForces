using System;
using System.Numerics;

class Program
{
    private static long N_global, M_global;
    private static int K_global;
    private const long MOD = 1_000_000_007;
    private const long MOD_PHI = 1_000_000_006;

    static long Power(long baseValue, long exp)
    {
        long result = 1;
        baseValue %= MOD;
        while (exp > 0)
        {
            if (exp % 2 == 1)
                result = (result * baseValue) % MOD;
            
            baseValue = (baseValue * baseValue) % MOD;
            exp /= 2;
        }
        return result;
    }

    static long ComputeExponent(long nVal, long mVal, int kVal, bool minusOne)
    {
        long nMod = nVal % MOD_PHI;
        long mMod = mVal % MOD_PHI;
        long nmMod = (nMod * mMod) % MOD_PHI;
        long kMod = kVal % MOD_PHI;

        if (kMod < 0)
            kMod += MOD_PHI;

        long expBase = (nmMod - kMod + MOD_PHI) % MOD_PHI;

        return minusOne 
            ? (expBase - 1 + MOD_PHI) % MOD_PHI
            : expBase;
    }

    static bool IsBorderNonCorner(long r, long c)
    {
        if (r < 1 || r > N_global || c < 1 || c > M_global)
            return false;

        bool onBorder = (r == 1 || r == N_global || c == 1 || c == M_global);
        bool isCorner = (r == 1 && c == 1) || 
                       (r == 1 && c == M_global) || 
                       (r == N_global && c == 1) || 
                       (r == N_global && c == M_global);

        return onBorder && !isCorner;
    }

    static void Main()
    {
        int T = int.Parse(Console.ReadLine()!);
        while (T-- > 0)
        {
            long[] dimensions = Array.ConvertAll(Console.ReadLine()!.Split(), long.Parse);
            N_global = dimensions[0];
            M_global = dimensions[1];
            K_global = (int)dimensions[2];

            long fixedOddCount = 0;
            int fixedOddSumParity = 0;

            for (int i = 0; i < K_global; i++)
            {
                long[] inputs = Array.ConvertAll(Console.ReadLine()!.Split(), long.Parse);
                long r = inputs[0];
                long c = inputs[1];
                int color = (int)inputs[2];

                if (IsBorderNonCorner(r, c))
                {
                    fixedOddCount++;
                    fixedOddSumParity = (fixedOddSumParity + color) % 2;
                }
            }

            long totalOddCount = (N_global >= 2 && M_global >= 2) 
                ? 2L * N_global + 2L * M_global - 8L 
                : 0;

            long variableOddCount = totalOddCount - fixedOddCount;
            long ans;

            if (variableOddCount > 0)
            {
                long exp = ComputeExponent(N_global, M_global, K_global, true);
                ans = Power(2, exp);
            }
            else
            {
                ans = fixedOddSumParity == 0
                    ? Power(2, ComputeExponent(N_global, M_global, K_global, false))
                    : 0;
            }

            Console.WriteLine(ans);
        }
    }
}