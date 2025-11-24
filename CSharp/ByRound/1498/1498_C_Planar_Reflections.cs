// Problem: CF 1498 C - Planar Reflections
// https://codeforces.com/contest/1498/problem/C

/*
Algorithm: Dynamic Programming with Simulation
Time Complexity: O(n * k)
Space Complexity: O(n)

This solution simulates the particle reflection process through n planes.
For each decay age k > 1, we simulate how particles bounce back and forth,
generating copies at each plane. The key insight is that we maintain arrays
to track particles going left and right, and at each step we compute how
many new particles are generated and add them to the result.

The problem can be viewed as a dynamic programming approach where we track
the number of particles of each decay age moving in each direction at each step.
*/

using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Numerics;

namespace Task
{
    static class Program
    {
        #region Read / Write
        static TextReader Reader;
        static TextWriter Writer;
        private static Queue<string> _currentLineTokens = new Queue<string>();

        private static string[] ReadAndSplitLine()
        {
            return Reader
                .ReadLine()
                .Split(new[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
        }

        public static string ReadToken()
        {
            while (_currentLineTokens.Count == 0)
                _currentLineTokens = new Queue<string>(ReadAndSplitLine());
            return _currentLineTokens.Dequeue();
        }

        public static int ReadInt()
        {
            return int.Parse(ReadToken());
        }

        public static long ReadLong()
        {
            return long.Parse(ReadToken());
        }

        public static double ReadDouble()
        {
            return double.Parse(ReadToken(), CultureInfo.InvariantCulture);
        }

        public static int[] ReadIntArray()
        {
            return ReadAndSplitLine().Select(int.Parse).ToArray();
        }

        public static long[] ReadLongArray()
        {
            return ReadAndSplitLine().Select(long.Parse).ToArray();
        }

        public static double[] ReadDoubleArray()
        {
            return ReadAndSplitLine()
                .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                .ToArray();
        }

        public static int[][] ReadIntMatrix(int numberOfRows)
        {
            int[][] matrix = new int[numberOfRows][];
            for (int i = 0; i < numberOfRows; i++)
                matrix[i] = ReadIntArray();
            return matrix;
        }

        public static int[][] ReadAndTransposeIntMatrix(int numberOfRows)
        {
            int[][] matrix = ReadIntMatrix(numberOfRows);
            int[][] ret = new int[matrix[0].Length][];
            for (int i = 0; i < ret.Length; i++)
            {
                ret[i] = new int[numberOfRows];
                for (int j = 0; j < numberOfRows; j++)
                    ret[i][j] = matrix[j][i];
            }
            return ret;
        }

        public static string[] ReadLines(int quantity)
        {
            string[] lines = new string[quantity];
            for (int i = 0; i < quantity; i++)
                lines[i] = Reader.ReadLine().Trim();
            return lines;
        }

        public static void WriteArray<T>(T[] arr)
        {
            Writer.WriteLine(string.Join(" ", arr));
        }

        public static void WriteArray<T>(IEnumerable<T> arr)
        {
            Writer.WriteLine(string.Join(" ", arr));
        }

        public static void Write<T>(T value)
        {
            Writer.Write(value + " ");
        }

        public static void WriteLine<T>(T value)
        {
            Writer.WriteLine(value);
        }
        #endregion
        private static readonly int modulus = 1000000007;
        private static readonly int modulus1 = modulus - 1;

        public static long Pow(long a, long b)
        {
            long y = 1;
            while (true)
            {
                if ((b & 1) != 0)
                    y = a * y % modulus;
                b = b >> 1;
                if (b == 0)
                    return y;
                a = a * a % modulus;
            }
        }

        public static long ReversedNumbByPrimeModulo(long a)
        {
            return Pow(a, modulus - 2);
        }

        public static long FactByModulo(long a)
        {
            long ans = 1;
            while (a > 0)
            {
                ans = ans * a % modulus;
                a--;
            }
            return ans;
        }

        public static long nCkModulo(long n, long k)
        {
            if (k < n >> 1)
                k = n - k;
            long ans = 1;
            for (long i = n; i > k; i--)
                ans = ans * i % modulus;
            k = n - k;
            var fact = FactByModulo(k);
            var revFact = ReversedNumbByPrimeModulo(fact);
            ans = ans * revFact % modulus;
            return ans;
        }

        #region Heap
        public static void InsertElementInHeap(int value, int[] arr, ref int sizeOfTree)
        {
            arr[sizeOfTree + 1] = value;
            sizeOfTree++;
            HeapifyBottomToTop(sizeOfTree, arr);
        }

        public static void HeapifyBottomToTop(int index, int[] arr)
        {
            int parent = index / 2;
            if (index <= 1)
            {
                return;
            }
            if (arr[index] > arr[parent])
            {
                int tmp = arr[index];
                arr[index] = arr[parent];
                arr[parent] = tmp;
            }
            HeapifyBottomToTop(parent, arr);
        }

        public static int ExtractHeadOfHeap(ref int sizeOfTree, int[] arr)
        {
            if (sizeOfTree == 0)
            {
                return -1;
            }
            else
            {
                int extractedValue = arr[1];
                arr[1] = arr[sizeOfTree];
                sizeOfTree--;
                HeapifyTopToBottom(1, sizeOfTree, arr);
                return extractedValue;
            }
        }

        public static void HeapifyTopToBottom(int index, int sizeOfTree, int[] arr)
        {
            int left = index << 1;
            int right = left + 1;
            int smallestChild = 0;
            if (sizeOfTree < left)
            {
                return;
            }
            else if (sizeOfTree == left)
            {
                if (arr[index] < arr[left])
                {
                    int tmp = arr[index];
                    arr[index] = arr[left];
                    arr[left] = tmp;
                }
                return;
            }
            else
            {
                if (arr[left] > arr[right])
                {
                    smallestChild = left;
                }
                else
                {
                    smallestChild = right;
                }
                if (arr[index] < arr[smallestChild])
                {
                    int tmp = arr[index];
                    arr[index] = arr[smallestChild];
                    arr[smallestChild] = tmp;
                }
            }
            HeapifyTopToBottom(smallestChild, sizeOfTree, arr);
        }
        #endregion
        static long GCD(long a, long b)
        {
            while (b > 0)
            {
                a %= b;
                a ^= b;
                b ^= a;
                a ^= b;
            }
            return a;
        }

        static void Main(string[] args)
        {
            Reader = new StreamReader(Console.OpenStandardInput());
            Writer = new StreamWriter(Console.OpenStandardOutput());
            var t = ReadInt();
            for (var tmp = 0; tmp < t; tmp++)
            {
                Solve();
            }
            Reader.Close();
            Writer.Close();
        }

        static void Solve()
        {
            var n = ReadLong();
            var k = ReadLong();
            long mod = 1000000007;
            var ans = 1l;
            if (k > 1)
                ans += n; // Base case: one particle at each plane after first bounce
            var arr1 = new long[n];
            var arr2 = new long[n];
            for (var i = 0; i < n; i++)
                arr1[i] = 1; // Initialize one particle going right at each position
            var toRight = false;
            // For each decay level from k-2 down to 1
            for (var j = k - 2; j >= 1; j--)
            {
                if (toRight)
                {
                    // Process particles going right and generate new particles going left
                    var tmp = 0l;
                    for (var i = 1; i < n; i++)
                    {
                        tmp += arr2[i - 1]; // Cumulative sum from left to right
                        tmp %= mod;
                        ans += tmp;
                        ans %= mod;
                        arr1[i] = tmp; // Store the cumulative count for next iteration
                    }
                }
                else
                {
                    // Process particles going left and generate new particles going right
                    var tmp = 0l;
                    for (var i = n - 2; i >= 0; i--)
                    {
                        tmp += arr1[i + 1]; // Cumulative sum from right to left
                        tmp %= mod;
                        ans += tmp;
                        ans %= mod;
                        arr2[i] = tmp; // Store the cumulative count for next iteration
                    }
                }
                toRight ^= true; // Toggle direction for next iteration
            }
            WriteLine(ans);
        }

        public class MyStruct
        {
            public int Index;
            public int Weight;
            public int Value;

            public MyStruct(int index, int weight, int value)
            {
                Index = index;
                Weight = weight;
                Value = value;
            }
        }

        static void Inc(this Dictionary<long, long> dict, long key, long addedValue)
        {
            if (dict.ContainsKey(key))
                dict[key] += addedValue;
            else
                dict[key] = addedValue;
        }

        static void Inc(this Dictionary<int, int> dict, int key, int addedValue)
        {
            if (dict.ContainsKey(key))
                dict[key] += addedValue;
            else
                dict[key] = addedValue;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
