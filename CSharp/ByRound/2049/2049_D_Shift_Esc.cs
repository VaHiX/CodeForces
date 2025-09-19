using System;
using System.Linq;

class Program {
    const long INF = (long)1e18;
    
    static void Main() {
        int t = int.Parse(Console.ReadLine());
        
        while (t-- > 0) {
            // Read inputs
            var inputs = Console.ReadLine().Split().Select(long.Parse).ToArray();
            int n = (int)inputs[0];
            int m = (int)inputs[1];
            long k = inputs[2];

            long[,] grid = new long[n, m];
            for (int i = 0; i < n; i++) {
                var row = Console.ReadLine().Split().Select(long.Parse).ToArray();
                for (int j = 0; j < m; j++) {
                    grid[i, j] = row[j];
                }
            }

            // Initialize DP arrays
            long[,] dpPrev = new long[m, m];
            long[,] dpCurrent = new long[m, m];
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    dpPrev[i, j] = INF;
                }
            }

            // Process the first row
            for (int s = 0; s < m; s++) {
                dpPrev[0, s] = k * s + grid[0, (0 + s) % m];
            }

            for (int j = 1; j < m; j++) {
                for (int s = 0; s < m; s++) {
                    if (dpPrev[j - 1, s] + grid[0, (j + s) % m] < dpPrev[j, s]) {
                        dpPrev[j, s] = dpPrev[j - 1, s] + grid[0, (j + s) % m];
                    }
                }
            }

            // Process remaining rows
            for (int i = 1; i < n; i++) {
                // Reset dpCurrent
                for (int j = 0; j < m; j++) {
                    for (int s = 0; s < m; s++) {
                        dpCurrent[j, s] = INF;
                    }
                }

                // Precompute minPrev for each column
                long[] minPrev = new long[m];
                for (int j = 0; j < m; j++) {
                    minPrev[j] = INF;
                    for (int sPrev = 0; sPrev < m; sPrev++) {
                        if (dpPrev[j, sPrev] < minPrev[j]) {
                            minPrev[j] = dpPrev[j, sPrev];
                        }
                    }
                }

                for (int s = 0; s < m; s++) {
                    for (int j = 0; j < m; j++) {
                        long cellVal = grid[i, (j + s) % m];
                        if (j == 0) {
                            // Coming from above
                            long cost = minPrev[j] + k * s + cellVal;
                            if (cost < dpCurrent[j, s]) {
                                dpCurrent[j, s] = cost;
                            }
                        }
                        else {
                            // Coming from above
                            long costFromAbove = minPrev[j] + k * s + cellVal;
                            // Coming from left
                            long costFromLeft = dpCurrent[j - 1, s] + cellVal;
                            dpCurrent[j, s] = Math.Min(dpCurrent[j, s], Math.Min(costFromAbove, costFromLeft));
                        }
                    }
                }

                // Swap dpPrev and dpCurrent
                Array.Copy(dpCurrent, dpPrev, dpCurrent.Length);
            }

            // Find the minimum cost at the bottom-right cell
            long answer = INF;
            for (int s = 0; s < m; s++) {
                answer = Math.Min(answer, dpPrev[m - 1, s]);
            }

            // Output the result
            Console.WriteLine(answer);
        }
    }
}
