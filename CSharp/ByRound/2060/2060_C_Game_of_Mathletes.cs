using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            var nk = Console.ReadLine().Split().Select(int.Parse).ToArray();
            int n = nk[0];
            int k = nk[1];

            var numbers = Console.ReadLine().Split().Select(int.Parse).ToList();
            var freq = new Dictionary<int, int>();

            foreach (var num in numbers)
            {
                if (freq.ContainsKey(num))
                    freq[num]++;
                else
                    freq[num] = 1;
            }

            int score = 0;
            var used = new HashSet<int>();

            foreach (var num in numbers)
            {
                if (used.Contains(num))
                    continue;

                int complement = k - num;
                if (freq.ContainsKey(complement))
                {
                    if (complement == num)
                    {
                        score += freq[num] / 2;
                        used.Add(num);
                    }
                    else
                    {
                        int min = Math.Min(freq[num], freq[complement]);
                        score += min;
                        used.Add(num);
                        used.Add(complement);
                    }
                }
            }

            Console.WriteLine(score);
        }
    }
}