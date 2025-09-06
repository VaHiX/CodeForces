using System.Text;

namespace LanesOfCars;
class Program
{
    static long Solve()
    {
        long n = Next();
        long k = Next();
        long[] a = new long[n];
        for (int i = 0; i < n; i++) a[i] = Next();
        Array.Sort(a);

        if (n == 1)
        {
            return a[0] * (a[0] + 1) / 2;
        }

        long l = a.Min() - 1, r = a.Max();
        while (l + 1 < r)
        {
            long m = (l + r) >> 1;
            long s = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[i] < m) s += m - a[i];
                else if (a[i] > m + k) s -= a[i] - (m + k);
            }
            if (s >= 0)
                r = m;
            else l = m;
        }

        long ans = 0;
        for (int i = 0, j = a.Length - 1; j > i && i < n; i++)
        {
            while (j > i && a[i] < l)
            {
                if (a[j] > r + k)
                {
                    long min = Math.Min(l - a[i], a[j] - (r + k));
                    ans += k * min;
                    a[i] += min;
                    a[j] -= min;
                }
                else j--;
            }
        }
        PriorityQueue<long, long> pq_min = new();
        PriorityQueue<long, long> pq_max = new();
        for (int i = 0; i < n; i++)
        {
            pq_max.Enqueue(i, -a[i]);
            pq_min.Enqueue(i, a[i]);
        }
        while (a[pq_min.Peek()] + k + 1 < a[pq_max.Peek()])
        {
            long i = pq_min.Dequeue();
            long j = pq_max.Dequeue();
            a[i]++;
            a[j]--;
            ans += k;
            pq_max.Enqueue(j, -a[j]);
            pq_min.Enqueue(i, a[i]);
        }

        for (int i = 0; i < n; i++)
            ans += a[i] * (a[i] + 1) / 2;

        return ans;


    }

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) writer.WriteLine(Solve());
        writer.Flush();
    }

    static long Next()
    {
        int c;
        int m = 1;
        long res = 0;
        do
        {
            c = reader.Read();
            if (c == '-')
                m = -1;
        } while (c < '0' || c > '9');
        res = c - '0';
        while (true)
        {
            c = reader.Read();
            if (c < '0' || c > '9')
                return m * res;
            res *= 10;
            res += c - '0';
        }
    }
    static readonly StreamReader reader = new(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
    static readonly StreamWriter writer = new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}