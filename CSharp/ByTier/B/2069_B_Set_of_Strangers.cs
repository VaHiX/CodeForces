using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            string[] nm = Console.ReadLine().Split();
            int n = int.Parse(nm[0]);
            int m = int.Parse(nm[1]);

            int[,] grid = new int[n, m];
            for (int i = 0; i < n; i++)
            {
                string[] row = Console.ReadLine().Split();
                for (int j = 0; j < m; j++)
                {
                    grid[i, j] = int.Parse(row[j]);
                }
            }

            Dictionary<int, int> colorMap = new Dictionary<int, int>();
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    int color = grid[i, j];
                    if (!colorMap.ContainsKey(color))
                        colorMap[color] = 0;

                    if (j + 1 < m && grid[i, j + 1] == color)
                        colorMap[color] = 1;
                    if (i + 1 < n && grid[i + 1, j] == color)
                        colorMap[color] = 1;
                }
            }

            int isolated = 0, adjacent = 0;
            foreach (var value in colorMap.Values)
            {
                if (value == 0) isolated++;
                else adjacent++;
            }

            int result = isolated + 2 * adjacent;
            Console.WriteLine(adjacent > 0 ? result - 2 : result - 1);
        }
    }
}
