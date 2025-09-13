int T = Convert.ToInt32(Console.ReadLine());
long MOD = 1000000007;
long PowMod(long a, long b, long mod = 1000000007)
{
    long result = 1;
    a %= mod;
    while (b > 0)
    {
        if ((b & 1) == 1)
            result = (result * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return result;
}
while (T-- > 0)
{
    int n = int.Parse(Console.ReadLine());
    List<List<int>> g = new List<List<int>>();
    for (int i = 0; i < n; i++)
    {
        g.Add(new List<int>());
    }
    
    for (int i = 0; i < n-1; i++)
    {
        string[] str = Console.ReadLine().Split(' ');
        int a =  int.Parse(str[0]);
        int b =  int.Parse(str[1]);
        a--;
        b--;
        g[a].Add(b);
        g[b].Add(a);
    }
    
    
    double solve()
    {
        if (g.Where((v, i) => i != 0 && v.Count == 1).Count() > 2) return 0;
        if (g.Where((v, i) => i != 0 && v.Count == 1).Count() == 1)
        {
            return PowMod(2, n);
        }
        Queue<(int,bool?)> q = new();
        bool[] used = new bool[n];
        q.Enqueue((0, null));
        int x=0, y=0, u=0;
        while (q.Any())
        {
            (var v, var type) = q.Dequeue();
            used[v] = true;
            if (type == true)
            {
                x++;
                if (g[v].Count > 1) q.Enqueue((g[v].First(v => used[v] == false), type));
            }else if (type == false)
            {
                y++;
                if(g[v].Count > 1) q.Enqueue((g[v].First(v => used[v] == false), type));
            }else if (g[v].Count >= 3 || (v == 0 && g[v].Count > 1))
            {
                var vertex = g[v].Where(v => used[v] == false);
                u++;
                q.Enqueue((vertex.ElementAt(0), false));
                q.Enqueue((vertex.ElementAt(1), true));
            }
            else
            {
                u++;
                if(g[v].Any(v => used[v] == false)) q.Enqueue((g[v].First(v => used[v] == false), null));
            }
        }

        if (x == y)
        {
            return PowMod(2, u + 1) % 1000000007;
        }
        else
        {
            return (((PowMod(2, Math.Max(x,y) - Math.Min(x,y)) + 
                     PowMod(2, Math.Max(x,y) - Math.Min(x,y) - 1))%MOD) * PowMod(2, u))%MOD; 
        }
    }
    Console.WriteLine(solve());
}