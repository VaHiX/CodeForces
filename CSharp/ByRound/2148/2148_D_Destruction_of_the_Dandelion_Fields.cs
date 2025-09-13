using System;
using System.Collections.Generic;
using System.Linq;

public class Solution {
    public static void Main() {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0) {
            int n = int.Parse(Console.ReadLine());
            var numbers = Console.ReadLine().Split().Select(long.Parse).ToArray();

            long sumEven = 0;
            var odds = new List<long>();

            foreach (var a in numbers) {
                if (a % 2 == 0)
                    sumEven += a;
                else
                    odds.Add(a);
            }

            if (odds.Count == 0) {
                Console.WriteLine(0);
                continue;
            }

            odds.Sort((x, y) => y.CompareTo(x)); // descending
            int take = (odds.Count + 1) / 2;

            long sumOdd = 0;
            for (int i = 0; i < take; i++) {
                sumOdd += odds[i];
            }

            Console.WriteLine(sumEven + sumOdd);
        }
    }
}
