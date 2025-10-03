using System;

public static class LexMaxStringTransformer
{
    // Returns the lexicographically maximum string obtainable from s.
    public static string LexMax(string s)
    {
        char[] chars = s.ToCharArray();
        int n = chars.Length;

        for (int i = 0; i < n; i++)
        {
            int best = chars[i] - '0';
            int pos = i;

            for (int j = i; j < Math.Min(i + 10, n); j++)
            {
                int value = chars[j] - '0' - (j - i);
                if (value > best)
                {
                    best = chars[j] - '0' - (j - i);
                    pos = j;
                }
            }

            while (pos > i)
            {
                // Swap adjacent characters to bring best to index i
                (chars[pos], chars[pos - 1]) = (chars[pos - 1], chars[pos]);
                pos--;
            }

            chars[i] = (char)(best + '0'); // Re-set in case of movement
        }

        return new string(chars);
    }
}


class Solution
{
    static void Main()
    {
        // Read number of test cases
        int t = int.Parse(Console.ReadLine());
        
        while (t-- > 0)
        {
            // Read the input string
            string s = Console.ReadLine().Trim();
            
            // Transform and print the result
            string ans = LexMaxStringTransformer.LexMax(s);
            Console.WriteLine(ans);
        }
    }
}
