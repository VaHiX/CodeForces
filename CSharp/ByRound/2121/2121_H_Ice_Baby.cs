using System.Text;

namespace IceBaby;
class Program
{
    static void Solve()
    {
        int n = Next();
        int[] l = new int[n];
        int[] r = new int[n];
        var ll = new (int v, int i)[n];
        for (int i = 0; i < n; i++)
        {
            l[i] = Next();
            ll[i] = (l[i], i);
            r[i] = Next();
        }
        Array.Sort(ll);
        int[] ri = new int[n];
        for (int i = 0; i < n; i++)
        {
            if (ll[^1].v < r[i])
            {
                ri[i] = -1;
            }
            else
            {
                int x = -1, y = n;
                while (x + 1 < y)
                {
                    int z = (x + y) >> 1;
                    if (ll[z].v <= r[i]) x = z;
                    else y = z;
                }
                ri[i] = y;
            }
        }
        for (int i = 0; i < n; i++) ll[i].v = i;
        Array.Sort(ll, (x, y) => x.i.CompareTo(y.i));

        int[] array = new int[n];
        Array.Fill(array, int.MaxValue);
        SegmentTree<int> tr = new(array, int.MaxValue, Math.Min);
        int max = 0;
        for (int i = 0; i < n; i++)
        {
            if (ri[i] != -1)
            {
                var min = tr.Query(ri[i], n);
                if (min != int.MaxValue)
                {
                    tr.Modify(min, int.MaxValue);
                    max--;
                }
            }
            tr.Modify(ll[i].v, ll[i].v);
            max++;

            writer.Write(max);
            writer.Write(' ');
        }
        writer.WriteLine();
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



    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) Solve();
        writer.Flush();
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
