using CodeforcesRound743.Problems;
using System;
using System.Buffers;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Runtime.Intrinsics.X86;
using System.Text;

namespace CodeforcesRound743.Problems
{
    public class ProblemA : ProblemBase
    {
        public ProblemA() : base(true) { }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        protected override void SolveEach(IOManager io)
        {
            var n = io.ReadInt();
            var graph = Enumerable.Repeat(0, n).Select(_ => new List<int>()).ToArray();

            var currentQueue = new PriorityQueue<int>(PriorityQueue<int>.Order.Ascending);
            var nextQueue = new PriorityQueue<int>(PriorityQueue<int>.Order.Ascending);
            var read = 0;
            var toRead = new int[n];

            for (int i = 0; i < n; i++)
            {
                var count = io.ReadInt();
                toRead[i] = count;

                if (count == 0)
                {
                    currentQueue.Enqueue(i);
                }

                for (int j = 0; j < count; j++)
                {
                    var v = io.ReadInt();
                    v--;
                    graph[v].Add(i);
                }
            }

            for (int i = 1; true; i++)
            {
                if (currentQueue.Count == 0)
                {
                    io.WriteLine(-1);
                    return;
                }

                while (currentQueue.Count > 0)
                {
                    var v = currentQueue.Dequeue();
                    read++;

                    if (read == n)
                    {
                        io.WriteLine(i);
                        return;
                    }

                    foreach (var next in graph[v].AsSpan())
                    {
                        toRead[next]--;

                        if (toRead[next] == 0)
                        {
                            if (next < v)
                            {
                                nextQueue.Enqueue(next);
                            }
                            else
                            {
                                currentQueue.Enqueue(next);
                            }
                        }
                    }
                }

                (currentQueue, nextQueue) = (nextQueue, currentQueue);
            }
        }

        public class PriorityQueue<T> : IEnumerable<T> where T : IComparable<T>
        {
            const int InitialSize = 4;
            private readonly int _reverseFactor;
            private T[] _heap;
            public int Count { get; private set; }
            public bool IsDescending => _reverseFactor == 1;

            public PriorityQueue(Order order)
            {
                _reverseFactor = order == Order.Ascending ? -1 : 1;
                _heap = new T[InitialSize];
                Count = 0;
            }

            public PriorityQueue(Order order, IEnumerable<T> collection) : this(order)
            {
                foreach (var item in collection)
                {
                    Enqueue(item);
                }
            }

            public void Enqueue(T item)
            {
                if (Count >= _heap.Length)
                {
                    var temp = new T[_heap.Length << 1];
                    _heap.AsSpan().CopyTo(temp);
                    _heap = temp;
                }

                var index = Count++;
                ref var child = ref _heap[index];
                child = item;

                while (index > 0)
                {
                    index = (index - 1) >> 1;
                    ref var parent = ref _heap[index];

                    if (Compare(child, parent) <= 0)
                    {
                        break;
                    }

                    Swap(ref child, ref parent);
                    child = ref parent;
                }
            }

            public T Dequeue()
            {
                var index = 0;
                ref var parent = ref _heap[index];
                var item = parent;
                parent = _heap[--Count];
                var span = _heap.AsSpan(0, Count);

                while (true)
                {
                    index = (index << 1) + 1;

                    if (unchecked((uint)index < (uint)span.Length))
                    {
                        ref var child = ref span[index];
                        var r = index + 1;

                        if (unchecked((uint)r < (uint)span.Length))
                        {
                            ref var brother = ref span[r];
                            if (Compare(child, brother) < 0)
                            {
                                child = ref brother;
                                index = r;
                            }
                        }

                        if (Compare(parent, child) < 0)
                        {
                            Swap(ref parent, ref child);
                            parent = ref child;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }

                return item;
            }

            public T Peek() => _heap[0];

            public void Clear() => Count = 0;

            private int Compare(T a, T b) => _reverseFactor * a.CompareTo(b);

            private void Swap(ref T a, ref T b)
            {
                var temp = a;
                a = b;
                b = temp;
            }

            public IEnumerator<T> GetEnumerator()
            {
                var copy = new T[_heap.Length];
                var cnt = Count;
                _heap.AsSpan().CopyTo(copy);

                try
                {
                    while (Count > 0)
                    {
                        yield return Dequeue();
                    }
                }
                finally
                {
                    _heap = copy;
                    Count = cnt;
                }
            }

            System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() => GetEnumerator();

            public enum Order
            {
                Ascending,
                Descending
            }
        }

    }
}

namespace CodeforcesRound743
{
    class Program
    {
        static void Main(string[] args)
        {
            IProblem question = new ProblemA();
            using var io = new IOManager(Console.OpenStandardInput(), Console.OpenStandardOutput());
            question.Solve(io);
        }
    }
}

#region Base Class

namespace CodeforcesRound743.Problems
{
    public interface IProblem
    {
        string Solve(string input);
        void Solve(IOManager io);
    }

    public abstract class ProblemBase : IProblem
    {
        protected bool HasMultiTestCases { get; }

        protected ProblemBase(bool hasMultiTestCases) => HasMultiTestCases = hasMultiTestCases;

        public string Solve(string input)
        {
            var inputStream = new MemoryStream(Encoding.UTF8.GetBytes(input));
            var outputStream = new MemoryStream();
            using var manager = new IOManager(inputStream, outputStream);

            Solve(manager);
            manager.Flush();

            outputStream.Seek(0, SeekOrigin.Begin);
            var reader = new StreamReader(outputStream);
            return reader.ReadToEnd();
        }

        public void Solve(IOManager io)
        {
            var tests = HasMultiTestCases ? io.ReadInt() : 1;

            for (var t = 0; t < tests; t++)
            {
                SolveEach(io);
            }
        }

        protected abstract void SolveEach(IOManager io);
    }
}

#endregion

#region Utils

namespace CodeforcesRound743
{
    public class IOManager : IDisposable
    {
        private readonly BinaryReader _reader;
        private readonly StreamWriter _writer;
        private bool _disposedValue;
        private byte[] _buffer = new byte[1024];
        private int _length;
        private int _cursor;
        private bool _eof;

        const char ValidFirstChar = '!';
        const char ValidLastChar = '~';

        public IOManager(Stream input, Stream output)
        {
            _reader = new BinaryReader(input);
            _writer = new StreamWriter(output) { AutoFlush = false };
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private char ReadAscii()
        {
            if (_cursor == _length)
            {
                _cursor = 0;
                _length = _reader.Read(_buffer);

                if (_length == 0)
                {
                    if (!_eof)
                    {
                        _eof = true;
                        return char.MinValue;
                    }
                    else
                    {
                        ThrowEndOfStreamException();
                    }
                }
            }

            return (char)_buffer[_cursor++];
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public char ReadChar()
        {
            char c;
            while (!IsValidChar(c = ReadAscii())) { }
            return c;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public string ReadString()
        {
            var builder = new StringBuilder();
            char c;
            while (!IsValidChar(c = ReadAscii())) { }

            do
            {
                builder.Append(c);
            } while (IsValidChar(c = ReadAscii()));

            return builder.ToString();
        }

        public int ReadInt() => (int)ReadLong();

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public long ReadLong()
        {
            long result = 0;
            bool isPositive = true;
            char c;

            while (!IsNumericChar(c = ReadAscii())) { }

            if (c == '-')
            {
                isPositive = false;
                c = ReadAscii();
            }

            do
            {
                result *= 10;
                result += c - '0';
            } while (IsNumericChar(c = ReadAscii()));

            return isPositive ? result : -result;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private Span<char> ReadChunk(Span<char> span)
        {
            var i = 0;
            char c;
            while (!IsValidChar(c = ReadAscii())) { }

            do
            {
                span[i++] = c;
            } while (IsValidChar(c = ReadAscii()));

            return span.Slice(0, i);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public double ReadDouble() => double.Parse(ReadChunk(stackalloc char[32]));

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public decimal ReadDecimal() => decimal.Parse(ReadChunk(stackalloc char[32]));

        public int[] ReadIntArray(int n)
        {
            var a = new int[n];
            for (int i = 0; i < a.Length; i++)
            {
                a[i] = ReadInt();
            }
            return a;
        }

        public long[] ReadLongArray(int n)
        {
            var a = new long[n];
            for (int i = 0; i < a.Length; i++)
            {
                a[i] = ReadLong();
            }
            return a;
        }

        public double[] ReadDoubleArray(int n)
        {
            var a = new double[n];
            for (int i = 0; i < a.Length; i++)
            {
                a[i] = ReadDouble();
            }
            return a;
        }

        public decimal[] ReadDecimalArray(int n)
        {
            var a = new decimal[n];
            for (int i = 0; i < a.Length; i++)
            {
                a[i] = ReadDecimal();
            }
            return a;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Write<T>(T value) => _writer.Write(value.ToString());

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void WriteLine<T>(T value) => _writer.WriteLine(value.ToString());

        public void WriteLine<T>(IEnumerable<T> values, char separator)
        {
            var e = values.GetEnumerator();
            if (e.MoveNext())
            {
                _writer.Write(e.Current.ToString());

                while (e.MoveNext())
                {
                    _writer.Write(separator);
                    _writer.Write(e.Current.ToString());
                }
            }

            _writer.WriteLine();
        }

        public void WriteLine<T>(T[] values, char separator) => WriteLine((ReadOnlySpan<T>)values, separator);
        public void WriteLine<T>(Span<T> values, char separator) => WriteLine((ReadOnlySpan<T>)values, separator);

        public void WriteLine<T>(ReadOnlySpan<T> values, char separator)
        {
            for (int i = 0; i < values.Length - 1; i++)
            {
                _writer.Write(values[i]);
                _writer.Write(separator);
            }

            if (values.Length > 0)
            {
                _writer.Write(values[^1]);
            }

            _writer.WriteLine();
        }

        public void Flush() => _writer.Flush();

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static bool IsValidChar(char c) => ValidFirstChar <= c && c <= ValidLastChar;

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static bool IsNumericChar(char c) => ('0' <= c && c <= '9') || c == '-';

        private void ThrowEndOfStreamException() => throw new EndOfStreamException();

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposedValue)
            {
                if (disposing)
                {
                    _reader.Dispose();
                    _writer.Flush();
                    _writer.Dispose();
                }

                _disposedValue = true;
            }
        }

        public void Dispose()
        {
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }
    }

    public static class UtilExtensions
    {
        public static bool ChangeMax<T>(ref this T value, T other) where T : struct, IComparable<T>
        {
            if (value.CompareTo(other) < 0)
            {
                value = other;
                return true;
            }
            return false;
        }

        public static bool ChangeMin<T>(ref this T value, T other) where T : struct, IComparable<T>
        {
            if (value.CompareTo(other) > 0)
            {
                value = other;
                return true;
            }
            return false;
        }

        public static void SwapIfLargerThan<T>(ref this T a, ref T b) where T : struct, IComparable<T>
        {
            if (a.CompareTo(b) > 0)
            {
                (a, b) = (b, a);
            }
        }

        public static void SwapIfSmallerThan<T>(ref this T a, ref T b) where T : struct, IComparable<T>
        {
            if (a.CompareTo(b) < 0)
            {
                (a, b) = (b, a);
            }
        }

        public static void Sort<T>(this T[] array) where T : IComparable<T> => Array.Sort(array);
        public static void Sort<T>(this T[] array, Comparison<T> comparison) => Array.Sort(array, comparison);
    }

    public static class CollectionExtensions
    {
        private class ArrayWrapper<T>
        {
#pragma warning disable CS0649
            public T[] Array;
#pragma warning restore CS0649
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Span<T> AsSpan<T>(this List<T> list)
        {
            return Unsafe.As<ArrayWrapper<T>>(list).Array.AsSpan(0, list.Count);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Span<T> GetRowSpan<T>(this T[,] array, int i)
        {
            var width = array.GetLength(1);
            return MemoryMarshal.CreateSpan(ref array[i, 0], width);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Span<T> GetRowSpan<T>(this T[,,] array, int i, int j)
        {
            var width = array.GetLength(2);
            return MemoryMarshal.CreateSpan(ref array[i, j, 0], width);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Span<T> GetRowSpan<T>(this T[,,,] array, int i, int j, int k)
        {
            var width = array.GetLength(3);
            return MemoryMarshal.CreateSpan(ref array[i, j, k, 0], width);
        }

        public static void Fill<T>(this T[] array, T value) => array.AsSpan().Fill(value);
        public static void Fill<T>(this T[,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0], array.Length).Fill(value);
        public static void Fill<T>(this T[,,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0, 0], array.Length).Fill(value);
        public static void Fill<T>(this T[,,,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0, 0, 0], array.Length).Fill(value);
    }

    public static class SearchExtensions
    {
        struct LowerBoundComparer<T> : IComparer<T> where T : IComparable<T>
        {
            public int Compare(T x, T y) => 0 <= x.CompareTo(y) ? 1 : -1;
        }

        struct UpperBoundComparer<T> : IComparer<T> where T : IComparable<T>
        {
            public int Compare(T x, T y) => 0 < x.CompareTo(y) ? 1 : -1;
        }

        // https://trsing.hatenablog.com/entry/2019/08/27/211038
        public static int GetGreaterEqualIndex<T>(this ReadOnlySpan<T> span, T inclusiveMin) where T : IComparable<T> => ~span.BinarySearch(inclusiveMin, new UpperBoundComparer<T>());
        public static int GetGreaterThanIndex<T>(this ReadOnlySpan<T> span, T exclusiveMin) where T : IComparable<T> => ~span.BinarySearch(exclusiveMin, new LowerBoundComparer<T>());
        public static int GetLessEqualIndex<T>(this ReadOnlySpan<T> span, T inclusiveMax) where T : IComparable<T> => ~span.BinarySearch(inclusiveMax, new LowerBoundComparer<T>()) - 1;
        public static int GetLessThanIndex<T>(this ReadOnlySpan<T> span, T exclusiveMax) where T : IComparable<T> => ~span.BinarySearch(exclusiveMax, new UpperBoundComparer<T>()) - 1;
        public static int GetGreaterEqualIndex<T>(this Span<T> span, T inclusiveMin) where T : IComparable<T> => ((ReadOnlySpan<T>)span).GetGreaterEqualIndex(inclusiveMin);
        public static int GetGreaterThanIndex<T>(this Span<T> span, T exclusiveMin) where T : IComparable<T> => ((ReadOnlySpan<T>)span).GetGreaterThanIndex(exclusiveMin);
        public static int GetLessEqualIndex<T>(this Span<T> span, T inclusiveMax) where T : IComparable<T> => ((ReadOnlySpan<T>)span).GetLessEqualIndex(inclusiveMax);
        public static int GetLessThanIndex<T>(this Span<T> span, T exclusiveMax) where T : IComparable<T> => ((ReadOnlySpan<T>)span).GetLessThanIndex(exclusiveMax);

        public static int BoundaryBinarySearch(Predicate<int> predicate, int ok, int ng)
        {
            while (Math.Abs(ok - ng) > 1)
            {
                var mid = (ok + ng) / 2;
                if (predicate(mid))
                {
                    ok = mid;
                }
                else
                {
                    ng = mid;
                }
            }
            return ok;
        }

        public static long BoundaryBinarySearch(Predicate<long> predicate, long ok, long ng)
        {
            while (Math.Abs(ok - ng) > 1)
            {
                var mid = (ok + ng) / 2;
                if (predicate(mid))
                {
                    ok = mid;
                }
                else
                {
                    ng = mid;
                }
            }
            return ok;
        }

        public static BigInteger BoundaryBinarySearch(Predicate<BigInteger> predicate, BigInteger ok, BigInteger ng)
        {
            while (BigInteger.Abs(ok - ng) > 1)
            {
                var mid = (ok + ng) / 2;
                if (predicate(mid))
                {
                    ok = mid;
                }
                else
                {
                    ng = mid;
                }
            }
            return ok;
        }

        public static double BoundaryBinarySearch(Predicate<double> predicate, double ok, double ng, double eps = 1e-9, int loopLimit = 1000)
        {
            var count = 0;

            while (Math.Abs(ok - ng) > eps && count++ < loopLimit)
            {
                var mid = (ok + ng) * 0.5;
                if (predicate(mid))
                {
                    ok = mid;
                }
                else
                {
                    ng = mid;
                }
            }

            return (ok + ng) * 0.5;
        }

        public static double Bisection(Func<double, double> f, double a, double b, double eps = 1e-9, int loopLimit = 100)
        {
            double mid = (a + b) / 2;
            var fa = f(a);

            if (fa * f(b) >= 0)
            {
                throw new ArgumentException("f(a)とf(b)は異符号である必要があります。");
            }

            for (int i = 0; i < loopLimit; i++)
            {
                var fmid = f(mid);
                var sign = fa * fmid;

                if (sign < 0)
                {
                    b = mid;
                }
                else if (sign > 0)
                {
                    a = mid;
                    fa = fmid;
                }
                else
                {
                    return mid;
                }

                mid = (a + b) / 2;

                if (Math.Abs(b - a) < eps)
                {
                    break;
                }
            }
            return mid;
        }
    }
}

#endregion
