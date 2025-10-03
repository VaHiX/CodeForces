using System;
using System.Linq;

namespace CF_596_A
{
    class Program
    {
        static void Main(string[] args)
        {
            var n = int.Parse(Console.ReadLine());
            int i,max1=-1000,max2=-1000,min1=1000,min2=1000;
            for (i = 0; i < n; i++)
            {
                var s = Console.ReadLine().Split().Select(int.Parse).ToArray();
                if (s[0] > max1) max1 = s[0];
                if (s[0] < min1) min1 = s[0];
                if (s[1] > max2) max2 = s[1];
                if (s[1] < min2) min2 = s[1];
            }
            //Console.WriteLine($"{max1} {min1} {max2} {min2}");
            if ((max1 - min1) * (max2 - min2) > 0) Console.WriteLine((max1 - min1) * (max2 - min2));
            else Console.WriteLine("-1");
        }
    }
}
