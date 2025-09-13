using System;
using System.Collections.Generic;

class Program
{
    const int N = 100005;
    const int mod = 1000000007;

    static void Solve()
    {

        string[] input = Console.ReadLine().Split();
        long n = long.Parse(input[0]);
        long m = long.Parse(input[1]);
        long q = long.Parse(input[2]);

        List<long> v = new List<long>();
        string[] vInput = Console.ReadLine().Split();
        for (int i = 0; i < m; i++)
        {
            v.Add(long.Parse(vInput[i]));
        }


        long x = long.Parse(Console.ReadLine());


        v.Sort();


        int it = v.BinarySearch(x);
        if (it < 0)
        {
            it = ~it; 
        }


        if (it == 0)
        {

            Console.WriteLine(v[0] - 1);
        }
        else if (it >= m)
        {

            Console.WriteLine(n - v[(int)m - 1]);
        }
        else
        {

            Console.WriteLine((v[it] - v[it - 1]) / 2);
        }
    }

    static void Main(string[] args)
    {

        Console.SetIn(new System.IO.StreamReader(Console.OpenStandardInput()));
        Console.SetOut(new System.IO.StreamWriter(Console.OpenStandardOutput()) { AutoFlush = true });


        int T = int.Parse(Console.ReadLine());
        while (T-- > 0)
        {
            Solve();
        }
    }
}
