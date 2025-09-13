using System;
using System.Collections.Generic;
using System.Linq;

class FenwickMax
{
    private int size;
    private int[] tree;

    public void Init(int n)
    {
        size = n;
        tree = new int[n + 1];
    }

    public void Update(int index, int value)
    {
        for (; index <= size; index += index & -index)
        {
            tree[index] = Math.Max(tree[index], value);
        }
    }

    public int Query(int index)
    {
        int result = 0;
        for (; index > 0; index -= index & -index)
        {
            result = Math.Max(result, tree[index]);
        }
        return result;
    }
}

class Program
{
    static void Main()
    {
        string? line = Console.ReadLine();
        if (line == null) return;
        int t = int.Parse(line);

        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine()!);

            int[] a = Console.ReadLine()!
                .Split()
                .Select(int.Parse)
                .Prepend(0) // 1-based index
                .ToArray();

            int[] b = Console.ReadLine()!
                .Split()
                .Select(int.Parse)
                .Prepend(0)
                .ToArray();

            int maxVal = 2 * n;
            int Reverse(int v) => maxVal - v + 1;

            var bit = new FenwickMax();
            bit.Init(maxVal + 2);

            long sum1 = 0, sum2 = 0;

            for (int i = 1; i <= n; i++)
            {
                int prevGEa = bit.Query(Reverse(a[i]));
                bit.Update(Reverse(a[i]), i);

                int LGEb = bit.Query(Reverse(b[i]));
                long weight = n - i + 1;

                sum1 += weight * LGEb;

                if (b[i] < a[i])
                {
                    sum2 += weight * (i - prevGEa);
                }
            }

            Console.WriteLine(sum1 - sum2);
        }
    }
}