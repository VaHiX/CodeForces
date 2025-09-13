using System;
using static System.Console;
class Program
{
    static void Main()
    {
        int t = int.Parse(ReadLine());
        while (t-- > 0)
        {
            int n = int.Parse(ReadLine());
            int m = 0, p = 0;
            for (int i = 0; i < n; i++)
            {
                var asd = ReadLine().Split();
                int w = int.Parse(asd[0]);
                int h = int.Parse(asd[1]);
                m = Math.Max(m, w);
                p = Math.Max(p, h);
            }
            WriteLine(2 * (m + p));
        }
    }
}
