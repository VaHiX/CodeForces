using System;
using System.Collections.Generic;

class Program
{
    const long md = 998244353;
    
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());  // Reading number of test cases
        List<long> ctl = new List<long>(new long[5050]);
        ctl[0] = 1;
        
        // Precompute Catalan numbers up to 5050
        for (int n = 1; n < 5050; n++)
        {
            for (int i = 1; i <= n; i++)
            {
                ctl[n] = (ctl[n] + ctl[i - 1] * ctl[n - i] % md) % md;
            }
        }

        // Process each test case
        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine());
            long ans = ctl[n];
            Console.Write(ans + " ");

            char[] s = new string('.', 2 * n + 2).ToCharArray();
            s[0] = '(';
            s[2 * n + 1] = ')';

            // Handle each query for the test case
            for (int a = 0; a < n; a++)
            {
                string[] tokens = Console.ReadLine().Split();
                int i = int.Parse(tokens[0]);
                int j = int.Parse(tokens[1]);

                ans = 1;
                s[i] = '(';
                s[j] = ')';

                Stack<char> stk = new Stack<char>();
                foreach (char c in s)
                {
                    if (c == ')')
                    {
                        int cnt = 0;
                        while (stk.Count > 0 && stk.Peek() != '(')
                        {
                            cnt++;
                            stk.Pop();
                        }
                        stk.Pop();  // Pop the '('
                        ans = (ans * ctl[cnt / 2]) % md;
                    }
                    else
                    {
                        stk.Push(c);
                    }
                }
                Console.WriteLine(ans);
            }
        }
    }
}
