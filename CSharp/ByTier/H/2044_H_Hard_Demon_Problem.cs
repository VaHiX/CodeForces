using System;
using System.Text;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        
        // Prepare StringBuilder for efficient output
        StringBuilder outputBuffer = new StringBuilder();
        
        while (t-- > 0)
        {
            int n, q;
            var inputs = Console.ReadLine().Split();
            n = int.Parse(inputs[0]);
            q = int.Parse(inputs[1]);
            
            // Read the matrix M
            long[,] M = new long[n, n];
            for (int r = 0; r < n; r++)
            {
                inputs = Console.ReadLine().Split();
                for (int c = 0; c < n; c++)
                {
                    M[r, c] = long.Parse(inputs[c]);
                }
            }
            
            // Initialize prefix sum matrices
            long[,] S = new long[n + 1, n + 1];
            long[,] Sr = new long[n + 1, n + 1];
            long[,] Sc = new long[n + 1, n + 1];
            
            // Fill the prefix sum matrices
            for (int r = 1; r <= n; r++)
            {
                long current_S = 0;
                long current_Sr = 0;
                long current_Sc = 0;
                for (int c = 1; c <= n; c++)
                {
                    long val = M[r - 1, c - 1];
                    current_S += val;
                    current_Sr += val * r;
                    current_Sc += val * c;
                    
                    // Compute the prefix sums
                    S[r, c] = S[r - 1, c] + current_S;
                    Sr[r, c] = Sr[r - 1, c] + current_Sr;
                    Sc[r, c] = Sc[r - 1, c] + current_Sc;
                }
            }
            
            // Process each query
            for (int i = 0; i < q; i++)
            {
                var query = Console.ReadLine().Split();
                int x1 = int.Parse(query[0]);
                int y1 = int.Parse(query[1]);
                int x2 = int.Parse(query[2]);
                int y2 = int.Parse(query[3]);
                
                // Calculate submatrix sums
                long S_sub = S[x2, y2] - S[x1 - 1, y2] - S[x2, y1 - 1] + S[x1 - 1, y1 - 1];
                long Sr_sub = Sr[x2, y2] - Sr[x1 - 1, y2] - Sr[x2, y1 - 1] + Sr[x1 - 1, y1 - 1];
                long Sc_sub = Sc[x2, y2] - Sc[x1 - 1, y2] - Sc[x2, y1 - 1] + Sc[x1 - 1, y1 - 1];
                
                // Width of the column range
                int W = y2 - y1 + 1;
                
                // Compute the result for this query
                long sum_val = (long)W * (Sr_sub - (long)x1 * S_sub) + (Sc_sub - (long)(y1 - 1) * S_sub);
                
                // Append result to the output
                outputBuffer.Append(sum_val).Append(' ');
            }
            
            // Output the result for this test case
            Console.WriteLine(outputBuffer.ToString().Trim());
            outputBuffer.Clear();
        }
    }
}
