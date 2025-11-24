// Problem: CF 1698 E - PermutationForces II
// https://codeforces.com/contest/1698/problem/E

﻿/*
 * Problem: E. PermutationForces II
 *
 * Algorithm/Technique:
 * - This problem involves determining how many ways we can fill missing elements in permutation b
 *   such that it's possible to transform array a into b using given strength s.
 * - The approach uses a sliding window technique along with dynamic programming concepts.
 * - For each element in the permutation, we determine whether it can be moved to its target position
 *   within the constraint of strength s.
 * - The solution tracks valid combinations using a custom StrangeNumber class to manage
 *   modular arithmetic and combinations.
 *
 * Time Complexity: O(n * s) - We process each element and for each element we may update up to s positions
 * Space Complexity: O(n) - Storing arrays and data structures of size n
 */

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VaHiX
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

    class StrangeNumber
    {
        public static long _prime = 998244353;
        public long A;
        public long B;

        public StrangeNumber(long a, long b)
        {
            A = a % _prime;
            B = b % _prime;
        }

        public StrangeNumber AddWith(StrangeNumber other)
        {
            long Ares = ((this.A * other.B) % _prime + (other.A * this.B) % _prime) % _prime;
            long Bres = (this.B * other.B) % _prime;
            if (other.A == 0)
            {
                Ares = this.A;
                Bres = this.B;
            }
            else if (this.A == 0)
            {
                Ares = other.A;
                Bres = other.B;
            }
            else { }
            return new StrangeNumber(Ares, Bres);
        }

        public StrangeNumber MulWith(StrangeNumber other)
        {
            long Ares = (this.A * other.A);
            long Bres = (this.B * other.B);
            if (this.A == 0 || other.A == 0)
            {
                Ares = 0;
                Bres = 1;
            }
            else { }
            return new StrangeNumber(Ares, Bres);
        }
    }

    class Program
    {
        protected IOHelper ioHelper;
        int t;
        int n;
        int s;
        int[] a = new int[200100];
        int[] posa = new int[200100];
        int[] b = new int[200100];
        HashSet<int> reqs = new HashSet<int>();
        Dictionary<int, int> insteadOf = new Dictionary<int, int>();
        Dictionary<int, int> targetOf = new Dictionary<int, int>();
        HashSet<int> carryOvers = new HashSet<int>();
        HashSet<int> curSet = new HashSet<int>();
        HashSet<int> targets = new HashSet<int>();

        public void Solve()
        {
            t = ioHelper.ReadNextInt();
            int i,
                j;
            while (t > 0)
            {
                n = ioHelper.ReadNextInt();
                s = ioHelper.ReadNextInt();
                reqs.Clear();
                insteadOf.Clear();
                targetOf.Clear();
                carryOvers.Clear();
                curSet.Clear();
                StrangeNumber availCombs = new StrangeNumber(0, 1);
                StrangeNumber curSum = new StrangeNumber(1, 1);
                for (i = 1; i <= n; i++)
                {
                    a[i] = ioHelper.ReadNextInt();
                    posa[a[i]] = i;
                    insteadOf[a[i]] = -1;
                    targetOf[i] = -1;
                }
                j = 0;
                for (i = 1; i <= n; i++)
                {
                    b[i] = ioHelper.ReadNextInt();
                    if (b[i] != -1)
                    {
                        reqs.Add(b[i]);
                        insteadOf[a[i]] = b[i];
                        targetOf[b[i]] = i;
                    }
                }
                // Initialize sliding window for first s positions
                for (j = 1; j <= 1 + s && j <= n; j++)
                {
                    curSet.Add(posa[j]);
                    if (insteadOf[j] == -1)
                        availCombs = availCombs.AddWith(new StrangeNumber(1, 1));
                }
                // Process each element to determine if transformation is valid
                for (i = 1; i < n; i++)
                {
                    var curb = insteadOf[i];
                    var targ = targetOf[i];
                    if (targ > 0)
                    {
                        // If target position is already in current set, remove it
                        if (curSet.Contains(targ))
                        {
                            curSet.Remove(targ);
                        }
                        else
                        {
                            // If target is not in current window, impossible transformation
                            curSum.A = 0;
                            break;
                        }
                    }
                    else
                    {
                        // If no specific target, multiply by available combinations
                        curSum = curSum.MulWith(availCombs);
                        availCombs = availCombs.AddWith(new StrangeNumber(-1, 1));
                        if (availCombs.A < 0)
                        {
                            curSum.A = 0;
                            break;
                        }
                    }
                    // Add next element to window if valid
                    if (i + 1 + s <= n)
                    {
                        curSet.Add(posa[i + 1 + s]);
                        if (insteadOf[i + 1 + s] == -1)
                            availCombs = availCombs.AddWith(new StrangeNumber(1, 1));
                    }
                }
                ioHelper.WriteLine(curSum.A.ToString());
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
