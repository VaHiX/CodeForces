using System;
using System.Collections.Generic;
using System.Linq;

public class Solution
{
    private const int MOD = 998244353; 

    private static int n;

    private static List<long> dataValues;
    private static List<long> prefixSums;
    private static List<long> doublePrefixSums;
    private static List<long> blockStartIndices;
    private static List<long> segmentSums;
    private static List<long> cumulativeBlockSums;

    private static List<long> CalculatePrefixSums(List<long> inputList)
    {
        int k = inputList.Count;
        List<long> result = new List<long>(k + 1);
        for (int i = 0; i <= k; i++)
        {
            result.Add(0); 
        }

        for (int i = 0; i < k; i++)
        {
            result[i + 1] = result[i] + inputList[i];
        }
        return result;
    }

    private static long GetPartialSum(int l, int r1, int r2)
    {
        if (r2 <= r1) return 0L;
        long count = r2 - r1;
        long remainder = prefixSums[l] * count;
        long addition = doublePrefixSums[r2 + 1] - doublePrefixSums[r1 + 1];
        return addition - remainder;
    }

    private static Tuple<int, int> ConvertIndexToBlockAndOffset(long i)
    {
        int blockIndex = blockStartIndices.BinarySearch(i);
        if (blockIndex < 0)
        {
            blockIndex = ~blockIndex - 1; 
        }
        
        Tuple<int, int> result = Tuple.Create(blockIndex, (int)(i - blockStartIndices[blockIndex] + blockIndex));
        return result;
    }

    private static long PerformQuery(long l, long r)
    {
        Tuple<int, int> leftInfo = ConvertIndexToBlockAndOffset(l);
        Tuple<int, int> rightInfo = ConvertIndexToBlockAndOffset(r);
        long result = cumulativeBlockSums[rightInfo.Item1 + 1] - cumulativeBlockSums[leftInfo.Item1];
        
        if (leftInfo.Item2 != leftInfo.Item1) result -= GetPartialSum(leftInfo.Item1, leftInfo.Item1, leftInfo.Item2);
        if (rightInfo.Item2 != n - 1) result -= GetPartialSum(rightInfo.Item1, rightInfo.Item2 + 1, n);
        
        return result;
    }

    public static void Main(string[] args)
    {
        n = int.Parse(Console.ReadLine());
        dataValues = Console.ReadLine().Split().Select(long.Parse).ToList();

        prefixSums = CalculatePrefixSums(dataValues);
        doublePrefixSums = CalculatePrefixSums(prefixSums);

        blockStartIndices = new List<long> { 0 };
        for (int i = n; i >= 1; i--)
        {
            blockStartIndices.Add(blockStartIndices.Last() + i);
        }

        segmentSums = new List<long>(n);
        for (int i = 0; i < n; i++)
        {
            segmentSums.Add(GetPartialSum(i, i, n));
        }
        cumulativeBlockSums = CalculatePrefixSums(segmentSums);

        int q = int.Parse(Console.ReadLine());
        for (int i = 0; i < q; i++)
        {
            long[] lr = Console.ReadLine().Split().Select(long.Parse).ToArray();
            long l = lr[0];
            long r = lr[1];
            Console.WriteLine(PerformQuery(l - 1, r - 1));
        }
    }
}