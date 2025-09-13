using System;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine()!);

        while (t-- > 0)
        {
            string[] parts = Console.ReadLine()!.Split();
            long a = long.Parse(parts[0]);
            long b = long.Parse(parts[1]);

            // if b is odd
            if ((b & 1) == 1)
            {
                if ((a & 1) == 1)
                {
                    Console.WriteLine(a * b + 1);
                }
                else
                {
                    Console.WriteLine("-1");
                }
                continue;
            }

            // factor out powers of 2 from b
            long bb = b;
            int powerOfTwo = 0;
            while ((bb & 1) == 0)
            {
                bb >>= 1;
                powerOfTwo++;
            }

            if ((a & 1) == 1 && powerOfTwo == 1)
            {
                Console.WriteLine("-1");
                continue;
            }

            long kMin = ((a & 1) == 1) ? 2 : 1;
            long s1 = a * kMin + b / kMin;
            long s2 = a * (b / 2) + 2;

            Console.WriteLine(Math.Max(s1, s2));
        }
    }
}