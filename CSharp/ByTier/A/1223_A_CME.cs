using System;

public class Program
{
    public static void Main()
    {
        int q = int.Parse(Console.ReadLine());

        while (q-- != 0)
        {
            int n = int.Parse(Console.ReadLine());

            if (n == 2)
            {
                Console.WriteLine(2);
            }
            else
            {
                Console.WriteLine(n % 2);
            }

        }
    }
}
