using System;

class FizzBuzzCount
{
    static int CountFizzBuzz(int n)
    {
        int cycles = n / 15;
        int count = 3 * cycles;

        int remainderStart = cycles * 15;
        for (int i = remainderStart; i <= n; i++)
        {
            if (i % 3 == i % 5)
            {
                count++;
            }
        }

        return count;
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine());
            Console.WriteLine(CountFizzBuzz(n));
        }
    }
}
