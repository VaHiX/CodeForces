using System;
public class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            string[] s = Console.ReadLine().Split();
            int x = int.Parse(s[0]);
            int k = int.Parse(s[1]);
            if (x == 1)
                Console.WriteLine((k == 2) ? "YES" : "NO");
            else
                Console.WriteLine((k == 1 && IsPrime(x)) ? "YES" : "NO");

        }
    }

    static bool IsPrime(int x)
    {
        if (x == 1)
            return false;
        for (int i = 2; i * i <= x; i++)
            if (x % i == 0)
                return false;
        return true;
    }
}