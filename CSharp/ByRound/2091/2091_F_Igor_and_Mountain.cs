using System;
using System.Linq; // Used for parsing multiple numbers from input line

public class Solver
{
    const long Mod = 998244353;

    // Helper function for correct modulo operation (handles negative results)
    static long M(long x)
    {
        return (x % Mod + Mod) % Mod;
    }
    
    // Overload for subtractions where intermediate result might be large negative
    static long M(long a, long b)
    {
         return ((a - b) % Mod + Mod) % Mod;
    }


    public static void Main(string[] args)
    {
        // Read number of test cases
        int t = int.Parse(Console.ReadLine());

        while (t-- > 0)
        {
            // Read n, m, d
            long[] input = Console.ReadLine().Split().Select(long.Parse).ToArray();
            long n = input[0];
            long m = input[1];
            long d = input[2];
            long ans = 0;

            // Initialize DP arrays and grid
            long[] cur = new long[m + 1];
            long[] prev = new long[m + 1];
            bool[,] v = new bool[n + 1, m + 1];

            // Read grid
            for (int i = 1; i <= n; i++)
            {
                string row = Console.ReadLine();
                for (int j = 1; j <= m; j++)
                {
                    // C# string is 0-indexed, grid v is 1-indexed
                    v[i, j] = (row[j - 1] != '#');
                }
            }

            // Base case: Calculate prefix sums for the first row
            for (int i = 1; i <= m; i++)
            {
                prev[i] = prev[i - 1] + (v[1, i] ? 1L : 0L);
                // No modulo needed here as it's just counting 0s and 1s
            }

            // Calculate initial 'cur' based on the first row's possibilities
            for (int i = 1; i <= m; i++)
            {
                // Only consider valid cells
                if (v[1, i]) {
                   long count = M(prev[Math.Min(i + d, m)], prev[Math.Max(0L, i - d - 1)]);
                   cur[i] = count; // Already modulo handled by M
                } else {
                   cur[i] = 0;
                }
            }


            // Iterate through the remaining rows (Dynamic Programming)
            for (int i = 2; i <= n; i++)
            {
                // Calculate prefix sums for 'cur' (ways to reach row i-1)
                for (int j = 1; j <= m; j++)
                {
                    cur[j] += cur[j - 1];
                    cur[j] = M(cur[j]);
                }

                // Calculate 'prev' (representing ways to reach row i, step 1)
                // This seems to be an intermediate calculation step in the C++ code
                for (int j = 1; j <= m; j++)
                {
                    if (v[i, j]) {
                        // Calculate reachable range from previous row's 'cur' prefix sums
                        long count = M(cur[Math.Min(j + d - 1, m)], cur[Math.Max(0L, j - d)]);
                        prev[j] = count;
                    } else {
                        prev[j] = 0;
                    }
                }

                // Calculate prefix sums for 'prev'
                for (int j = 1; j <= m; j++)
                {
                    prev[j] += prev[j - 1];
                    prev[j] = M(prev[j]);
                }

                 // Calculate 'cur' (representing ways to reach row i, step 2 - final for this row)
                for (int j = 1; j <= m; j++)
                {
                    if (v[i, j]) {
                         // Calculate reachable range from the 'prev' prefix sums calculated above
                        long count = M(prev[Math.Min(j + d, m)], prev[Math.Max(0L, j - d - 1)]);
                        cur[j] = count;
                    } else {
                        cur[j] = 0;
                    }
                }
                // The 'cur' array now holds the counts for row 'i', ready for the next iteration or final sum
            }

            // Calculate the final answer by summing up possibilities in the last row
            for (int j = 1; j <= m; j++)
            {
                ans += cur[j];
                ans = M(ans);
            }

            Console.WriteLine(ans);
        }
    }
}