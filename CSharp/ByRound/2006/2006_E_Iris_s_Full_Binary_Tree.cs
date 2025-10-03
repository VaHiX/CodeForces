using System;

public class Program
{
    const int MAX_N = 500100;
    static int[,] f = new int[MAX_N + 1, 20];
    static int[] p = new int[MAX_N + 1];
    static int[,] s = new int[MAX_N + 1, 23];
    static int[] d = new int[MAX_N + 1];
    static int[] zk = new int[MAX_N + 1];

    // Function to compute LCA (Lowest Common Ancestor)
    static int LCA(int x, int y)
    {
        if (d[x] < d[y])
            (x, y) = (y, x);

        int a = d[x] - d[y];
        for (int i = 19; i >= 0; i--)
        {
            if (((a >> i) & 1) != 0)
                x = f[x, i];
        }

        if (x == y)
            return x;

        for (int i = 19; i >= 0; i--)
        {
            if (f[x, i] != f[y, i])
            {
                x = f[x, i];
                y = f[y, i];
            }
        }

        return f[x, 0];
    }

    // Function to get the k-th ancestor of a node
    static int Kth(int x, int k)
    {
        for (int i = 0; i < 20; i++)
        {
            if (((k >> i) & 1) != 0)
                x = f[x, i];
        }

        return x;
    }

    // Function to calculate the distance between two nodes
    static int Dis(int x, int y)
    {
        return d[x] + d[y] - 2 * d[LCA(x, y)];
    }

    // Function to update the sums for a node's ancestors
    static void Doi(int x, int z)
    {
        int o = x;
        for (int i = 0; i <= 20; i++)
        {
            if (i != 0)
            {
                o = p[o];
                if (o == 0)
                    break;
            }
            s[o, i] += z;
        }
    }

    // Function to find the smallest `e` where the sum is non-zero
    static int Sp(int x)
    {
        int e = 0;
        while (e <= 20 && s[x, e] == 0)
            e++;
        return e;
    }

    // Function to perform the ask2 operation
    static int Ask2(int x)
    {
        int fk = int.MaxValue;
        int o = x;
        for (int i = 0; i <= 20; i++)
        {
            if (i != 0)
            {
                o = p[o];
                if (o == 0)
                    break;
            }
            fk = Math.Min(fk, i + Sp(o));
        }

        return fk;
    }

    // Function to perform the ask1 operation
    static int Ask1(int x)
    {
        int fk = int.MaxValue;
        int o = x;
        for (int i = 0; i <= 20; i++)
        {
            if (i != 0)
            {
                o = p[o];
                if (o == 0)
                    break;
            }
            fk = Math.Min(fk, Math.Max(0, i - 1) + Sp(o));
        }

        return fk;
    }

    // Function to solve the problem for a given test case
    static void Sol()
    {
        int n = int.Parse(Console.ReadLine());

        // Read parents p[2..n]
        string[] parentInputs = Console.ReadLine().Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
        for (int i = 2; i <= n; i++)
        {
            p[i] = int.Parse(parentInputs[i - 2]); // Adjust index because parentInputs[0] corresponds to p[2]
            f[i, 0] = p[i];
            d[i] = d[p[i]] + 1;
        }

        // Preprocessing for binary lifting
        for (int o = 1; o < 20; o++)
        {
            for (int i = 1; i <= n; i++)
            {
                f[i, o] = f[f[i, o - 1], o - 1];
            }
        }

        // Initialize s array
        for (int i = 1; i <= n; i++)
        {
            for (int o = 0; o <= 20; o++)
            {
                s[i, o] = 0;
            }
        }

        int a = 1, b = 1;
        Array.Clear(zk, 0, zk.Length);
        zk[1] = -1;
        bool gg = false;

        for (int i = 1; i <= n; i++)
        {
            if (gg)
            {
                Console.Write("-1 ");
                continue;
            }

            if (Dis(a, b) < Dis(b, i)) a = i;
            if (Dis(a, b) < Dis(a, i)) b = i;

            if (d[a] < d[b]) (a, b) = (b, a);

            Doi(i, 1);

            if (i > 1)
            {
                int fa = p[i];
                zk[fa]++;
                if (zk[fa] > 2)
                {
                    gg = true;
                    Console.Write("-1 ");
                    continue;
                }

                if (zk[fa] == 2)
                    Doi(fa, -1);
            }

            int lc = LCA(a, b);
            int di = d[a] + d[b] - 2 * d[lc];

            if (((d[a] ^ d[b]) & 1) != 0)
                Console.Write($"{1 + Ask1(Kth(a, di / 2)) + (di + 1) / 2} ");
            else
                Console.Write($"{1 + Ask2(Kth(a, di / 2)) + di / 2} ");
        }

        Console.WriteLine();
    }

    // Main function to handle multiple test cases
    public static void Main(string[] args)
    {
        int T = int.Parse(Console.ReadLine());

        for (int t = 0; t < T; t++)
        {
            Sol();
        }
    }
}
