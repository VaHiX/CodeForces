namespace Program;

public class Solver(int n, List<(int, int, int)> monsters)
{
    public void Solve()
    {
        long res;
        if (n == 1) res = 1;
        else if (n == 2) res = 2;
        else
        {
            var m1 = monsters.OrderBy(o => o.Item1).ToList();
            var m2 = monsters.OrderBy(o => o.Item2).ToList();

            long x = m1[n - 1].Item1 - m1[0].Item1 + 1;
            long y = m2[n - 1].Item2 - m2[0].Item2 + 1;
            res = x * y;

            // lets remove x -> 0
            if (m1[0].Item1 < m1[1].Item1)
            {
                x = m1[n - 1].Item1 - m1[1].Item1 + 1;
                y = m2[n - 1].Item2 - m2[0].Item2 + 1;
                if (m2[n - 1].Item3 == m1[0].Item3)
                    y = m2[n - 2].Item2 - m2[0].Item2 + 1;
                if (m2[0].Item3 == m1[0].Item3)
                    y = m2[n - 1].Item2 - m2[1].Item2 + 1;

                long size = x * y;
                if (size > n - 1)
                {
                    if (size < res)
                        res = size;
                }
                else
                {
                    size = x * (y + 1);
                    if (size < res)
                        res = size;
                    size = (x + 1) * y;
                    if (size < res)
                        res = size;
                }
            }

            // lets remove x -> n - 1
            if (m1[n - 1].Item1 > m1[n - 2].Item1)
            {
                x = m1[n - 2].Item1 - m1[0].Item1 + 1;
                y = m2[n - 1].Item2 - m2[0].Item2 + 1;
                if (m2[n - 1].Item3 == m1[n - 1].Item3)
                    y = m2[n - 2].Item2 - m2[0].Item2 + 1;
                if (m2[0].Item3 == m1[n - 1].Item3)
                    y = m2[n - 1].Item2 - m2[1].Item2 + 1;

                long size = x * y;
                if (size > n - 1)
                {
                    if (size < res)
                        res = size;
                }
                else
                {
                    size = x * (y + 1);
                    if (size < res)
                        res = size;
                    size = (x + 1) * y;
                    if (size < res)
                        res = size;
                }
            }

            // lets remove y -> 0
            if (m2[0].Item2 < m2[1].Item2)
            {
                y = m2[n - 1].Item2 - m2[1].Item2 + 1;
                x = m1[n - 1].Item1 - m1[0].Item1 + 1;
                if (m1[n - 1].Item3 == m2[0].Item3)
                    x = m1[n - 2].Item1 - m1[0].Item1 + 1;
                if (m1[0].Item3 == m2[0].Item3)
                    x = m1[n - 1].Item1 - m1[1].Item1 + 1;

                long size = x * y;
                if (size > n - 1)
                {
                    if (size < res)
                        res = size;
                }
                else
                {
                    size = x * (y + 1);
                    if (size < res)
                        res = size;
                    size = (x + 1) * y;
                    if (size < res)
                        res = size;
                }
            }

            // lets remove y -> n - 1
            if (m2[n - 1].Item2 > m2[n - 2].Item2)
            {
                y = m2[n - 2].Item2 - m2[0].Item2 + 1;
                x = m1[n - 1].Item1 - m1[0].Item1 + 1;
                if (m2[n - 1].Item3 == m1[n - 1].Item3)
                    x = m1[n - 2].Item1 - m1[0].Item1 + 1;
                if (m2[n - 1].Item3 == m1[0].Item3)
                    x = m1[n - 1].Item1 - m1[1].Item1 + 1;

                long size = x * y;
                if (size > n - 1)
                {
                    if (size < res)
                        res = size;
                }
                else
                {
                    size = x * (y + 1);
                    if (size < res)
                        res = size;
                    size = (x + 1) * y;
                    if (size < res)
                        res = size;
                }
            }
        }

        Console.WriteLine(res);
    }
}

public static class Program
{
    public static void Main(string[] args)
    {
        IInputReader inputReader = new ConsoleInputReader();
        if (args.Length > 0)
            inputReader = new FileInputReader(args[0]);

        var t = InputParser.GetNumber(inputReader);
        for (int i = 1; i <= t; i++)
        {
            int n = InputParser.GetNumber(inputReader);
            List<(int, int, int)> monsters = [];
            for (int j = 1; j <= n; j++)
            {
                var x = InputParser.GetNumbers(inputReader);
                monsters.Add((x[0], x[1], j));
            }

            new Solver(n, monsters).Solve();
        }
    }
}

#region Input

internal static class InputParser
{
    public static int GetNumber(IInputReader inputReader) => int.Parse(inputReader.ReadLine()!);

    public static List<int> GetNumbers(IInputReader inputReader) =>
        inputReader.ReadLine()!.Split(' ').Select(int.Parse).ToList();
}

internal interface IInputReader
{
    string? ReadLine();
}

internal class ConsoleInputReader : IInputReader
{
    public string? ReadLine() => Console.ReadLine();
}

internal class FileInputReader(string filePath) : IInputReader
{
    private readonly string[] _lines = File.ReadAllLines(filePath);
    private int _currentLine;

    public string ReadLine() => _lines[_currentLine++];
}

#endregion