using System;
using System.Collections.Generic;

class Program {
    static void Main() {
        int testCases = int.Parse(Console.ReadLine());
        while (testCases-- > 0) {
            string[] input = Console.ReadLine().Split();
            int rows = int.Parse(input[0]);
            int cols = int.Parse(input[1]);
            int radius = int.Parse(input[2]);

            string[] grid = new string[rows];
            for (int i = 0; i < rows; i++) {
                grid[i] = Console.ReadLine();
            }

            int[,] prefixSum = new int[rows + 1, cols + 1];
            int totalGold = 0;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    int isGold = grid[i][j] == 'g' ? 1 : 0;
                    totalGold += isGold;
                    prefixSum[i + 1, j + 1] = prefixSum[i + 1, j] + prefixSum[i, j + 1] - prefixSum[i, j] + isGold;
                }
            }

            int GetGoldInRegion(int x1, int y1, int x2, int y2) {
                if (x1 > x2 || y1 > y2) return 0;
                return prefixSum[x2 + 1, y2 + 1] - prefixSum[x1, y2 + 1] - prefixSum[x2 + 1, y1] + prefixSum[x1, y1];
            }

            int minLoss = int.MaxValue;
            int offset = radius - 1;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (grid[i][j] == '.') {
                        int x1 = Math.Max(0, i - offset);
                        int y1 = Math.Max(0, j - offset);
                        int x2 = Math.Min(rows - 1, i + offset);
                        int y2 = Math.Min(cols - 1, j + offset);
                        int lostGold = GetGoldInRegion(x1, y1, x2, y2);
                        minLoss = Math.Min(minLoss, lostGold);
                    }
                }
            }

            Console.WriteLine(totalGold - minLoss);
        }
    }
}
