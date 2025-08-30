namespace Name
{
    class Program
    {
        static void Main(string[] args)
        {
            int t = int.Parse(Console.ReadLine());
            while (t-- > 0)
            {
                int n = int.Parse(Console.ReadLine());
                string[] a = Console.ReadLine().Split();
                SortedDictionary<int, int> mp = new SortedDictionary<int, int>();
                for (int i = 0; i < n; i++)
                {
                    int x = int.Parse(a[i]);
                    if (x == -1) continue;
                    if (mp.ContainsKey(x)) mp[x]++;
                    else mp[x] = 1;
                }
                if (mp.ContainsKey(0))
                {
                    Console.WriteLine("NO");
                    continue;
                }
                Console.WriteLine(mp.Count() > 1 ? "NO" : "YES");
            }
        }
    }
}