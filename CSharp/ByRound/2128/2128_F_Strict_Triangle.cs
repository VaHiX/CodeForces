using System.Numerics;
using System.Text;

#if ONLINE_JUDGE
TemplateF.SolutionF a = new();
a.Main();
#endif

namespace TemplateF { 
    internal class SolutionF {
        public void Solve() {
            int n = br.ReadInt32(), m = br.ReadInt32(), k = br.ReadInt32() - 1;
            Graph<long> GL = new(n, m << 1), GR = new(n, m << 1);
            for (int i = 0; i < m; ++i) {
                int u = br.ReadInt32() - 1, v = br.ReadInt32() - 1;
                int l = br.ReadInt32(), r = br.ReadInt32();
                GL.Add(u, v, l);
                GL.Add(v, u, l);
                GR.Add(u, v, r);
                GR.Add(v, u, r);
            }
            var dis1 = GR.Dijkstra(k);
            long[] dis2 = new long[n];
            PriorityQueue<int, long> q = new();
            bool[] vis = new bool[n];
            Array.Fill(dis2, long.MaxValue / 2);
            q.Enqueue(0, dis2[0] = -dis1[0]);
            while (q.Count > 0) {
                int u = q.Dequeue();
                if (vis[u]) continue;
                vis[u] = true;
                foreach (var e in GL[u]) {
                    int v = e.To;
                    long l = e.Weight;
                    long npy = Math.Max(dis2[u] + l, -dis1[v]);
                    if (npy < dis2[v] && npy < dis1[v]) {
                        q.Enqueue(v, dis2[v] = npy);
                    }
                }
            }
            bw.AppendYes(dis2[^1] < long.MaxValue / 2);
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
    public static class ShortestPath {
        public static bool SPFA(this Graph<long> G, long[] dis, int s) {
            int n = G.Count;
            bool[] vis = new bool[n];
            int[] cnt = new int[n];
            Array.Fill(dis, long.MaxValue / 2);
            dis[s] = 0;
            vis[s] = true;
            Queue<int> q = new();
            q.Enqueue(s);
            while (q.Count > 0) {
                int u = q.Dequeue();
                vis[u] = false;
                foreach (var e in G[u]) {
                    var (v, w) = (e.To, e.Weight);
                    if (dis[v] > dis[u] + w) {
                        dis[v] = dis[u] + w;
                        cnt[v] = cnt[u] + 1;
                        if (cnt[v] >= n) return false;
                        if (!vis[v]) {
                            q.Enqueue(v);
                            vis[v] = true;
                        }
                    }
                }
            }
            return true;
        }

        public static long[] Dijkstra(this Graph<long> G, int s) {
            int n = G.Count;
            bool[] vis = new bool[n];
            long[] dis = new long[n];
            Array.Fill(dis, long.MaxValue / 2);
            dis[s] = 0;
            PriorityQueue<int, long> q = new();
            q.Enqueue(s, dis[s]);
            while (q.Count > 0) {
                var u = q.Dequeue();
                if (vis[u]) continue;
                vis[u] = true;
                foreach (var e in G[u]) {
                    var (v, w) = (e.To, e.Weight);
                    if (dis[v] > dis[u] + w) {
                        dis[v] = dis[u] + w;
                        q.Enqueue(v, dis[v]);
                    }
                }
            }
            return dis;
        }

        public static long[,] Floyd(this Graph<long> G) {
            int n = G.Count;
            long[,] f = new long[n, n];
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i == j) continue;
                    f[i, j] = long.MaxValue / 2;
                }
                foreach (var e in G[i]) {
                    var (v, w) = (e.To, e.Weight);
                    f[i, v] = w;
                }
            }
            for (int k = 0; k < n; ++k) {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        f[i, j] = Math.Min(f[i, j], f[i, k] + f[k, j]);
                    }
                }
            }
            return f;
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