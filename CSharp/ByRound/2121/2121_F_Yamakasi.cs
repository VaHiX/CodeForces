internal class Program
{
    static int F_L_X_R(long a, long b)
    {
        string a_str = a.ToString();
        string b_str = b.ToString();
        int res = 0;
        for (int i = 0; i < a_str.Length; i++)
        {
            if (a_str[i] == b_str[i])
            {
                res++;
            }
        }
        return res;
    }

    static long solve(List<int> ai, long n, long s, long x)
    {
        long res = 0;
        long[] pref = new long[n + 1];
        for (int i = 1; i <= n; i++)
            pref[i] = pref[i - 1] + ai[i - 1];

        var cnt = new Dictionary<long, int>();
        int lef = 1;

        for (int r = 1; r <= n; r++)
        {
            if (ai[r - 1] > x)
            {
                cnt.Clear();
                lef = r + 1;
            }
            else if (ai[r - 1] == x)
            {
                while (lef <= r)
                {
                    long key = pref[lef - 1];
                    if (!cnt.ContainsKey(key)) cnt[key] = 0;
                    cnt[key]++;
                    lef++;
                }
            }

            long target = pref[r] - s;
            if (cnt.TryGetValue(target, out int count))
                res += count;
        }

        return res;
    }

    private static void Main(string[] args)
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            List<long> nsx = Console.ReadLine().Split().Select(long.Parse).ToList();
            long n = nsx[0];
            long s = nsx[1];
            long x = nsx[2];
            List<int> ai = Console.ReadLine().Split().Select(int.Parse).ToList();

            long res = solve(ai, n, s, x);

            Console.WriteLine(res);
        }
    }
}