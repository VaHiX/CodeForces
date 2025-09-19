using System;

public class Solution
{
    static bool inside(int x, int n){
        return x>=0 && x<n;
    }
    public static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-->0){
            int n = int.Parse(Console.ReadLine());
            int[,] grid = new int[n, n];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    grid[i,j] = -1;
            //for (int i = 0; i < n; i++)
            //{
            //    string[] parts = Console.ReadLine().Split();
            //    for (int j = 0; j < n; j++)
            //        grid[i, j] = int.Parse(parts[j]);
            //}
            int x = 0,y=0,z=1,val=n*n-1;
            int[] dx = { -1,0,1,0 };
            int[] dy = { 0,1,0,-1 };
            while (val>=0){
                grid[x, y] = val--;
                if (!inside(x + dx[z], n) || !inside(y + dy[z], n) || grid[x + dx[z], y + dy[z]]>-1)
                    z = (z + 1) % 4;
                x += dx[z];
                y += dy[z];
            }
            //int s = 0;
            //for (int i = 0; i < n; i++)
            //    for (int j = 0; j < n; j++)
            //        for (int k = i; k < n; k++)
            //            for (int p = 0; p < n; p++)
            //            {
            //                int[] B = new int[n*n+1];
            //                for (int q = 0; q <= n * n; q++)
            //                    B[q] = 0;
            //                for (int q = i; q <= k; q++)
            //                    for (int r = j; r <= p; r++)
            //                        B[grid[q, r]] = 1;
            //                int mex = 0;
            //                while (B[mex]==1)
            //                    mex++;
            //                s += mex;
            //            }
            //Console.WriteLine(s);
            for (int i = 0; i < n; i++) { 
                for (int j = 0; j < n; j++)
                    Console.Write(grid[i, j] + " ");
                Console.WriteLine();
            }
        }
    }
}