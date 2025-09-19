using System;

class Program
{
    static void Main()
    {
        long t = long.Parse(Console.ReadLine());
        
        while (t-- > 0)
        {
            string[] input = Console.ReadLine().Split();
            long n = long.Parse(input[0]);
            long b = long.Parse(input[1]);
            long c = long.Parse(input[2]);

            if (c >= n)
            {
                Console.WriteLine(n);
                continue;
            }

            if (b == 0)
            {
                if (n - c > 2)
                    Console.WriteLine(-1);
                else
                    Console.WriteLine(n - 1);
                continue;
            }

            long last = (n - 1 - c) / b;
            Console.WriteLine(n - 1 - last);
        }
    }
}
