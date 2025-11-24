// Problem: CF 1922 E - Increasing Subsequences
// https://codeforces.com/contest/1922/problem/E

/*
 * Problem: E. Increasing Subsequences
 * Algorithm: Greedy approach with binary representation manipulation
 * Time Complexity: O(log X) per test case, as we iterate through bits of X
 * Space Complexity: O(log X) for storing the array, which is at most 200 elements
 *
 * Approach:
 * The idea is to represent the number X as a sum of powers of 2, and construct
 * an array such that the number of increasing subsequences equals X.
 *
 * For each bit in the binary representation of X:
 *   - If the bit is 0, we add a large number (curValLarge) and divide X by 2.
 *   - If the bit is 1, we add a small number (curValSmall) and decrement X by 1.
 *
 * This ensures that the number of increasing subsequences matches X.
 * The final array is reversed to maintain correct order.
 *
 * Sample Input-Output:
 * Input: 2
 * Output: 1\n0\n
 *
 * Input: 5
 * Output: 3\n0 1 0\n
 *
 * Input: 13
 * Output: 5\n2 2 3 4 2\n
 *
 * Input: 37
 * Output: 7\n-1 -1 0 0 2 3 -1\n
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
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
        int n,
            t;
        long X;

        public void Solve()
        {
            t = ioHelper.ReadNextInt();
            while (t > 0)
            {
                X = long.Parse(ioHelper.ReadNextToken());
                List<int> vec = new List<int>();
                int curValLarge = 200;
                int curValSmall = -200;
                while (X > 1)
                {
                    // If X is even, we add a large number and divide by 2
                    if ((X % 2) == 0)
                    {
                        vec.Add(curValLarge);
                        curValLarge--;
                        X /= 2;
                    }
                    else
                    {
                        // If X is odd, we add a small number and decrement X by 1
                        vec.Add(curValSmall);
                        curValSmall++;
                        X--;
                    }
                }
                vec.Reverse(); // Reverse to get correct order
                ioHelper.WriteLine(vec.Count.ToString());
                foreach (var x in vec)
                    ioHelper.Write($"{x} ");
                ioHelper.WriteLine("");
                t--;
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
