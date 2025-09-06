using System;

class Program
{
    static void Main()
    {
        // Read number of test cases
        if (!int.TryParse(Console.ReadLine(), out int t) || t < 1 || t > 10000)
        {
            Console.WriteLine("Invalid number of test cases.");
            return;
        }

        for (int i = 0; i < t; i++)
        {
            string s = Console.ReadLine();

            // Validate that input is exactly 4 digits
            if (s == null || s.Length != 4 || !int.TryParse(s, out int S) || S < 0 || S > 9999)
            {
                Console.WriteLine("-1");
                continue;
            }

            int root = (int)Math.Sqrt(S);
            if (root * root == S)
            {
                // Output any pair (a, b) such that a + b = root
                // Simplest: (0, root)
                Console.WriteLine($"0 {root}");
            }
            else
            {
                Console.WriteLine("-1");
            }
        }
    }
}
