using System;
using System.Buffers;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Runtime.Intrinsics.X86;
using CodeforcesRound596Div1.Questions;

namespace CodeforcesRound596Div1.Questions
{
    public class QuestionA : AtCoderQuestionBase
    {
        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        public override void Solve(IOManager io)
        {
            var n = io.ReadInt();
            var p = io.ReadInt();

            for (int i = 1; i <= 1000000; i++)
            {
                n -= p;
                if (n <= 0)
                {
                    break;
                }
                else
                {
                    var count = 0;
                    var popcnt = 0;
                    var current = n;
                    for (int shift = 0; shift < 32; shift++)
                    {
                        if (((current >> shift) & 1) > 0)
                        {
                            count += 1 << shift;
                            popcnt++;
                        }
                    }

                    if (popcnt <= i && i <= count)
                    {
                        io.WriteLine(i);
                        return;
                    }
                }
            }

            io.WriteLine(-1);
        }
    }
}

namespace CodeforcesRound596Div1
{
    class Program
    {
        static void Main(string[] args)
        {
            IAtCoderQuestion question = new QuestionA();
            using var io = new IOManager(Console.OpenStandardInput(), Console.OpenStandardOutput());
            question.Solve(io);
        }
    }
}

#region Base Class

namespace CodeforcesRound596Div1.Questions
{
    public interface IAtCoderQuestion
    {
        string Solve(string input);
        void Solve(IOManager io);
    }

    public abstract class AtCoderQuestionBase : IAtCoderQuestion
    {
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

        public abstract void Solve(IOManager io);
    }
}

#endregion

#region Utils

namespace CodeforcesRound596Div1
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

        public static void Fill<T>(this T[] array, T value) => array.AsSpan().Fill(value);
        public static void Fill<T>(this T[,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0], array.Length).Fill(value);
        public static void Fill<T>(this T[,,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0, 0], array.Length).Fill(value);
        public static void Fill<T>(this T[,,,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0, 0, 0], array.Length).Fill(value);
    }
}

#endregion
