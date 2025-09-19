using System;
using System.Collections.Generic;
using System.Linq;

public class Solution
{
    private const int MOD = 1_000_000_007;

    public static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        List<string> results = new List<string>();

        for (int _ = 0; _ < t; _++)
        {
            string[] line1 = Console.ReadLine().Split(' ');
            int n = int.Parse(line1[0]);
            int k = int.Parse(line1[1]);
            int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);


            Dictionary<int, int> freqDict = new Dictionary<int, int>();
            foreach (int num in a)
            {
                if (freqDict.ContainsKey(num))
                    freqDict[num]++;
                else
                    freqDict[num] = 1;
            }


            List<int> sortedUnique = freqDict.Keys.ToList();
            sortedUnique.Sort();
            int[] freqSorted = sortedUnique.Select(x => freqDict[x]).ToArray();
            int m = sortedUnique.Count;

            int left = 0;
            int currentSum = 0;
            int maxSum = 0;

            for (int right = 0; right < m; right++)
            {
                currentSum += freqSorted[right];


                while (left <= right && (sortedUnique[right] - sortedUnique[left] + 1 > right - left + 1 || right - left + 1 > k))
                {
                    currentSum -= freqSorted[left];
                    left++;
                }

                maxSum = Math.Max(maxSum, currentSum);
            }

            results.Add(maxSum.ToString());
        }

        Console.WriteLine(string.Join("\n", results));
    }
}
