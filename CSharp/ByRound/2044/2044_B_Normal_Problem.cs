using System;

class Program
{
    static string ReverseView(string a)
    {
        char[] b = new char[a.Length];
        
        for (int i = 0; i < a.Length; i++)
        {
            if (a[i] == 'p') b[a.Length - 1 - i] = 'q';
            else if (a[i] == 'q') b[a.Length - 1 - i] = 'p';
            else b[a.Length - 1 - i] = 'w';
        }
        
        return new string(b);
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine().Trim());
        
        for (int i = 0; i < t; i++)
        {
            string a = Console.ReadLine().Trim();
            Console.WriteLine(ReverseView(a));
        }
    }
}
