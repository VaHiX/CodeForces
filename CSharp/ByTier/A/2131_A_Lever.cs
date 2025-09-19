using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Numerics;

namespace CodeForces.Problems.Round2131.A
{
    /// <summary>
    /// Problem: CF2131A - Lever
    /// 
    /// This program solves a problem where we need to determine the minimum number of operations
    /// required to balance two arrays by transferring values between them, where each operation
    /// can move a unit from one array to another.
    /// 
    /// Approach:
    /// 1. Calculate the total excess in array 'a' (elements greater than corresponding in 'b')
    /// 2. Calculate the total deficit in array 'a' (elements less than corresponding in 'b')
    /// 3. The answer is the minimum number of operations needed to balance the arrays
    /// 
    /// Time Complexity: O(n) where n is the length of the arrays
    /// Space Complexity: O(1) additional space
    /// </summary>

    #region Вспомогательные штуки
    /// <summary>
    /// Custom comparer that uses a delegate for comparison
    /// </summary>
    public class CustomComparer<T> : IComparer<T>
    {
        private readonly Func<T?, T?, int> _compareFunc;

        public CustomComparer(Func<T?, T?, int> compareFunc) =>
            _compareFunc = compareFunc;

        public int Compare(T? x, T? y) => _compareFunc(x, y);
    }

    /// <summary>
    /// Extension methods for mathematical operations
    /// </summary>
    public static class MathExtensions
    {
        /// <summary>
        /// Performs ceiling division of two numbers
        /// </summary>
        public static T CeilingDivide<T>(this T dividend, T divisor) where T : INumber<T>
        {
            return (dividend + divisor - T.One) / divisor;
        }

        /// <summary>
        /// Calculates the greatest common divisor of two numbers
        /// </summary>
        public static T GreatestCommonDivisor<T>(this T a, T b) where T : INumber<T>
        {
            while (!T.IsZero(a) && !T.IsZero(b))
            {
                a = T.Abs(a);
                b = T.Abs(b);
                if (a > b)
                    a %= b;
                else
                    b %= a;
            }
            return T.IsZero(a) ? b : a;
        }

        /// <summary>
        /// Calculates the greatest common divisor of a collection of numbers
        /// </summary>
        public static T GreatestCommonDivisor<T>(this IReadOnlyList<T> numbers) where T : INumber<T>
        {
            T gcd = numbers[0];
            for (int i = 1; i < numbers.Count; i++)
            {
                gcd = gcd.GreatestCommonDivisor(numbers[i]);
            }

            return gcd;
        }

        /// <summary>
        /// Calculates the least common multiple of two numbers
        /// </summary>
        public static T LeastCommonMultiple<T>(this T a, T b) where T : INumber<T>
        {
            return a / GreatestCommonDivisor(a, b) * b;
        }

        /// <summary>
        /// Calculates the binary power of a number
        /// </summary>
        public static T BinaryPower<T>(this T x, T pow) where T : INumber<T>, IBinaryInteger<T>
        {
            T ret = T.One;

            pow = T.Abs(pow);
            while (pow != T.Zero)
            {
                if ((pow & T.One) == T.One)
                    ret *= x;
                x *= x;
                pow >>= 1;
            }
            return ret;
        }

        /// <summary>
        /// Calculates the binary power of a number modulo another number
        /// </summary>
        public static T BinaryPowerModulo<T>(this T x, T pow, T mod) where T : INumber<T>, IBinaryInteger<T>
        {
            T ret = T.One;
            x %= mod;

            pow = T.Abs(pow);
            while (pow != T.Zero)
            {
                if ((pow & T.One) == T.One)
                {
                    ret *= x;
                    ret %= mod;
                }

                x *= x;
                x %= mod;
                pow >>= 1;
            }
            return ret;
        }

        /// <summary>
        /// Gets the maximum bit of a number
        /// </summary>
        public static T GetMaxBit<T>(this T num) where T : INumber<T>, IBinaryInteger<T>
        {
            int res = int.CreateChecked(T.Log2(num));
            return T.One << res;
        }

        /// <summary>
        /// Gets the digits of a number
        /// </summary>
        public static IReadOnlyList<T> GetDigits<T>(this T num) where T : INumber<T>
        {
            List<T> ret = new List<T>(18);
            T ten = T.CreateChecked(10);

            while (num != T.Zero)
            {
                ret.Add(num % ten);
                num /= ten;
            }

            return ret;
        }
    }

    /// <summary>
    /// Extension methods for collections
    /// </summary>
    public static class CollectionExtensions
    {
        /// <summary>
        /// Finds the minimum and maximum indices of a collection
        /// </summary>
        public static (T, int, T, int) MinIndexMaxIndex<T>(this IReadOnlyList<T> collection) where T : INumber<T>
        {
            int minIndex = 0, maxIndex = 0;
            for (int i = 1; i < collection.Count; i++)
            {
                if (collection[i] < collection[minIndex])
                    minIndex = i;
                if (collection[i] > collection[maxIndex])
                    maxIndex = i;
            }

            return (collection[minIndex], minIndex, collection[maxIndex], maxIndex);
        }

        /// <summary>
        /// Finds the lower bound index of a collection
        /// </summary>
        public static int LowerBoundIndex<T>(this IReadOnlyList<T> collection, T value) where T : INumber<T>
        {
            int left = -1, right = collection.Count;
            while (right - left > 1)
            {
                int mid = (left + right) >> 1;
                if (collection[mid] < value)
                    left = mid;
                else
                    right = mid;
            }

            return right;
        }

        /// <summary>
        /// Finds the upper bound index of a collection
        /// </summary>
        public static int UpperBoundIndex<T>(this IReadOnlyList<T> collection, T value) where T : INumber<T>
        {
            int left = -1, right = collection.Count;
            while (right - left > 1)
            {
                int mid = (left + right) >> 1;
                if (collection[mid] <= value)
                    left = mid;
                else
                    right = mid;
            }

            return right;
        }

        /// <summary>
        /// Calculates the prefix sum of a collection
        /// </summary>
        public static T[] PrefixSum<T>(this IReadOnlyList<T> collection) where T : INumber<T>
        {
            return GenericPrefixSum(collection, T.Zero, (acc, cur) => acc + cur);
        }

        /// <summary>
        /// Calculates the generic prefix sum of a collection
        /// </summary>
        public static V[] GenericPrefixSum<T, V>(this IReadOnlyList<T> collection, V zero, Func<V, T, V> operation) where T : INumber<T> where V : INumber<V>
        {
            V[] newArr = new V[collection.Count + 1];
            newArr[0] = zero;
            for (int i = 0; i < collection.Count; i++)
            {
                newArr[i + 1] = operation(newArr[i], collection[i]);
            }

            return newArr;
        }

        /// <summary>
        /// Gets or adds a value to a dictionary
        /// </summary>
        public static TV GetOrAdd<TK, TV>(this IDictionary<TK, TV> dictionary, TK key, TV value)
        {
            if (dictionary.TryGetValue(key, out TV? tempVal))
            {
                return tempVal;
            }

            dictionary.Add(key, value);

            return dictionary[key];
        }

        /// <summary>
        /// Gets or adds a value to a dictionary using a factory function
        /// </summary>
        public static TV GetOrAdd<TK, TV>(this IDictionary<TK, TV> dictionary, TK key, Func<TV> valueFactory)
        {
            if (dictionary.TryGetValue(key, out TV? tempVal))
            {
                return tempVal;
            }

            dictionary.Add(key, valueFactory());

            return dictionary[key];
        }
    }

    /// <summary>
    /// Extension methods for streams
    /// </summary>
    public static class StreamExtensions
    {
        /// <summary>
        /// Reads a line from a stream and splits it into an array
        /// </summary>
        public static string[] ReadLineSplit(this StreamReader reader)
        {
            return reader.ReadLine()!.Split(' ');
        }

        /// <summary>
        /// Reads an array from a stream
        /// </summary>
        public static T[] InputArray<T>(this StreamReader reader) where T : INumber<T>
        {
            return reader.InputArray<T>(0);
        }

        /// <summary>
        /// Reads an array from a stream with a specified start index
        /// </summary>
        public static T[] InputArray<T>(this StreamReader reader, int start) where T : INumber<T>
        {
            string[] raw = reader.ReadLineSplit();
            T[] arr = new T[start + raw.Length];

            for (int i = 0; i < raw.Length; i++)
            {
                arr[i + start] = T.Parse(raw[i], CultureInfo.CurrentCulture);
            }
            return arr;
        }

        /// <summary>
        /// Reads a tuple of two values from a stream
        /// </summary>
        public static (T, T) InputTuple2<T>(this StreamReader reader) where T : INumber<T>
        {
            var array = reader.InputArray<T>();
            return (array[0], array[1]);
        }

        /// <summary>
        /// Reads a tuple of three values from a stream
        /// </summary>
        public static (T, T, T) InputTuple3<T>(this StreamReader reader) where T : INumber<T>
        {
            var array = reader.InputArray<T>();
            return (array[0], array[1], array[2]);
        }

        /// <summary>
        /// Reads a tuple of four values from a stream
        /// </summary>
        public static (T, T, T, T) InputTuple4<T>(this StreamReader reader) where T : INumber<T>
        {
            var array = reader.InputArray<T>();
            return (array[0], array[1], array[2], array[3]);
        }

        /// <summary>
        /// Reads a tuple of five values from a stream
        /// </summary>
        public static (T, T, T, T, T) InputTuple5<T>(this StreamReader reader) where T : INumber<T>
        {
            var array = reader.InputArray<T>();
            return (array[0], array[1], array[2], array[3], array[4]);
        }

        /// <summary>
        /// Reads a string from a stream
        /// </summary>
        public static char[] InputString(this StreamReader reader)
        {
            return reader.ReadLine()!.ToCharArray();
        }

        /// <summary>
        /// Reads a value from a stream
        /// </summary>
        public static T Input<T>(this StreamReader reader) where T : INumber<T>
        {
            return T.Parse(reader.ReadLine()!, CultureInfo.CurrentCulture);
        }

        /// <summary>
        /// Writes "YES" to a stream
        /// </summary>
        public static void Yes(this StreamWriter writer)
        {
            writer.WriteLine("YES");
        }

        /// <summary>
        /// Writes "NO" to a stream
        /// </summary>
        public static void No(this StreamWriter writer)
        {
            writer.WriteLine("NO");
        }

        /// <summary>
        /// Writes "YES" or "NO" to a stream based on a condition
        /// </summary>
        public static void YesNo(this StreamWriter writer, bool cond)
        {
            if (cond)
                writer.Yes();
            else
                writer.No();
        }

        /// <summary>
        /// Writes an array to a stream
        /// </summary>
        public static void WriteArray<T>(this StreamWriter writer, IReadOnlyList<T> arr)
        {
            writer.WriteLine(string.Join(' ', arr));
        }
    }
    #endregion

    /// <summary>
    /// Main program class for solving the Lever problem
    /// </summary>
    public class LeverSolver
    {
        private const int BufferSize = 1 << 16;
        private const long Modulo = 1_000_000_007L;

        private readonly StreamWriter _output;
        private readonly StreamReader _input;

        /// <summary>
        /// Initializes a new instance of the LeverSolver class
        /// </summary>
        public LeverSolver(Stream input, Stream output)
        {
            _output = new StreamWriter(output, Encoding.UTF8, BufferSize);
            _input = new StreamReader(input, Encoding.UTF8, false, BufferSize);
        }

        /// <summary>
        /// Main entry point for the program
        /// </summary>
        public static void Main()
        {
            using var solver = new LeverSolver(
                System.Console.OpenStandardInput(),
                System.Console.OpenStandardOutput()
            );

            solver.Solve();
        }

        /// <summary>
        /// Solves the problem for multiple test cases
        /// </summary>
        public void Solve()
        {
            int testCases = ReadInt();
            for (int i = 0; i < testCases; i++)
            {
                SolveTestCase();
            }
            _output.Flush();
        }

        /// <summary>
        /// Solves a single test case
        /// </summary>
        private void SolveTestCase()
        {
            int n = ReadInt();
            int[] firstArray = ReadIntArray(n);
            int[] secondArray = ReadIntArray(n);

            int totalOperations = CalculateMinimumOperations(firstArray, secondArray);
            _output.WriteLine(totalOperations);
        }

        /// <summary>
        /// Calculates the minimum number of operations needed to balance two arrays
        /// </summary>
        private int CalculateMinimumOperations(int[] firstArray, int[] secondArray)
        {
            int excessSum = 0;
            int deficitSum = 0;

            for (int i = 0; i < firstArray.Length; i++)
            {
                int difference = firstArray[i] - secondArray[i];
                if (difference > 0)
                {
                    excessSum += difference;
                }
                else if (difference < 0)
                {
                    deficitSum += -difference;
                }
            }

            // The minimum operations is the maximum of excess and deficit sums
            // plus one for the final adjustment if needed
            return Math.Max(excessSum, deficitSum) + 1;
        }

        #region Input Helpers

        private int ReadInt() => int.Parse(ReadLine()!);

        private int[] ReadIntArray(int length)
        {
            string[] parts = ReadLine()!.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            return Array.ConvertAll(parts, int.Parse);
        }

        private string? ReadLine() => _input.ReadLine();

        #endregion

        #region IDisposable Implementation

        public void Dispose()
        {
            _output?.Dispose();
            _input?.Dispose();
        }

        #endregion
    }
}