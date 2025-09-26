using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

public static class Solution
{
    // Returns the maximum count of non-overlapping zero-sum segments (“beautiful” segments)
    public static int MaxBeautifulSegments(int n, int[] a)
    {
        var seenSums = new SortedSet<long> { 0L };
        long prefixSum = 0L;
        int result = 0;

        for (int i = 0; i < n; i++)
        {
            prefixSum += a[i];
            if (seenSums.Contains(prefixSum))
            {
                result++;
                seenSums.Clear();
                prefixSum = 0L;
            }
            seenSums.Add(prefixSum);
            
        }

        return result;
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
            // Read n
            int n = int.Parse(Console.ReadLine());
            
            // Read the array elements
            string[] parts = Console.ReadLine()
                                    .Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            int[] a = Array.ConvertAll(parts, int.Parse);
            
            // Compute and print the result
            int result = Solution.MaxBeautifulSegments(n, a);
            Console.WriteLine(result);
        }
    }
}
