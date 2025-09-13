using System;
using System.IO.Pipes;

public class Program
{
    public static void Main()
    {
        Program program = new Program();
        program.Task_B();
    }
    public void Task_A()
    {

        int t = int.Parse(Console.ReadLine());
        for (int i = 0; i < t; i++)
        {
            int ans = 0;

            string s = Console.ReadLine();
            foreach (char c in s)
            {
                if (c == '1')
                    ans++;
            }
            Console.WriteLine(ans);
        }


    }
    public void Task_B()
    {

        int t = int.Parse(Console.ReadLine());
        for (int q = 0; q < t; q++)
        {
            int n = int.Parse(Console.ReadLine());
            string[] s = Console.ReadLine().Split(' ');
            int[] a = new int[s.Length];
            for (int i=0; i < n; i++)
            {
                a[i] = int.Parse(s[i]);
            }
            int k = 0;
            bool f = true;
            if (n % 2 != 0)
                k++;
            for (int i = 0; i < n/2+k ;i++)
            {
                if (a[i] <= (n - 1 - i) * 2 || a[n - 1 - i] <= (n - 1 - i)*2)
                {
                    Console.WriteLine("NO");
                    f = false;
                    break;
                }
            }
            
            if (f)
                Console.WriteLine("YES");
        }
    }
}
