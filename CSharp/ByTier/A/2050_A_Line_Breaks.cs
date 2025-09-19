using System;
using System.Text;
using System.Diagnostics.CodeAnalysis;
using System.Security.Cryptography.X509Certificates;
using System.Collections.Generic;
using System.Diagnostics.Tracing;

class Program
{
    static void Main()
    {
        int tk = int.Parse(Console.ReadLine()), sum = 0;
        for (int l = 0; l < tk; l++) {
            string[] nm = Console.ReadLine().Split(' ');
            int n = int.Parse(nm[0]), m = int.Parse(nm[1]);
            sum = 0;
            bool a = true;
            List<string> list = new List<string>();
            for (int i = 0; i < n; i++)
            {
                string word = Console.ReadLine();
                if (a)
                {
                    if (sum + word.Length > m)
                    {
                        a = false;
                    }
                    else
                    {
                        list.Add(word);
                        sum += word.Length;
                    } 
                }
            }
            if (list.Count==0) { Console.WriteLine(0); }
            else Console.WriteLine(list.Count);
        }
    }
}