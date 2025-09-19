using System;
using System.Linq;
using System.Threading;
using System.Collections.Generic;
using System.Diagnostics;

public class Program
{
    int N;
    int[] A;
    public void Solve()
    {
#if DEBUG
        N = DebugA.Length;
#else
        N = int.Parse(Console.ReadLine());
#endif
        if (N == 1)
        {
            Console.WriteLine($"! 1");
            return;
        }


        // N-順列A
        //  
        // a_i < min(a_{i-1}, a_{i+1})
        // i は local minimum 
        // 
        // local minimumを探す
        // 
        // ? i
        // A_iを返す
        //
        // 
        int[] fib = new int[27];
        fib[0] = 0;
        fib[1] = 1;
        for (int i = 2; i <= 26; i++)
        {
            fib[i] = fib[i - 1] + fib[i - 2];
        }

        // Console.WriteLine(string.Join("\n", fib));
        A = new int[fib[26]];
        for (int i = 0; i < fib[26]; i++)
        {
            if (1 <= i && i <= N) continue;
            A[i] = i;
        }

        A[0] = int.MaxValue;
        int l = 0;
        int r = fib[26];
        for (int d = 26; d > 3; d--)
        {
            int m1 = l + fib[d - 2];
            int m2 = l + fib[d - 1];

            int q1 = Q(m1);
            int q2 = Q(m2);

            if (q1 < q2)
            {
                r = m2;
            }
            else
            {
                l = m1;
            }
        }

        for (int i = l; i < r; i++) Q(i);
        for (int i = l; i < r; i++)
        {
            if (i <= 0 || i > N) continue;
            if (A[i] < Math.Min(A[i - 1], A[i + 1]))
            {
                Console.WriteLine($"! {i}");
                return;
            }
        }


    }

#if DEBUG
    // int[] DebugA = { 3, 2, 1, 4, 5 };
    // int[] DebugA = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int[] DebugA = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
#endif

    int Q(int i)
    {
        if (A[i] != 0) return A[i];
#if DEBUG
        A[i] = DebugA[i - 1];
        Console.WriteLine($"DEBUG ? {i}\n{DebugA[i - 1]}");
        return DebugA[i - 1];
#else
       
        Console.WriteLine($"? {i}");
        int ret =  int.Parse(Console.ReadLine());
        A[i] = ret;
        return ret;
#endif
    }



    public static void Main(string[] args) => new Program().Solve();
    // public static void Main(string[] args) => new Thread(new Program().Solve, 1 << 27).Start();
}
