using System;
using System.Collections.Generic;

class ObstacleCourseSolver
{
    static void Main()
    {
        int testCases = int.Parse(Console.ReadLine());
        
        while (testCases-- > 0)
        {
            int obstacleCount = int.Parse(Console.ReadLine());
            int[] heightChanges = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
            
            int[] lowerBounds = new int[obstacleCount];
            int[] upperBounds = new int[obstacleCount];
            
            for (int i = 0; i < obstacleCount; i++)
            {
                string[] bounds = Console.ReadLine().Split();
                lowerBounds[i] = int.Parse(bounds[0]);
                upperBounds[i] = int.Parse(bounds[1]);
            }

            // dp[i] stores {minPossibleHeight, maxPossibleHeight} after i-th obstacle
            (int Min, int Max)[] dp = new (int, int)[obstacleCount + 1];
            dp[0] = (0, 0); // Initial height is zero

            bool isPossible = true;

            // Forward DP: Calculate feasible height intervals
            for (int i = 1; i <= obstacleCount; i++)
            {
                int currentLower = lowerBounds[i - 1];
                int currentUpper = upperBounds[i - 1];
                var prev = dp[i - 1];
                int minHeight, maxHeight;

                switch (heightChanges[i - 1])
                {
                    case 0:  // Height doesn't increase
                        minHeight = prev.Min;
                        maxHeight = prev.Max;
                        break;
                    case 1:  // Height increases by 1
                        minHeight = prev.Min + 1;
                        maxHeight = prev.Max + 1;
                        break;
                    default: // Unknown change (-1), can be 0 or 1
                        minHeight = prev.Min;
                        maxHeight = prev.Max + 1;
                        break;
                }

                // Intersect with current obstacle's bounds
                minHeight = Math.Max(minHeight, currentLower);
                maxHeight = Math.Min(maxHeight, currentUpper);

                if (minHeight > maxHeight)
                {
                    isPossible = false;
                    break;
                }
                dp[i] = (minHeight, maxHeight);
            }

            if (!isPossible)
            {
                Console.WriteLine(-1);
                continue;
            }

            // Backward reconstruction of height changes
            int[] solution = new int[obstacleCount];
            int currentHeight = dp[obstacleCount].Min; // Pick min height at end

            for (int i = obstacleCount; i >= 1; i--)
            {
                var prev = dp[i - 1];

                switch (heightChanges[i - 1])
                {
                    case 0:
                        solution[i - 1] = 0;
                        // Height stays same
                        break;
                    case 1:
                        solution[i - 1] = 1;
                        currentHeight -= 1;
                        break;
                    default: // Unknown change (-1)
                        if (currentHeight >= prev.Min && currentHeight <= prev.Max)
                        {
                            solution[i - 1] = 0;
                            // Height stays same
                        }
                        else
                        {
                            solution[i - 1] = 1;
                            currentHeight -= 1;
                        }
                        break;
                }
            }

            if (currentHeight != 0)
            {
                Console.WriteLine(-1);
                continue;
            }

            // Print solution
            Console.WriteLine(string.Join(" ", solution));
        }
    }
}