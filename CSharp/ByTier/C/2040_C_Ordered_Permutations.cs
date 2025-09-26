using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int testCases = int.Parse(Console.ReadLine());
        while (testCases-- > 0)
        {
            string[] inputs = Console.ReadLine().Split();
            int n = int.Parse(inputs[0]);
            long k = long.Parse(inputs[1]);
            
            List<int> firstGroup = new List<int>();
            List<int> secondGroup = new List<int>();
            
            if (n <= 60 && (1L << (n - 1)) < k)
            {
                Console.WriteLine(-1);
                continue;
            }
            
            k--; // Decrease k by 1 to work with 0-based index
            List<int> binaryDigits = new List<int>();
            
            // Convert k to binary representation
            while (k > 0)
            {
                binaryDigits.Add((int)(k % 2));
                k /= 2;
            }
            
            // Ensure the binary representation is of length (n-1)
            while (binaryDigits.Count < n - 1)
                binaryDigits.Add(0);
            
            // Distribute elements into firstGroup and secondGroup based on binary digits
            for (int i = n - 2, j = 1; i >= 0; i--, j++)
            {
                if (binaryDigits[i] == 0)
                    firstGroup.Add(j);
                else
                    secondGroup.Add(j);
            }

            secondGroup.Reverse();
            
            // Output the result
            foreach (int num in firstGroup)
                Console.Write(num + " ");
            Console.Write(n + " ");
            foreach (int num in secondGroup)
                Console.Write(num + " ");
            Console.WriteLine();
        }
    }
}
