using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int testCases = int.Parse(Console.ReadLine());

        while (testCases-- > 0)
        {
            int arraySize = int.Parse(Console.ReadLine());
            int[] numbers = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);

            int referenceValue = Math.Abs(numbers[0]);
            int countLessThanReference = 0;

            for (int index = 1; index < arraySize; index++)
            {
                if (Math.Abs(numbers[index]) < referenceValue)
                    countLessThanReference++;
            }

            if (countLessThanReference <= arraySize / 2)
                Console.WriteLine("YES");
            else
                Console.WriteLine("NO");
        }
    }
}