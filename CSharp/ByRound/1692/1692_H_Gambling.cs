// Problem: CF 1692 H - Gambling
// https://codeforces.com/contest/1692/problem/H

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VaHiX
{
    internal class Program
    {
        static void Main(string[] args)
        {
            long tests = Read.Long(); // Read number of test cases
            List<string> results = new List<string>(); // Store results for each test case
            while (tests-- > 0)
            {
                int len = Read.Int(); // Read length of array
                string[] line = Read.Strings(); // Read array elements
                int[] arr = new int[len]; // Create array to store elements
                Dictionary<int, List<int>> check = new Dictionary<int, List<int>>(); // Dictionary to store indices of each number
                for (int i = 0; i < len; i++)
                {
                    arr[i] = int.Parse(line[i]); // Parse and store array element
                    if (!check.ContainsKey(arr[i]))
                    { // If number not present in dictionary
                        check.Add(arr[i], new List<int>()); // Add it with empty list
                    }
                    check[arr[i]].Add(i); // Add index of current element to number's list
                }
                int max = 0; // Maximum count of consecutive indices
                int mB = 0,
                    mE = 0,
                    mV = 0; // Variables to store result: value, start, end
                int b = -1,
                    e = 0,
                    p = 0; // Temporary variables for tracking ranges
                foreach (var k in check)
                { // For each unique number
                    int num = k.Key; // Current number
                    int count = 0; // Count of consecutive indices
                    b = -1; // Start of current range
                    List<int> ch1 = k.Value; // List of indices for current number
                    for (int i = 0; i < ch1.Count; i++)
                    { // Iterate through indices
                        if (b == -1)
                        { // If start of range not set
                            b = ch1[i]; // Set start
                            p = b; // Set previous
                        }
                        count++; // Increase count
                        e = ch1[i]; // Set end
                        // Adjust count based on gap between current and previous indices
                        count -= e - 1 >= p + 1 ? e - p - 1 : 0;
                        if (count > max)
                        { // If current count is greater than max
                            mV = num; // Store number
                            max = count; // Update max
                            mB = b; // Store start
                            mE = e; // Store end
                        }
                        if (count <= 0)
                        { // If count becomes non-positive
                            b = e; // Reset start
                            p = e; // Reset previous
                            count = 1; // Reset count
                        }
                        p = e; // Update previous
                    }
                }
                results.Add((mV) + " " + (mB + 1) + " " + (mE + 1)); // Add result for this test case
            }
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine(string.Join("\n", results)); // Output all results
            Console.ForegroundColor = ConsoleColor.Gray;
        }

        class Read
        {
            public static string String()
            {
                return Console.ReadLine();
            }

            public static char Char()
            {
                return char.Parse(String());
            }

            public static int Int()
            {
                return int.Parse(String());
            }

            public static long Long()
            {
                return long.Parse(String());
            }

            public static double Double()
            {
                return double.Parse(String());
            }

            public static string[] Strings()
            {
                return String().Split(' ');
            }

            public static char[] Chars()
            {
                return Array.ConvertAll(String().Split(' '), char.Parse);
            }

            public static int[] Ints()
            {
                return Array.ConvertAll(String().Split(' '), int.Parse);
            }

            public static long[] Longs()
            {
                return Array.ConvertAll(String().Split(' '), long.Parse);
            }

            public static double[] Doubles()
            {
                return Array.ConvertAll(String().Split(' '), double.Parse);
            }
        }
    }
}

// ### Algorithm/Techniques:
// - **Sliding Window with Dictionary**: The algorithm uses a dictionary to group indices of same numbers and then applies a sliding window technique to maximize the count of consecutive indices for a fixed number.
// - **Greedy Approach**: It greedily selects the best range that maximizes the winning count.

// ### Time Complexity:
// - $ O(n) $ where $ n $ is the length of the input array. Each element is processed once to build the dictionary, and then again to find the maximum interval.

// ### Space Complexity:
// - $ O(n) $ for storing the dictionary and the input array. The dictionary stores at most $ n $ elements in the worst case.

// https://github.com/VaHiX/CodeForces/
