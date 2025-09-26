using System;

class Program
{
    static bool Solve()
    {  
        int n = int.Parse(Console.ReadLine());
        int[] a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        int[] b = new int[n + 5]; // Prevents index out of bounds

        for (int i = 0; i < n; i++)
        {
            if (a[i] < 1 || a[i] > n) return false; // Additional safeguard
            b[a[i]]++;
        }

        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {   
            if (b[i] == 0)
            {
                if (cnt  == 1) return false;
                if (cnt >= 2) cnt -= 2; 
            }
            else
            {
                int asa = b[i] + cnt;
                if (asa == 1) return false;
                cnt = asa - 2;
            }
        }
        return true;
    }

    static void Main(string[] args)
    {
        int t = int.Parse(Console.ReadLine());
        for (int i = 0; i < t; i++) // Fixed loop (starts at 0, not 1)
        {
            Console.WriteLine(Solve() ? "Yes" : "No");
        }
    }
}
