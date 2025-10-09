using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace Codeforces
{
    class Program
    {
        //static void Main(string[] args)
        //{
        //    //string input2 = Console.ReadLine();
        //    //var inputs2 = input2.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries).Select(int.Parse);

        //    int t = int.Parse(Console.ReadLine());

        //    var answer = new List<long>();

        //    var visited = new HashSet<int>();
        //    var list = new List<int>();

        //    //int[] count = new int[26];

        //    bool result;
        //    for (int i = 0; i < t; i++)
        //    {
        //        //int n = int.Parse(Console.ReadLine());

        //        string s = Console.ReadLine();
        //        var nums = s.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries).Select(long.Parse).ToArray();

        //        long k = nums[0];
        //        long a = nums[1];
        //        long b = nums[2];

        //        long count1 = Math.Abs(a) / k;
        //        long count2 = Math.Abs(b) / k;

        //        if (a == 0)
        //        {
        //            answer.Add(count2 + 1);
        //        }
        //        else if (b == 0)
        //        {
        //            answer.Add(count1 + 1);
        //        }
        //        else if (a < 0 && b < 0)
        //        {
        //            answer.Add(count1 - count2);
        //        }
        //        else if (a > 0 && b > 0)
        //        {
        //            answer.Add(count2 - count1);
        //        }
        //        else
        //        {
        //            answer.Add(count1 + count2 + 1);
        //        }

        //        //answer.Add(count);
        //    }

        //    foreach (var ans in answer)
        //    {
        //        Console.WriteLine(ans);
        //    }
        //}

        private static int GetDivision(int rating)
        {
            if (rating <= 1399)
            {
                return 4;
            }

            if (rating >= 1400 && rating <= 1599)
            {
                return 3;
            }

            if (rating >= 1600 && rating <= 1899)
            {
                return 2;
            }

            return 1;
        }

        private static int GetSum(int num)
        {
            int sum = 0;

            while (num > 0)
            {
                sum += num % 10;
                num /= 10;
            }

            return sum;
        }

        private static int GetCount(int num)
        {
            int count = 0;

            while (num > 0)
            {
                count++;
                num /= 10;
            }

            return count;
        }

        static void Main(string[] args)
        {
            string s = Console.ReadLine();
            var nums = s.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries).Select(long.Parse).ToArray();

            long k = nums[0];
            long a = nums[1];
            long b = nums[2];

            long add1 = Math.Max(0, 1 - Math.Abs(a) % k);
            long add2 = Math.Max(0, 1 - Math.Abs(b) % k);

            long count1 = Math.Abs(a) / k;
            long count2 = Math.Abs(b) / k;

            if (a == 0)
            {
                Console.WriteLine(count2 + 1);
            }
            else if (b == 0)
            {
                Console.WriteLine(count1 + 1);
            }
            else if (a < 0 && b < 0)
            {
                Console.WriteLine(count1 - count2 + add2);
            }
            else if (a > 0 && b > 0)
            {
                Console.WriteLine(count2 - count1 + add1);
            }
            else
            {
                Console.WriteLine(count1 + count2 + 1);
            }
        }

        private static bool IsPrime(int num)
        {
            if (num == 1)
            {
                return true;
            }

            for (int i = 2; i * i <= num; i++)
            {
                if (num % i == 0)
                {
                    return false;
                }
            }

            return true;
        }
    }
}
