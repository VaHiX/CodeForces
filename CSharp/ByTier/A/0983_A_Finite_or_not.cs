using System;

class Program 
{
    static long gcd(long a, long b) 
    {
        if (b == 0) 
        {
            return a;
        }
        return gcd(b, a % b);
    }

    static void Main(string[] args) 
    {
        int T = int.Parse(Console.ReadLine());

        while (T-- > 0) 
        {
            long p, q, b;
            string[] input = Console.ReadLine().Split();

            p = long.Parse(input[0]);
            q = long.Parse(input[1]);
            b = long.Parse(input[2]);

            q /= gcd(p, q);

            while (b != 1) 
            {
                b = gcd(q,b);
                q /= b;
            }

            if (q == 1) 
            {
                Console.WriteLine("Finite");
            }
            else 
            {
                Console.WriteLine("Infinite");
            }
        }
    }
}