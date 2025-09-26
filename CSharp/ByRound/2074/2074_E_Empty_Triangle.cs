using System;

public class Program
{
    private const int MAX_QUERIES = 75;
    private static int queryCount = 0;

    // Function to perform an interactive query.
    private static int Query(int x, int y, int z)
    {
        if (queryCount >= MAX_QUERIES)
        {
            Environment.Exit(0); // Prevent exceeding query limit
        }
        
        Console.WriteLine($"? {x} {y} {z}");
        Console.Out.Flush();

        string input = Console.ReadLine();
        if (input == null)
        {
            Environment.Exit(0);
        }
        
        int response = int.Parse(input.Trim());
        
        if (response == -1)
        {
            Environment.Exit(0); // Handle invalid query termination
        }
        
        queryCount++;
        return response;
    }

    // Function to find and output the required triangle.
    private static void SolveTestCase()
    {
        int n = int.Parse(Console.ReadLine().Trim());
        
        // Start with the first three points.
        int a = 1, b = 2, c = 3;
        
        while (true)
        {
            int result = Query(a, b, c);
            if (result == 0)
            {
                break; // If empty, exit loop.
            }
            
            // Try replacing one of the points with the new result.
            if (Query(result, b, c) == 0) { a = result; continue; }
            if (Query(a, result, c) == 0) { b = result; continue; }
            if (Query(a, b, result) == 0) { c = result; continue; }
            
            // Update candidates for further iteration.
            int newB = Query(result, b, c);
            int newC = Query(a, result, c);
            a = result;
            b = newB;
            c = newC;
        }
        
        Console.WriteLine($"! {a} {b} {c}");
        Console.Out.Flush();
    }

    public static void Main(string[] args)
    {
        int t = int.Parse(Console.ReadLine().Trim());
        while (t-- > 0)
        {
            queryCount = 0;
            SolveTestCase();
        }
    }
}
