using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var L = int.Parse(line[0]);
            var r = int.Parse(line[1]);
            getAns(L, r);
        }
    }
    static void getAns(int L, int r)
    {
        var bit = Convert.ToString(r, 2);
        var n = bit.Length;
        var av = 0;
        for (int i = 0; i < n; i++)
        {
            if (bit[i] == '1')
            {
                av += 1 << (n - 1 - i);
                if (av >= L + 2) break;
            }
        }
        Console.WriteLine("{0} {1} {2}", av, av - 1, L);
    }
}
