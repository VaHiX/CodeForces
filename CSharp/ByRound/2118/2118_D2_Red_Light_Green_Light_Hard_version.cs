using System.Diagnostics;
using System.Numerics;
using System.Text;

using i64 = System.Int64;

Template.Snippet a = new();
a.Main();

namespace Template
{   
    internal class Snippet
    {
        static readonly i64 timestamp = Stopwatch.GetTimestamp();
        static readonly int seed = (int)(timestamp ^ (timestamp >> 32)); // 混合高低位
        static readonly Random rng = new Random(seed);
        static readonly i64 FIXED_RANDOM = rng.NextInt64();
        public void Solve()
        {
            int n = br.ReadInt32();
            i64 k = br.ReadInt64();
            i64[] p = br.ReadInt64(n);
            i64[] d = br.ReadInt64(n);
            int[] nxt = new int[2 * n];
            Array.Fill(nxt, -1);
            Dictionary<i64, int> f = new();
            for (int i = n - 1; i >= 0; i--) {
                i64 v = (d[i] - p[i] % k + k) % k;
                if (f.ContainsKey(v ^ FIXED_RANDOM)) {
                    nxt[n + i] = f[v ^ FIXED_RANDOM];
                }
                if (!f.ContainsKey(v ^ FIXED_RANDOM)) f.Add(v ^ FIXED_RANDOM, i);
                else f[v ^ FIXED_RANDOM] = i;
            }
            f = new();
            for (int i = 0; i < n; i++)
            {
                i64 v = (d[i] + p[i]) % k;
                if (f.ContainsKey(v ^ FIXED_RANDOM))
                {
                    nxt[i] = n + f[v ^ FIXED_RANDOM];
                }
                if (!f.ContainsKey(v ^ FIXED_RANDOM)) f.Add(v ^ FIXED_RANDOM, i);
                else f[v ^ FIXED_RANDOM] = i;
            }
            head = new int[n * 2];
            idx = 0;
            Array.Fill(head, -1);
            Queue<int> q = new();
            bool[] good = new bool[2 * n];
            for (int i = 0; i < 2 * n; i++) {
                if (nxt[i] == -1) {
                    good[i] = true;
                    q.Enqueue(i);
                } else {
                    addEdge(nxt[i], i);
                }
            }
            
            while (q.Count > 0) {
                int x = q.Dequeue();
                for (int i = head[x]; i >= 0; i = e[i].Item2) {
                    int y = e[i].Item1;
                    good[y] = true;
                    q.Enqueue(y);
                }
            }

            Dictionary<i64, List<(i64, int)>> vec = new();
            for (int i = 0; i < n; i++) {
                i64 v = (p[i] - d[i] + k) % k;
                if (!vec.ContainsKey(v ^ FIXED_RANDOM)) vec.Add(v ^ FIXED_RANDOM, new());
                vec[v ^ FIXED_RANDOM].Add((p[i], i));
            }
            int m = br.ReadInt32();
            while (m -- > 0) {
                i64 a = br.ReadInt64();
                i64 v = (a % k) ^ FIXED_RANDOM;
                if (!vec.ContainsKey(v))
                {
                    bw.AppendYes(true);
                    continue;
                }
                
                int i = lower_bound(vec[v], (a, 0));
                if (i == vec[v].Count) {
                    bw.AppendYes(true);
                    continue;
                }
                bw.AppendYes(good[vec[v][i].Item2]);
            }
        }

int lower_bound<T>(IList<T> a, T M) where T : IComparable<T>
{
    return lower_bound(a, 0, a.Count, M);
}
int lower_bound<T>(IList<T> a, int lo, int hi, T M) where T : IComparable<T>
{
    while (lo < hi)
    {
        int x = (lo + hi) / 2;
        if (a[x].CompareTo(M) >= 0)
        {
            hi = x;
        } else
        {
            lo = x + 1;
        }
    }
    return hi;
}

static readonly int N = 400_000;
(int, int)[] e = new (int, int)[N];
int[] head;

int idx = 0;

void addEdge(int u, int v)
{
    e[idx] = (v, head[u]);
    head[u] = idx++;
}
        public void Main()
        {
            int T = 1;
            T = br.ReadInt32();
            while (T-- > 0)
            {
                Solve();
            }
            bw.Output();
        }
        #region FastIO
#if LOCAL
        private static readoFILEPATH = in.txt";
        private readonly BufferedReader br = new(new FileStream("in.txt", FileMode.OpenOrCreate, FileAccess.ReadWrite), 0);
#else
        private readonly BufferedReader br = new(Console.OpenStandardInput(), 1 << 16);
#endif
        private readonly BufferedWriter bw = new();
        #endregion
    }

    #region IO
    internal class BufferedReader : IDisposable
    {
        private StreamReader sr;
        private char[] buffer;
        private int S = 0, T = 0;

        private int Peek()
        {
            if (buffer == null)
            {
                return sr.Peek();
            }
            if (S == T)
            {
                T = sr.ReadBlock(buffer.AsSpan());
                if (T == 0) return -1;
                S = 0;
            }
            return buffer[S];
        }

        private int Read()
        {
            if (buffer == null)
            {
                return sr.Read();
            }
            int p = Peek();
            if (p >= 0) ++S;
            return p;
        }

        public string ReadString()
        {
            int c;
            StringBuilder sb = new();
            while ((c = Read()) != -1)
            {
                if (c == '\r' || c == ' ') continue; // omit '\r'
                if (c == '\n')
                {
                    if (sb.Length > 0) break;
                    else continue; // omit empty lines
                }
                sb.Append((char)c);
            }
            return sb.ToString();
        }

        public BufferedReader(Stream stream, int capacity)
        {
            sr = new(stream);
            if (capacity > 0)
            {
                buffer = new char[capacity];
            }
            else
            {
                buffer = null;
            }
        }

        public bool EndOfStream { get => buffer == null ? sr.EndOfStream : Peek() == -1; }

        public T ReadInt<T>() where T : INumber<T>
        {
            char c;
            T res = default;
            T sign = T.CreateChecked(1);
            while (!EndOfStream && char.IsWhiteSpace((char)Peek())) Read();
            if (!EndOfStream && (char)Peek() == '-')
            {
                Read();
                sign = T.CreateChecked(-1);
            }
            while (!EndOfStream && char.IsDigit((char)Peek()))
            {
                c = (char)Read();
                res = res * T.CreateChecked(10) + T.CreateChecked(c - '0');
            }
            return res * sign;
        }

        public T[] ReadArray<T>(int count) where T : INumber<T> => ReadArray<T>(count, 0);
        public T[] ReadArray<T>(int count, int startIndex) where T : INumber<T>
        {
            T[] arr = new T[count + startIndex];
            for (int i = 0; i < count; ++i) arr[i + startIndex] = ReadInt<T>();
            return arr;
        }

        public int ReadInt32() => ReadInt<int>();
        public long ReadInt64() => ReadInt<long>();
        public int[] ReadInt32(int count) => ReadArray<int>(count);
        public long[] ReadInt64(int count) => ReadArray<long>(count);

        public double ReadDouble()
        {
            double res = ReadInt64();
            if ((char)Peek() == '.')
            {
                Read();
                double tail = 0.1;
                while (!EndOfStream && char.IsDigit((char)Peek()))
                {
                    char c = (char)Read();
                    res += (c - '0') * tail;
                    tail *= 0.1;
                }
            }
            return res;
        }
        public void Dispose()
        {
            sr.Close();
        }
    }
 
    internal class BufferedWriter : IDisposable {
        private StringBuilder sb = new();
        private StreamWriter sw;
        public BufferedWriter() : this(Console.OpenStandardOutput()) { }
        public BufferedWriter(Stream stream) { sw = new(stream); }
 
        public void Append(object val) => sb.AppendFormat("{0}", val);
 
        public void AppendLine(object val) => sb.AppendFormat("{0}\n", val);
 
        public void AppendYes(bool suc) => sb.AppendLine(suc ? "YES" : "NO");
 
        public void AppendJoin<T>(char delim, IEnumerable<T> values) => sb.AppendJoin(delim, values).AppendLine();
        public void AppendFormat(string format, params object[] args) => sb.AppendFormat(format, args);
        public void Output() {
            sw.Write(sb.ToString());
            sw.Flush();
            sb.Clear();
        }
        public void Dispose() {
            sw.Close();
        }
    }
    #endregion

    #region ArrayExt
    public static class ArrayExt
    {
        public static Span<T> AsSpan<T>(this T[,] array) => asSpan<T>(array);
        public static Span<T> AsSpan<T>(this T[,,] array) => asSpan<T>(array);
        static Span<T> asSpan<T>(Array array)
            => System.Runtime.InteropServices.MemoryMarshal.CreateSpan(
                ref System.Runtime.CompilerServices.Unsafe.As<byte, T>(
                    ref System.Runtime.InteropServices.MemoryMarshal.GetArrayDataReference(array)
                ), array.Length);
    }
    #endregion
}