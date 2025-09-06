#define active

using System.Numerics;
using System.Text;

namespace cf
{
    class TemplateA
    {
        private readonly BufferedReader br = new(Console.OpenStandardInput(), 1 << 16);
        private readonly BufferedWriter bw = new();

        void Solve()
        {
            var y = br.ReadInt32(6);
            (int l, int b) r1 = (y[0], y[1]);
            (int l, int b) r2 = (y[2], y[3]);
            (int l, int b) r3 = (y[4], y[5]);

            if ((r1.l == r2.l && r1.l == r3.l) && (r1.l == r1.b + r2.b + r3.b)) bw.AppendYes(true);
            else if ((r1.b == r2.b && r1.b == r3.b) && (r1.b == r1.l + r2.l + r3.l)) bw.AppendYes(true);
            else if ((r2.l == r3.l && r2.b + r3.b == r1.b) && (r1.l + r2.l == r1.b)) bw.AppendYes(true);
            else if ((r2.b == r3.b && r2.l + r3.l == r1.l) && (r1.b + r2.b == r1.l)) bw.AppendYes(true);
            else bw.AppendYes(false);
        }
#if active

        public static void Main()
        {
            var solution = new TemplateA();
            solution.Run();
        }

        void Run()
        {
            // a-z 97-122 | A-Z 65-90 || +32 diff
            int t = 1;
            t = br.ReadInt32();
            while (t-- > 0) Solve();
            bw.Output();
        }
#endif

        internal class BufferedReader : IDisposable
        {
            private StreamReader sr;
            private char[] buffer;
            private int S = 0, T = 0;

            private int Peek()
            {
                if (buffer == null) return sr.Peek();
                if (S == T)
                {
                    if (T == 0 || !sr.BaseStream.CanSeek)
                    {
                        T = sr.Read(buffer, 0, Math.Min(buffer.Length, 1024));
                    }
                    else
                    {
                        T = sr.ReadBlock(buffer.AsSpan());
                    }

                    if (T == 0) return -1;
                    S = 0;
                }
                return buffer[S];
            }
            private int Read()
            {
                if (buffer == null) return sr.Read();
                int p = Peek();
                if (p >= 0) ++S;
                return p;
            }
            public string ReadLine()
            {
                int c;
                StringBuilder sb = new();
                while ((c = Read()) != -1)
                {
                    if (c == '\r') continue;
                    if (c == '\n')
                    {
                        if (sb.Length > 0) break;
                        else continue;
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
                    buffer = null!;
                }
            }
            public bool EndOfStream { get => buffer == null ? sr.EndOfStream : Peek() == -1; }
            public T ReadInt<T>() where T : INumber<T>
            {
                char c;
                T res = default!;
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

        internal class BufferedWriter : IDisposable
        {
            private StringBuilder sb = new();
            private StreamWriter sw;
            public BufferedWriter() : this(Console.OpenStandardOutput()) { }
            public BufferedWriter(Stream stream) { sw = new(stream); }
            public void Append(object val) => sb.AppendFormat("{0}", val);
            public void AppendLine(object val) => sb.AppendFormat("{0}\n", val);
            public void AppendYes(bool suc) => sb.AppendLine(suc ? "YES" : "NO");
            public void AppendJoin<T>(IEnumerable<T> values) => sb.AppendJoin(' ', values).AppendLine();
            public void AppendFormat(string format, params object[] args) => sb.AppendFormat(format, args);
            public void Output()
            {
                sw.Write(sb.ToString());
                sw.Flush();
                sb.Clear();
            }
            public void Dispose()
            {
                sw.Close();
            }
        }
    }
}