using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine()); // Number of test cases

        for (int testCase = 0; testCase < t; testCase++)
        {
            var inputs = Console.ReadLine().Split(' ');
            int n = int.Parse(inputs[0]);
            int k = int.Parse(inputs[1]);

            var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

            bool found = false;
            int chosenIndex = -1;

            // Iterate through each element as a candidate for the first player's choice
            for (int i = 0; i < n; i++)
            {
                bool canWin = true;

                // Check against all other elements
                for (int j = 0; j < n; j++)
                {
                    if (i != j && Math.Abs(a[i] - a[j]) % k == 0)
                    {
                        canWin = false;
                        break;
                    }
                }

                if (canWin)
                {
                    found = true;
                    chosenIndex = i + 1; // Convert to 1-based index
                    break;
                }
            }

            if (found)
            {
                Console.WriteLine("YES");
                Console.WriteLine(chosenIndex);
            }
            else
            {
                Console.WriteLine("NO");
            }
        }
    }
}
