using System.Text;

namespace AA;
class Program
{
    static int Solve()
    {
        int n = Next();
        int[] a = new int[n];
        var nn = new Dictionary<int, List<int>>();
        for (int i = 0; i < n; i++)
        {
            a[i] = Next();
            if (nn.TryGetValue(a[i], out List<int> l))
            {
                l.Add(i);
            }
            else
            {
                nn[a[i]] = new List<int>() { i };
            }
        }

        SegmentTree<int> tr = new SegmentTree<int>(new int[n], 0, Math.Max);
        for (int i = 0; i < n; i++)
        {
            List<int> ll = nn[a[i]];
            int index = ll.BinarySearch(i);
            if (index - a[i] + 1 >= 0)
            {
                tr.Modify(i, a[i] + tr.Query(0, ll[index - a[i] + 1]));
            }
        }

        return tr.Query(0, n); ;
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
        for (int i = 0; i < t; i++) writer.WriteLine(Solve());
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