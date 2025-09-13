using System;
using System.Linq;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine()!);

        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine()!);
            
            // Using LINQ for more concise min/max calculation
            int[] numbers = Console.ReadLine()!
                .Split(' ', StringSplitOptions.RemoveEmptyEntries)
                .Select(int.Parse)
                .ToArray();
            
            // Using pattern matching for null checks (though not needed here as we're using !)
            // Using tuple deconstruction for min and max
            var (minVal, maxVal) = (numbers.Min(), numbers.Max());
            
            Console.WriteLine(maxVal - minVal);
        }
    }
}