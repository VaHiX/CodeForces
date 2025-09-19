using System;
using System.Linq;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine()); // عدد حالات الاختبار

        while (t-- > 0)
        {
            string[] input = Console.ReadLine().Split();
            int n = int.Parse(input[0]); // حجم المصفوفة
            int l = int.Parse(input[1]); // بداية المقطع
            int r = int.Parse(input[2]); // نهاية المقطع

            long[] arr = Console.ReadLine().Split().Select(long.Parse).ToArray();

            l--; r--;

            long[] leftPart = arr.Take(r + 1).ToArray();
            Array.Sort(leftPart);

            long[] rightPart = arr.Skip(l).ToArray();
            Array.Sort(rightPart);

            long leftSum = leftPart.Take(r - l + 1).Sum();
            long rightSum = rightPart.Take(r - l + 1).Sum();

            Console.WriteLine(Math.Min(leftSum, rightSum));
        }
    }
}
