// Problem: CF 2044 D - Harder Problem
// https://codeforces.com/contest/2044/problem/D

/*
 * Problem: Construct an array b such that a[i] is a mode of the prefix b[0..i].
 *
 * Algorithm:
 * - For each element a[i] in the input array:
 *   - If a[i] has not been used yet in the current prefix, use it.
 *   - Otherwise, find the smallest unused integer in [1, n] and place it in b[i].
 *
 * Time Complexity: O(n^2) in worst case due to nested loops in the 'while' block.
 * Space Complexity: O(n) for storing the arrays and visited flags.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp16
{
    internal class Program
    {
        static void Main(string[] args)
        {
            for (int t = int.Parse(Console.ReadLine()); t > 0; t--)
            {
                int n = int.Parse(Console.ReadLine());
                string line = Console.ReadLine();
                int[] array = new int[n];
                int cnt = 0;
                foreach (string s in line.Split(' '))
                {
                    array[cnt] = int.Parse(s);
                    cnt++;
                }
                int[] writing = new int[n];
                cnt = 1;
                bool[] visited = new bool[n];
                for (int i = 0; i < n; i++)
                {
                    if (visited[array[i] - 1])
                    {
                        // If the value a[i] has already been seen, find the smallest unused index.
                        while (true)
                        {
                            if (visited[cnt - 1])
                            {
                                cnt++;
                            }
                            else
                            {
                                visited[cnt - 1] = true;
                                Console.Write(cnt);
                                cnt++;
                                break;
                            }
                        }
                    }
                    else
                    {
                        // If a[i] is new, mark it as visited and use it.
                        visited[array[i] - 1] = true;
                        writing[i] = array[i];
                        Console.Write(writing[i]);
                    }
                    Console.Write(" ");
                }
                Console.WriteLine();
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/
