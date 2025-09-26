using System;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());

        for (int i = 0; i < t; i++)
        {
            string[] input = Console.ReadLine().Split();
            int a = int.Parse(input[0]);
            int b = int.Parse(input[1]);

            int result = (a == 1 && b == 1) ? 1 : b - a;
            Console.WriteLine(result);
        }
    }
}
