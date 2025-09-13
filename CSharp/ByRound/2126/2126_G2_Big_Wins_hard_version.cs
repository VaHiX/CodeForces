using System.Numerics;
using System.Runtime.InteropServices.Marshalling;
using System.Text;

#if ONLINE_JUDGE
TemplateG2.SolutionG2 a = new();
a.Main();
#endif

namespace TemplateG2 { 
    internal class SolutionG2 {
        public void Solve() {
            int n = br.ReadInt32();
            int[] a = br.ReadInt32(n);
            DisjointSet l = new(n + 1), r = new(n + 1);
            int min = n, ans = 0;
            foreach (var i in Enumerable.Range(0, n).OrderByDescending(i => a[i]).ThenBy(i => i)) {
                for (int j = 0; j < 2; ++j) {
                    int x = l[i + 1];
                    if (x > 0) {
                        l.Merge(x, x - 1);
                        min = Math.Min(min, a[x - 1]);
                    }
                    x = r[i];
                    if (x < n) {
                        r.Merge(x, x + 1);
                        min = Math.Min(min, a[x]);
                    }
                }
                ans = Math.Max(ans, a[i] - min);
            }
            bw.AppendLine(ans);
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

    public class DisjointSet {
        private int n;
        private int[] fa;
        private void Update() {
            for (int i = 0; i < fa.Length; ++i) Find(i);
        }

        public DisjointSet(int n) {
            this.n = n;
            fa = Enumerable.Range(0, n).ToArray();
        }

        public int Find(int u) => fa[u] == u ? fa[u] : fa[u] = Find(fa[u]);
        public void Merge(int x, int y) {
            x = Find(x);
            y = Find(y);
            if (x != y) { fa[x] = y; --n; }
        }

        public int this[int u] { get => Find(u); }
        public int Count { get => n; }
        public int Size(int x) { Update(); return fa.Where(t => t == fa[x]).Count(); }
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