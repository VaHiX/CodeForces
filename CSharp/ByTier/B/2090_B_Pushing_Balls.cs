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
            getAns(h, w);
        }
    }
    static void getAns(int h, int w)
    {
        var map = new int[h, w];
        for (int i = 0; i < h; i++)
        {
            var s = Console.ReadLine().Trim();
            for (int j = 0; j < w; j++)
                if (s[j] == '1') map[i, j] = 1;
        }
        var ok = new bool[h, w];
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
                if (map[i, j] == 1) ok[i, j] = true;
                else break;
        }
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
                if (map[j, i] == 1) ok[j, i] = true;
                else break;
        }
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
                if (map[i, j] == 1 && !ok[i, j]) { Console.WriteLine("NO"); return; }
        }
        Console.WriteLine("YES");
    }
}
