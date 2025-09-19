using System;

public class UnionFind
{
    private int[] data;
    public UnionFind(int size)
    {
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = -1;
    }
    public bool Unite(int x, int y)
    {
        x = Root(x);
        y = Root(y);
        if (x != y)
        {
            if (data[y] < data[x])
            {
                var tmp = y;
                y = x;
                x = tmp;
            }
            data[x] += data[y];
            data[y] = x;
        }
        return x != y;
    }
    public bool IsSameGroup(int x, int y) => Root(x) == Root(y);
    public int Root(int x) => data[x] < 0 ? x : data[x] = Root(data[x]);
    public int getMem(int x) => -data[Root(x)];
}


public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var n = int.Parse(Console.ReadLine().Trim());
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, a);
        }
    }
    static void getAns(int n, int[] a)
    {
        var uf = new UnionFind(n + 10);
        for (int i = 0; i < n - 2; i++)
        {
            if (a[i] == 1)
            {
                uf.Unite(i + 1, i + 2);
                uf.Unite(i + 2, i + 3);
            }
        }
        for (int i = 0; i < n - 2; i++)
        {
            if (a[i] == 0)
            {
                var p1 = uf.Root(i + 1);
                var p2 = uf.Root(i + 2);
                var p3 = uf.Root(i + 3);
                if (p1 == p2 && p2 == p3) { Console.WriteLine("NO"); return; }
            }
        }
        Console.WriteLine("YES");
    }
}

