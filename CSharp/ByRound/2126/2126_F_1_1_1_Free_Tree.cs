using System.Numerics;
using System.Text;

#if ONLINE_JUDGE
TemplateF.SolutionF a = new();
a.Main();
#endif

namespace TemplateF { 
    internal class SolutionF {
        public void Solve() {
            int n = br.ReadInt32(), q = br.ReadInt32();
            int[] a = br.ReadArray<int>(n, 1);
            int[] fa = new int[n + 1], fb = new int[n + 1];
            long sum = 0;
            SortedDictionary<int, long>[] mp = new SortedDictionary<int, long>[n + 1];
            for (int i = 0; i <= n; ++i) mp[i] = new();
            Graph<int> G = new(n + 1, n << 1);
            for (int i = 1; i < n; ++i) {
                int u = br.ReadInt32(), v = br.ReadInt32(), w = br.ReadInt32();
                G.Add(u, v, w);
                G.Add(v, u, w);
            }
            mp[0].Add(a[1], 0);
            dfs(1);
            while (q-- > 0) {
                int u = br.ReadInt32(), x = br.ReadInt32();
                if (a[u] != a[fa[u]]) sum -= fb[u];
                if (mp[u].TryGetValue(a[u], out var y)) sum += y;
                Dec(mp[fa[u]], a[u], fb[u]);
                a[u] = x;
                if (a[u] != a[fa[u]]) sum += fb[u];
                if (mp[u].TryGetValue(a[u], out y)) sum -= y;
                Inc(mp[fa[u]], a[u], fb[u]);
                bw.AppendLine(sum);
            }

            void dfs(int u) {
                foreach (var e in G[u]) {
                    int v = e.To, w = e.Weight;
                    if (v == fa[u]) continue;
                    fa[v] = u;
                    fb[v] = w;
                    Inc(mp[u], a[v], w);
                    if (a[u] != a[v]) sum += w;
                    dfs(v);
                }
            }
        }
        static void Inc<T>(IDictionary<T, long> mp, T key, int value) {
            if (mp.TryGetValue(key, out var v)) mp[key] = v + value;
            else mp.Add(key, value);
        }

        static void Dec<T>(IDictionary<T, long> mp, T key, int value) {
            if ((mp[key] -= value) == 0) mp.Remove(key);
        }
        private readonly BufferedReader br = new(Console.OpenStandardInput(), 1 << 16);
        private readonly BufferedWriter bw = new();
        public void Main() {
            int T = 1;
            T = br.ReadInt32();
            while (T-- > 0) {
                Solve();
            }
            bw.Output();
        }
    }
    public class Edge<T> {
        public int To { get; set; }
        public T Weight { get; set; }
        public int Next { get; set; }
    }

    public class Graph<T> {
        protected Edge<T>[] e;
        protected int[] head;
        protected int cnt, n;
        public Graph(int n, int m) {
            head = new int[n];
            Array.Fill(head, -1);
            e = new Edge<T>[m];
            cnt = -1;
            this.n = n;
        }

        public void Add(int u, int v) => Add(u, v, default(T));
        public void Add(int u, int v, T w) {
            e[++cnt] = new Edge<T> { To = v, Weight = w, Next = head[u] };
            head[u] = cnt;
        }

        public IEnumerable<Edge<T>> this[int u] {
            get {
                for (int v = head[u]; v >= 0; v = e[v].Next) yield return e[v];
            }
        }

        public int Count { get => n; }
    }
    internal class BufferedReader : IDisposable {
        private StreamReader sr;
        private char[] buffer;
        private int S = 0, T = 0;

        private int Peek() {
            if (buffer == null) {
                return sr.Peek();
            }
            if (S == T) {
                T = sr.ReadBlock(buffer.AsSpan());
                if (T == 0) return -1;
                S = 0;
            }
            return buffer[S];
        }

        private int Read() {
            if (buffer == null) {
                return sr.Read();
            }
            int p = Peek();
            if (p >= 0) ++S;
            return p;
        }

        public string ReadLine() {
            int c;
            StringBuilder sb = new();
            while ((c = Read()) != -1) {
                if (c == '\r') continue; // omit '\r'
                if (c == '\n') {
                    if (sb.Length > 0) break;
                    else continue; // omit empty lines
                }
                sb.Append((char)c);
            }
            return sb.ToString();
        }

        public BufferedReader(Stream stream, int capacity) {
            sr = new(stream);
            if (capacity > 0) {
                buffer = new char[capacity];
            } else {
                buffer = null;
            }
        }

        public bool EndOfStream { get => buffer == null ? sr.EndOfStream : Peek() == -1; }

        public T ReadInt<T>() where T: INumber<T> {
            char c;
            T res = default;
            T sign = T.CreateChecked(1);
            while (!EndOfStream && char.IsWhiteSpace((char)Peek())) Read();
            if (!EndOfStream && (char)Peek() == '-') {
                Read();
                sign = T.CreateChecked(-1);
            }
            while (!EndOfStream && char.IsDigit((char)Peek())) {
                c = (char)Read();
                res = res * T.CreateChecked(10) + T.CreateChecked(c - '0');
            }
            return res * sign;
        }

        public T[] ReadArray<T>(int count) where T: INumber<T> => ReadArray<T>(count, 0);
        public T[] ReadArray<T>(int count, int startIndex) where T: INumber<T> {
            T[] arr = new T[count + startIndex];
            for (int i = 0; i < count; ++i) arr[i + startIndex] = ReadInt<T>();
            return arr;
        }

        public int ReadInt32() => ReadInt<int>();
        public long ReadInt64() => ReadInt<long>();
        public int[] ReadInt32(int count) => ReadArray<int>(count);
        public long[] ReadInt64(int count) => ReadArray<long>(count);

        public double ReadDouble() {
            double res = ReadInt64();
            if ((char)Peek() == '.') {
                Read();
                double tail = 0.1;
                while (!EndOfStream && char.IsDigit((char)Peek())) {
                    char c = (char)Read();
                    res += (c - '0') * tail;
                    tail *= 0.1;
                }
            }
            return res;
        }
        public void Dispose() {
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

        public void AppendJoin<T>(IEnumerable<T> values) => sb.AppendJoin(' ', values).AppendLine();
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
}