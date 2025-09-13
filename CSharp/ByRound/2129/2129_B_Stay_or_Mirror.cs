using System.Text;

namespace StayOrMirror;
class Program
{
    static long Solve()
    {
        int n = Next();
        var v = new int[n];
        var p = new int[n];
        for (int i = 0; i < n; i++)
        {
            v[i] = Next();
            p[i] = i;
        }
        Array.Sort(v, p);
        var array = new int[n];
        Array.Fill(array, 1);
        SegmentTree<int> tr = new(array, 0, (x, y) => x + y);
        long ans = 0;
        for (int i = 0; i < n; i++)
        {
            tr.Modify(p[i], 0);
            int l = tr.Query(0, p[i]);
            int r = tr.Query(p[i], n);
            ans += Math.Min(l, r);
        }
        return ans;
    }

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) writer.WriteLine(Solve());
        writer.Flush();
    }

    private class SegmentTree<T>
    {
        public delegate T Op(T x, T y);

        private readonly int n;
        private readonly T[] t;
        private readonly T def;
        private readonly Op operation;

        public SegmentTree(T[] array, T def, Op operation)
        {
            n = array.Length;
            this.def = def;
            this.operation = operation;
            t = new T[2 * n];
            Array.Copy(array, 0, t, n, n);
            Build();
        }

        private void Build()
        {
            for (int i = n - 1; i > 0; --i) t[i] = operation(t[i << 1], t[i << 1 | 1]);
        }

        public void Modify(int p, T value)
        {
            for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = operation(t[p], t[p ^ 1]);
        }

        public T Query(int l, int r)
        {
            T res = def;
            for (l += n, r += n; l < r; l >>= 1, r >>= 1)
            {
                if ((l & 1) == 1) res = operation(res, t[l++]);
                if ((r & 1) == 1) res = operation(res, t[--r]);
            }
            return res;
        }
    }


    static int Next()
    {
        int c;
        int m = 1;
        int res = 0;
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