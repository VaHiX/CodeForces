using static System.Math;
using System.Linq;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var h = int.Parse(line[0]);
            var w = int.Parse(line[1]);
            var s = new string[h];
            for (int i = 0; i < h; i++) s[i] = Console.ReadLine().Trim();
            getAns(h, w, s);
        }
    }
    static void getAns(int h, int w, string[] s)
    {
        var c = 0;
        for (int i = 0; i < h; i++)
        {
            var t = s[i].Count(z => z == '1');
            if (t % 2 == 1) c++;
        }
        var d = 0;
        for (int i = 0; i < w; i++)
        {
            var t = 0;
            for (int j = 0; j < h; j++)
            {
                if (s[j][i] == '1') t++;
            }
            if (t % 2 == 1) d++;
        }
        Console.WriteLine(Max(c, d));
    }
}
