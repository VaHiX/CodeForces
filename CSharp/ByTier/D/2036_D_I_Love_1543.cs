using static System.Math;
using System.Collections.Generic;
using System;

public class hello
{
    public static int[] dx, dy;
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var h = int.Parse(line[0]);
            var w = int.Parse(line[1]);
            var map = new int[h, w];
            for (int i = 0; i < h; i++)
            {
                var s = Console.ReadLine().Trim();
                for (int j = 0; j < w; j++) map[i, j] = s[j] - '0';
            }
            getAns(h, w, map);
        }
    }
    static int check(int h, int w, int[,] map, bool[,] visited, int x, int y)
    {
        var map2 = new List<int>();
        var d = 0;
        while (d < 4)
        {
            var nx = x + dx[d];
            var ny = y + dy[d];
            if (nx >= 0 && nx < h && ny >= 0 && ny < w && !visited[nx, ny])
            {
                map2.Add(map[nx, ny]);
                x = nx;
                y = ny;
                visited[nx, ny] = true;
            }
            else d++;
        }
        var n = map2.Count;
        var c = 0;
        for (int i = 0; i < n; i++)
        {
            if (map2[i] == 1)
            {
                if (map2[(i + 1) % n] == 5 && map2[(i + 2) % n] == 4 && map2[(i + 3) % n] == 3) c++;
            }
        }
        return c;
    }
    static void getAns(int h, int w, int[,] map)
    {
        dx = new int[] { 0, 1, 0, -1 };
        dy = new int[] { 1, 0, -1, 0 };
        var visited = new bool[h, w];
        var imax = Min(h, w);
        var ans = 0;
        for (int i = 0; i < imax / 2; i++)
        {
            ans += check(h, w, map, visited, i, i);
        }
        Console.WriteLine(ans);
    }
}
