// Problem: CF 1931 D - Divisible Pairs
// https://codeforces.com/contest/1931/problem/D

/*
 * Problem: D. Divisible Pairs
 *
 * Algorithm:
 * - For each element in the array, we compute its remainders when divided by x and y.
 * - We maintain a dictionary (vals) that maps (remainder mod x, remainder mod y) pairs to their count.
 * - For each new element, we check if there exists a previous element that can form a beautiful pair with it.
 *   A pair (i, j) is beautiful if:
 *     (a[i] + a[j]) % x == 0
 *     (a[i] - a[j]) % y == 0
 * - This translates to:
 *     a[i] % x + a[j] % x ≡ 0 (mod x) => a[j] % x ≡ (x - a[i] % x) (mod x)
 *     a[i] % y - a[j] % y ≡ 0 (mod y) => a[i] % y ≡ a[j] % y (mod y)
 * - Therefore, for current element a[i], we look for elements that have:
 *   (a[i] % x) = (x - (a[j] % x)) % x and (a[i] % y) = (a[j] % y)
 * - We keep a running count of such pairs and increment the result accordingly.
 *
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(min(n, x * y)) in the worst case for storing the dictionary.
 */

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test
{
    class IOHelper : IDisposable
    {
        StreamReader reader;
        StreamWriter writer;

        public IOHelper(string inputFile, string outputFile, Encoding encoding)
        {
            StreamReader iReader;
            StreamWriter oWriter;
            if (inputFile == null)
                iReader = new StreamReader(Console.OpenStandardInput(), encoding);
            else
                iReader = new StreamReader(inputFile, encoding);
            if (outputFile == null)
                oWriter = new StreamWriter(Console.OpenStandardOutput(), encoding);
            else
                oWriter = new StreamWriter(outputFile, false, encoding);
            reader = iReader;
            writer = oWriter;
            curLine = new string[] { };
            curTokenIdx = 0;
        }

        string[] curLine;
        int curTokenIdx;
        char[] whiteSpaces = new char[] { ' ', '\t', '\r', '\n' };

        public string ReadNextToken()
        {
            if (curTokenIdx >= curLine.Length)
            {
                string line = reader.ReadLine();
                if (line != null)
                    curLine = line.Split(whiteSpaces, StringSplitOptions.RemoveEmptyEntries);
                else
                    curLine = new string[] { };
                curTokenIdx = 0;
            }
            if (curTokenIdx >= curLine.Length)
                return null;
            return curLine[curTokenIdx++];
        }

        public int ReadNextInt()
        {
            return int.Parse(ReadNextToken());
        }

        public double ReadNextDouble()
        {
            var nextToken = ReadNextToken();
            var result = 0.0;
            nextToken = nextToken.Replace(
                ".",
                System
                    .Threading
                    .Thread
                    .CurrentThread
                    .CurrentCulture
                    .NumberFormat
                    .NumberDecimalSeparator
            );
            result = double.Parse(nextToken);
            return result;
        }

        public void Write(string stringToWrite)
        {
            writer.Write(stringToWrite);
        }

        public void WriteLine(string stringToWrite)
        {
            writer.WriteLine(stringToWrite);
        }

        public void WriteLine(double valueToWrite)
        {
            writer.WriteLine(valueToWrite.ToString("F8"));
        }

        public void Dispose()
        {
            try
            {
                if (reader != null)
                {
                    reader.Dispose();
                }
                if (writer != null)
                {
                    writer.Dispose();
                }
            }
            catch { }
            ;
        }

        public void Flush()
        {
            if (writer != null)
            {
                writer.Flush();
            }
        }
    }

    class Program
    {
        protected IOHelper ioHelper;
        int t,
            n,
            x,
            y;
        Dictionary<int, Dictionary<int, int>> vals = new Dictionary<int, Dictionary<int, int>>();

        public void Solve()
        {
            t = ioHelper.ReadNextInt();
            while (t-- > 0)
            {
                n = ioHelper.ReadNextInt();
                x = ioHelper.ReadNextInt();
                y = ioHelper.ReadNextInt();
                vals.Clear();
                int i;
                long res = 0;
                for (i = 0; i < n; i++)
                {
                    int a = ioHelper.ReadNextInt();
                    int xx = a % x; // remainder when divided by x
                    int yy = a % y; // remainder when divided by y
                    int targetxx = x - xx; // required remainder for x
                    if (targetxx == x)
                        targetxx = 0; // handle special case where xx = 0
                    int targetyy = yy; // required remainder for y
                    if (vals.ContainsKey(targetxx))
                        if (vals[targetxx].ContainsKey(targetyy))
                            res += vals[targetxx][targetyy]; // add count of matching pairs
                    if (!vals.ContainsKey(xx))
                        vals[xx] = new Dictionary<int, int>();
                    if (!vals[xx].ContainsKey(yy))
                        vals[xx][yy] = 0;
                    vals[xx][yy]++; // increment count of current (xx, yy) pair
                }
                ioHelper.WriteLine(res.ToString());
            }
            ioHelper.Flush();
        }

        public Program(string inputFile, string outputFile)
        {
            ioHelper = new IOHelper(inputFile, outputFile, Encoding.Default);
            Solve();
            ioHelper.Dispose();
        }

        static void Main(string[] args)
        {
            Program myProgram = new Program(null, null);
        }
    }
}


// https://github.com/VaHiX/CodeForces/
