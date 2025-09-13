using System;

class Program
{

    const int SIZE = 5;
    const int INF = -(int)1e9;
    static string targetString = "narek";

    static void Main()
    {

        var input = Console.In;
        var output = Console.Out;

        int testcases = int.Parse(input.ReadLine());

        while (testcases-- > 0)
        {
            var dimensions = input.ReadLine().Split();
            int rows = int.Parse(dimensions[0]);
            int columns = int.Parse(dimensions[1]);

            int[] prevScores = new int[SIZE];
            int[] currScores = new int[SIZE];

            for (int i = 0; i < SIZE; i++)
            {

                prevScores[i] = INF;
                currScores[i] = INF;
            }

            prevScores[0] = 0;

            for (int row = 0; row < rows; row++)
            {
                string inputString = input.ReadLine();
                Array.Copy(prevScores, currScores, SIZE);

                for (int z = 0; z < SIZE; z++)
                {
                    int k = z, score = currScores[z];

                    for (int col = 0; col < columns; col++)
                    {

                        if (targetString.Contains(inputString[col]))
                            score--;

                        if (inputString[col] == targetString[k])
                            k++;

                        if (k == SIZE)
                        {
                            score += 2 * SIZE;
                            k = 0;
                        }
                    }

                    prevScores[k] = Math.Max(prevScores[k], score);
                    prevScores[0] = Math.Max(prevScores[0], score);
                }
            }

            output.WriteLine(prevScores[0]);
        }
    }
}