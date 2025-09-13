using System;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            var input = Console.ReadLine().Split();
            long a = long.Parse(input[0]);
            long b = long.Parse(input[1]);

            int result;
            if (a == b)
                result = 0;
            else if (a % b == 0 || b % a == 0)
                result = 1;
            else
                result = 2;

            Console.Write(result);
            if (t > 0) Console.WriteLine();
        }
    }
}