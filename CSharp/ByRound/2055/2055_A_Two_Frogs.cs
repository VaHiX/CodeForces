using System;
class Program
{
    static string[] InputLine;
    static int t;
    static int n, a, b;

    static bool[] Ans;
    static void Main()
    {
        t = int.Parse(Console.ReadLine());
        Ans = new bool[t];

        for (int i = 0; i < t; i++)
        {
            InputNextSet();
            FindAnswerForCurI(i);
        }
        Output();
    }
    static void InputNextSet()
    {
        InputLine = Console.ReadLine().Split();
        n = int.Parse(InputLine[0]);
        a = int.Parse(InputLine[1]);
        b = int.Parse(InputLine[2]);
    }
    static void Output()
    {
        foreach (bool elem in Ans)
        {
            if (elem)
            {
                Console.WriteLine("YES");
            }
            else
            {
                Console.WriteLine("NO");
            }
        }
    }
    static void FindAnswerForCurI(int i)
    {
        bool ans;
        {
            int len = Math.Abs(a - b)-1;
            if((len == 0) || (len % 2 == 0))
            {
                ans = false;
            }
            else
            {
                ans = true;
            }
        }
        Ans[i] = ans;
    }
}