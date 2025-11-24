// Problem: CF 1698 D - Fixed Point Guessing
// https://codeforces.com/contest/1698/problem/D

/*
Algorithm: Binary Search with Query-based Detection
Purpose: Find the element that did not change position in an array after several disjoint swaps.
Time Complexity: O(log n) per test case due to binary search approach
Space Complexity: O(n) for storing the sorted query results
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

    class Program
    {
        protected IOHelper ioHelper;
        int t;
        int n;
        List<int> rez = new List<int>();

        public int query(int l, int r)
        {
            int ans = 0;
            rez.Clear(); // Clear previous results
            ioHelper.WriteLine($"? {l} {r}");
            ioHelper.Flush(); // Send query to jury
            int t = r - l + 1; // Number of elements in subarray
            while (t > 0)
            {
                var a = ioHelper.ReadNextInt(); // Read sorted elements from jury
                rez.Add(a);
                if (a < l || a > r) // Check if element is out of range
                    ans++;
                t--;
            }
            return ans; // Return count of out of range elements
        }

        public void Solve()
        {
            t = ioHelper.ReadNextInt(); // Read number of test cases
            int i,
                j;
            while (t > 0)
            {
                n = ioHelper.ReadNextInt(); // Read array length
                int left = 1;
                int right = n;
                int ans = -1;
                // Binary search to find fixed point
                while (left < right)
                {
                    int mid = (left + right) / 2;
                    // Ensure mid is odd for balanced split
                    if ((mid - left + 1) % 2 == 0)
                        mid++;
                    if (mid == right)
                    {
                        ans = left;
                        if (query(ans, ans) == 0) // Single element query
                            break;
                        ans = -1;
                        left++;
                        continue;
                    }
                    var qans = query(left, mid); // Query half of the range
                    if (qans % 2 == 0)
                    { // Even count implies fixed element in right half
                        if (ans > 0)
                            ans = right;
                        right = mid; // Move to left half
                    }
                    else
                    { // Odd count implies fixed element in left half
                        left = mid + 1; // Move to right half
                    }
                }
                if (ans < 0)
                    ans = left; // Set final answer
                ioHelper.WriteLine($"! {ans}"); // Output result
                ioHelper.Flush(); // Send answer to jury
                t--; // Process next test case
            }
            ioHelper.Flush(); // Flush final output
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
