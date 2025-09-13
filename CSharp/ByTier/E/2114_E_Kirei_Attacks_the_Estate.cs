public class Program
{
    private void Solve(int src, int parent, List<List<int>> adj, long[] dangers, long[] maxValues, long[] minValues)
    {
        if (parent != -1)
        {
            maxValues[src] = Math.Max(dangers[src], dangers[src] - minValues[parent]);
            minValues[src] = Math.Min(dangers[src], dangers[src] - maxValues[parent]);
        }
        else
        {
            maxValues[src] = dangers[src];
            minValues[src] = 0;
        }

        foreach (int neighbor in adj[src])
        {
            if (neighbor == parent) continue;

            Solve(neighbor, src, adj, dangers, maxValues, minValues);
        }
    }
    // Standard input start
    private void Input(out int input)
    {
        input = Convert.ToInt32(Console.ReadLine());
    }
    private void Input(int[][] arr)
    {
        for (int i = 0; i < arr.Length; i++)
        {
            var input = Console.ReadLine()!.Split();
            arr[i] = Array.ConvertAll(input, s => int.Parse(s));
        }
    }
    private void Input(int[] arr)
    {
        var input = Console.ReadLine()!.Split();
        var temp = Array.ConvertAll(input, s => int.Parse(s));
        Array.Copy(temp, arr, arr.Length);
    }
    private void Input(long[] arr)
    {
        var input = Console.ReadLine()!.Split();
        var temp = Array.ConvertAll(input, s => long.Parse(s));
        Array.Copy(temp, arr, arr.Length);
    }
    // Standard input end

    private void Input()
    {
        int t = Convert.ToInt32(Console.ReadLine());

        while (t-- > 0)
        {
            int n = Convert.ToInt32(Console.ReadLine());
            var adj = new List<List<int>>();
            var dangers = new long[n];
            var maxValues = new long[n];
            var minValues = new long[n];
            Array.Fill(maxValues, long.MinValue);

            for (int i = 0; i < n; i++)
            {
                adj.Add(new List<int>());
            }

            Input(dangers);

            for (int i = 0; i < n - 1; i++)
            {
                var input = Console.ReadLine()!.Split();
                var temp = Array.ConvertAll(input, s => int.Parse(s));

                int u = temp[0] - 1;
                int v = temp[1] - 1;

                adj[u].Add(v);
                adj[v].Add(u);
            }

            Solve(0, -1, adj, dangers, maxValues, minValues);

            foreach (long r in maxValues)
            {
                Console.Write(r + " ");
            }
        }
    }
    static void Main(string[] args)
    {
        var program = new Program();
        program.Input();
    }
}