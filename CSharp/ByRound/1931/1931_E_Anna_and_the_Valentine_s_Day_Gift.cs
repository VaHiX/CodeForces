// Problem: CF 1931 E - Anna and the Valentine's Day Gift
// https://codeforces.com/contest/1931/problem/E

/*
Problem: Anna and the Valentine's Day Gift
Purpose: Determine the winner of a game between Anna and Sasha where they manipulate a list of integers according to specific rules.
Algorithms/Techniques:
- Game theory approach: Analyze the game state based on trailing zeros in numbers
- Greedy strategy: Players take optimal moves to maximize their chances of winning
Time Complexity: O(n) where n is the total number of integers in all test cases
Space Complexity: O(1) since we use a fixed-size array of size 10 for counting trailing zeros

The game proceeds as follows:
1. Anna reverses a number (removes leading zeros from reversed digits)
2. Sasha concatenates two numbers and adds the result back to list
3. Game ends when only one number remains in the list
4. Sasha wins if final number >= 10^m, otherwise Anna wins

The key insight:
- Each reverse operation removes trailing zeros from a number
- If number has k trailing zeros, then after reverse operation we lose k digits
- Since Anna goes first and both play optimally, we simulate the optimal play
- The total number of digits (with adjustment for trailing zeros) determines the outcome
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
            m;
        List<int> withTrailingZeros = new List<int>();

        public void Solve()
        {
            t = ioHelper.ReadNextInt();
            while (t-- > 0)
            {
                n = ioHelper.ReadNextInt();
                m = ioHelper.ReadNextInt();
                withTrailingZeros.Clear();
                int i;
                // Initialize count array for trailing zeros (0 to 9)
                for (i = 0; i < 10; i++)
                    withTrailingZeros.Add(0);
                long totnumdigs = 0; // Total number of digits in all numbers
                for (i = 0; i < n; i++)
                {
                    int a = ioHelper.ReadNextInt();
                    int cnttz = 0; // Count of trailing zeros
                    int numdiga = 0; // Number of digits in current a
                    bool bTrailing = true; // Flag to track if we're still counting trailing zeros
                    do
                    {
                        numdiga++;
                        if ((a % 10 == 0) && bTrailing)
                            cnttz++; // If digit is 0 and we're still counting trailing zeros, increment count
                        else
                            bTrailing = false; // Stop counting trailing zeros once we hit a non-zero digit
                        a /= 10; // Move to next digit
                    } while (a > 0); // Continue while a > 0
                    totnumdigs += numdiga; // Add current number's digit count
                    withTrailingZeros[cnttz]++; // Increment count of numbers with cnttz trailing zeros
                }
                int bag = 9; // Start from maximum number of trailing zeros (9)
                bool bAliceTurn = true; // Anna plays first (true means it's Anna's turn)
                while (bag > 0)
                {
                    // If no numbers with 'bag' trailing zeros exist, move to lower count
                    if (withTrailingZeros[bag] == 0)
                    {
                        bag--;
                        continue;
                    }
                    // If it's Anna's turn, subtract the trailing zeros count from total
                    if (bAliceTurn)
                        totnumdigs -= bag;
                    // Decrement counter of numbers with 'bag' trailing zeros
                    withTrailingZeros[bag]--;
                    // Switch turns
                    bAliceTurn = !bAliceTurn;
                }
                // Check final condition: if total digits after optimal play > m, Sasha wins
                if (totnumdigs > m)
                    ioHelper.WriteLine("Sasha");
                else
                    ioHelper.WriteLine("Anna");
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
