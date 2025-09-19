using System;

class Program
{
    static void Main(string[] args)
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;
        int t = int.Parse(Console.ReadLine());
        for (int i = 0; i < t; i++)
        {
            string[] inputs = Console.ReadLine().Split();
            int l = int.Parse(inputs[0]);
            int r = int.Parse(inputs[1]);
            int k = int.Parse(inputs[2]);
            Console.WriteLine(Math.Max(0, r / k - l + 1));
        }
    }
}
