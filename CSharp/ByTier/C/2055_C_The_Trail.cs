using System;
using System.Linq;

public class Program
{
    static void Solve()
    {
        var dimensions = Console.ReadLine().Split();
        int rows = int.Parse(dimensions[0]);
        int columns = int.Parse(dimensions[1]);
        string moves = Console.ReadLine();
        
        long[,] grid = new long[rows + 1, columns + 1];
        long[] rowSums = new long[rows + 1];
        long[] columnSums = new long[columns + 1];

        for (int i = 1; i <= rows; i++)
        {
            var rowValues = Console.ReadLine().Split().Select(long.Parse).ToArray();
            for (int j = 1; j <= columns; j++)
            {
                grid[i, j] = rowValues[j - 1];
                rowSums[i] += grid[i, j];
                columnSums[j] += grid[i, j];
            }
        }

        int currentRow = 1, currentColumn = 1;
        foreach (char move in moves)
        {
            long tempValue = (move == 'D') ? -rowSums[currentRow] : -columnSums[currentColumn];
            grid[currentRow, currentColumn] = tempValue;

            if (move == 'D')
            {
                rowSums[currentRow] = tempValue + grid[currentRow, currentColumn];
                columnSums[currentColumn] += tempValue;
                currentRow++;
            }
            else
            {
                columnSums[currentColumn] = tempValue + grid[currentRow, currentColumn];
                rowSums[currentRow] += tempValue;
                currentColumn++;
            }
        }

        grid[rows, columns] = -columnSums[columns];

        for (int i = 1; i <= rows; i++)
        {
            Console.WriteLine(string.Join(" ", Enumerable.Range(1, columns).Select(j => grid[i, j])));
        }
    }

    public static void Main()
    {
        int testCases = int.Parse(Console.ReadLine());
        for (int i = 0; i < testCases; i++)
        {
            Solve();
        }
    }
}
