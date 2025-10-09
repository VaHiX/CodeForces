using System;

namespace ASD
{
    class Program
    {
        static void Main()
        {
            int n = int.Parse(Console.ReadLine());

            for (int i = 0; i < n; i++)
            {
                int a = int.Parse(Console.ReadLine());

                string[] str = Console.ReadLine().Split();
                int[] str_1 = Array.ConvertAll(str, int.Parse);

                bool total = true;

                for (int j = 0; j < a  - 1; j++)
                {
                    int c = Math.Abs(str_1[j] - str_1[j + 1]);
                    if (c != 5 && c != 7)
                    {
                        total = false;
                        break;

                    }

                }

                if (total)
                {
                    Console.WriteLine("Yes");
                }


                else
                {
                    Console.WriteLine("No");
                }
            }
        }

    }
}
