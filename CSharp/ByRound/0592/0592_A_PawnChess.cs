using static System.Math;
using System;

public class hello
{
    static void Main()
    {
        var map = new int[8, 8];
        for (int i = 0; i < 8; i++)
        {
            var s = Console.ReadLine().Trim();
            for (int j = 0; j < 8; j++)
            {
                if (s[j] == 'W') map[i, j] = 1;
                else if (s[j] == 'B') map[i, j] = 2;
            }
        }
        getAns(map);
    }
    static void getAns(int[,] map)
    {
        var wstep = 10;
        var bstep = 10;
        for (int i = 0; i < 8; i++)
        {
            var twp = -1;
            for (int j = 0; j < 8; j++)
            {
                if (map[j, i] == 1) { twp = j; break; }
                else if (map[j, i] == 2) break;
            }
            if (twp != -1) wstep = Min(wstep, twp);
            var tbp = -1;
            for (int j = 7; j >= 0; j--)
            {
                if (map[j, i] == 2) { tbp = j; break; }
                else if (map[j, i] == 1) break;
            }
            if (tbp != -1) bstep = Min(bstep, 7 - tbp);
        }
        Console.WriteLine(wstep <= bstep ? "A" : "B");
    }
}
