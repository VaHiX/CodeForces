using System;
using System.Linq;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine());
            string input = Console.ReadLine();
            
            // 1-based indexing
            input = " " + input;
            
            // Prepare the next_p array (next 'p' position from current)
            int[] nextP = Enumerable.Repeat(n + 1, n + 2).ToArray();
            for (int j = n; j >= 1; j--)
            {
                if (input[j] == 'p') nextP[j] = j;
                else nextP[j] = nextP[j + 1];
            }

            // Prepare the last_s array (last 's' position up to current)
            int[] lastS = new int[n + 1];
            for (int j = 1; j <= n; j++)
            {
                if (input[j] == 's') lastS[j] = j;
                else lastS[j] = lastS[j - 1];
            }

            // Array to store Uj values
            int[] Uj = new int[n];
            for (int j = 1; j <= n; j++)
            {
                int uP = int.MaxValue;
                if (nextP[j] <= n)
                {
                    uP = nextP[j];
                }

                int uS = int.MaxValue;
                if (lastS[j] >= 1)
                {
                    uS = n - lastS[j] + 1;
                }

                if (uP != int.MaxValue && uS != int.MaxValue)
                {
                    Uj[j - 1] = Math.Min(uP, uS);
                }
                else if (uP != int.MaxValue)
                {
                    Uj[j - 1] = uP;
                }
                else if (uS != int.MaxValue)
                {
                    Uj[j - 1] = uS;
                }
                else
                {
                    Uj[j - 1] = n;
                }
            }

            // Sort the Uj array
            Array.Sort(Uj);

            // Check if the condition is met for each Uj[i] >= i
            bool isValid = true;
            for (int i = 1; i <= n; i++)
            {
                if (Uj[i - 1] < i)
                {
                    isValid = false;
                    break;
                }
            }

            // Output the result
            Console.WriteLine(isValid ? "YES" : "NO");
        }
    }
}
