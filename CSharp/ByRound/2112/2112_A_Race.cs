using System;

public class HelloWorld
{
    public static void Main(string[] args)
    {
        

        int t = Convert.ToInt32(Console.ReadLine());
        int c,u,p,counter=0;
        int[] f = new int[3];

        for (int q = 0; q < t; q++)
        {
            string[] x = Console.ReadLine().Split();
            for (int i = 0; i < 3; i++)
            {
                f[i] = int.Parse(x[i]);
            }


            c = f[0];
            bool bobWins = false;
            for (int b = 1; b <= 100; b++)
            {
                if (b == f[0]) continue;

                int bobToX = Math.Abs(b - f[1]);
                int bobToY = Math.Abs(b - f[2]);

                int aliceToX = Math.Abs(f[0] - f[1]);
                int aliceToY = Math.Abs(f[0] - f[2]);

                if (bobToX < aliceToX && bobToY < aliceToY)
                {
                    bobWins = true;
                    break;
                }
            }
            Console.WriteLine(bobWins ? "YES" : "NO");

        }

    }
}


