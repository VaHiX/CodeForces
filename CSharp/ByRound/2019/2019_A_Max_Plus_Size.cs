using System;
using System.Collections.Generic;
using System.Linq;
public class Solution
{
    public static void Main(string[] args)
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            int size = int.Parse(Console.ReadLine());
            List<int> array = new List<int>();

            string[] inputs = Console.ReadLine().Split();
            for (int i = 0; i < size; i++)
            {
                array.Add(int.Parse(inputs[i]));
            }

            int MaxScore = new Solution().MaxPlusSize(size, array);
            Console.WriteLine(MaxScore);
        }
    }
    public int MaxPlusSize(int size, List<int> array)
    {        
        int maxElement1 = array.Max();
        int maxElement2 = array.Max();
        int OddScore = 0; int EvenScore = 0;        

        for (int j = 0; j < size; j++)
        {
            // Odd position
            if (j % 2 == 0)
            {
                OddScore += 1;
                if (maxElement1 == array[j])
                {
                    OddScore += maxElement1;
                    maxElement1 = 0;
                }
            }
            // Even position
            else
            {
                EvenScore += 1;
                if (maxElement2 == array[j])
                {
                    EvenScore += maxElement2;
                    maxElement2 = 0;
                }
            }

        }
        return (OddScore >= EvenScore) ? OddScore : EvenScore;

    }
}