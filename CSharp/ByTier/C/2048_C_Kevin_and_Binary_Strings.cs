using System;

class Program
{
    static void Main()
    {
        int tests = int.Parse(Console.ReadLine());
        while (tests-- > 0)
        {
            Solve();
            Console.WriteLine();
        }
    }

    static void Solve()
    {
        string input = Console.ReadLine();
        int zeroCh = input.IndexOf('0');
        int n = input.Length;

        if (zeroCh == -1)
            zeroCh = n - 1;

        int k = zeroCh - 1;
        int j = zeroCh;

        while (j < n && k >= 0)
        {
            if (input[j] == '1') break;
            j++;
            k--;
        }

        k++;
        Console.WriteLine($"1 {n} {k + 1} {k + n - zeroCh}");
    }
}
