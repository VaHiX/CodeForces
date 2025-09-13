using System;
using System.Linq;

public static class Solution
{
    public static long MinCustomers(int n, int x, long[] a)
    {
        long totalCars = a.Sum();
        long minCustomersFromTotal = (long)Math.Ceiling((double)totalCars / x);
        long minCustomersFromMaxModel = a.Max();
        return Math.Max(minCustomersFromTotal, minCustomersFromMaxModel);
    }
}

public class Program
{
    static void Main()
    {
        // Read number of test cases
        int t = int.Parse(Console.ReadLine());
        
        while (t-- > 0)
        {
            // Read n and x
            string[] header = Console.ReadLine()
                                     .Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            int n = int.Parse(header[0]);
            int x = int.Parse(header[1]);
            
            // Read the counts of each model
            string[] parts = Console.ReadLine()
                                    .Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            long[] a = Array.ConvertAll(parts, long.Parse);
            
            // Compute and print the result
            long result = Solution.MinCustomers(n, x, a);
            Console.WriteLine(result);
        }
    }
}
