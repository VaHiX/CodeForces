using System;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        for (int i = 0; i < t; i++)
        {
        int result=10;
        int n = int.Parse(Console.ReadLine());
        while (n!=0)
        {
            if (n%10<result)
            {
                result = n%10;
            }
            n /= 10;
        }
        Console.WriteLine(result);
        }}
}