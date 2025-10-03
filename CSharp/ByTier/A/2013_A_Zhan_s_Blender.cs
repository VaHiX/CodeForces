using System;
 
class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine()); // Read number of test cases
        for (int i = 0; i < t; i++)
        {
            long n = long.Parse(Console.ReadLine()); // Read the number of fruits
            string[] xy = Console.ReadLine().Split();
            long x = long.Parse(xy[0]); // Blender capacity
            long y = long.Parse(xy[1]); // Adding capacity
 
            if (n == 0)
            {
                Console.WriteLine(0);
                continue;
            }
 
            if (n <= y)
            {
                // Case 1: If the number of fruits is less than or equal to y (can be added in one go)
                long result = (n + x - 1) / x; // Ceiling of n / x (how many seconds to blend all)
                Console.WriteLine(result);
            }
            else
            {
                // Case 2: When the number of fruits exceeds the adding capacity (y)
                long secondsToAddFruits = (n + y - 1) / y; // How many seconds to add all fruits
                long secondsToBlendFruits = (n + x - 1) / x; // How many seconds to blend all fruits
                long result = Math.Max(secondsToAddFruits, secondsToBlendFruits); // The maximum of both
                Console.WriteLine(result);
            }
        }
    }
}