using System.Numerics;
using System.Text;
using System.Diagnostics;

using i64 = System.Int64;
using i128 = System.Int128;

Template.Snippet a = new();
a.Main();

namespace Template
{   
    internal class Snippet
    {
        public void Solve()
        {
            int x = br.ReadInt32();
            i64 m = br.ReadInt64();

            int B = BitOperations.Log2((uint)x) + 1;
            int msk = (1 << B) - 1;

            i64 ans = 0;
            for (int y = 1; y <= Math.Min(msk, m); ++y)
            {
                if ((x ^ y) % x == 0 || (x ^ y) % y == 0)
                {
                    ++ans;
                }
            }

            if (m > msk)
            {
                /*
                    if x^y | y, then y * 2 <= x^y, out of question
                    so x^y | x
                    x^y = kx
                    y = kx^x <= m
                    kx <= m|msk
                    k <= (m|msk)/x
                */
                for (i64 k = (m | msk) / x; k > 1; --k)
                {
                    i64 y = (k * x) ^ x;
                    if ((y >> B) < (m >> B))
                    {
                        ans += k - 1;
                        break;
                    }
                    if (y <= m)
                    {
                        ++ans;
                    }
                }
            } 

            bw.AppendLine(ans);
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

        private string readLine(bool skipSpace)
        {
            int c;
            StringBuilder sb = new();
            while ((c = Read()) != -1)
            {
                if (c == '\r') continue; // omit '\r'
                if (c == ' ' && skipSpace) break;
                if (c == '\n')
                {
                    if (sb.Length > 0) break;
                    else continue; // omit empty lines
                }
                sb.Append((char)c);
            }
            return sb.ToString();
        }

        public string ReadString() => readLine(true);
        public string ReadLine() => readLine(false);

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
        public static int lower_bound<T>(this IList<T> a, T M) where T : IComparable<T>
        => lower_bound<T>(a, 0, a.Count, M);
        public static int lower_bound<T>(this IList<T> a, int lo, int hi, T M) where T : IComparable<T>
        {
            while (lo < hi)
            {
                int x = (lo + hi) / 2;
                if (a[x].CompareTo(M) >= 0)
                {
                    hi = x;
                }
                else
                {
                    lo = x + 1;
                }
            }
            return hi;
        }
        public static int upper_bound<T>(this IList<T> a, T M) where T : IComparable<T>
        => upper_bound<T>(a, 0, a.Count, M);
        public static int upper_bound<T>(this IList<T> a, int lo, int hi, T M) where T : IComparable<T>
        {
            while (lo < hi)
            {
                int x = (lo + hi) / 2;
                if (a[x].CompareTo(M) > 0)
                {
                    hi = x;
                }
                else
                {
                    lo = x + 1;
                }
            }
            return hi;
        }
    }
    #endregion
}