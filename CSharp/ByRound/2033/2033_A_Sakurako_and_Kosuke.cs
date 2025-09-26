using System;

namespace ASD
{
    class Program
    {
        static void Main()
        {
            int b = int.Parse(Console.ReadLine());
            for (int i = 0; i < b; i++)
            {
                int n = int.Parse(Console.ReadLine());
                int x = 0;
                int v = 1;
                string player = "Kosuke";
                while (true)
                {
                    int r = 2 * v - 1;
                    if (v % 2 == 1)
                    {
                        x -= r;
                        player = "Sakurako";
                    }
                    else
                    {
                        x += r;
                        player = "Kosuke";
                    }
                    if (Math.Abs(x) > n)
                    {
                        Console.WriteLine(player);
                        break;
                    }
                    v++;
                }
            }
        }
    }
}