using System;
using System.Text;

class Program
{

    static void solve()
    {

        int n = int.Parse(Console.ReadLine());
        int aux = n / 5;
        int[] vowels = new int[5];
        Array.Fill(vowels, aux);

        for (int i = 0; i < n % 5; i++)
        {
            vowels[i]++;
        }

        string vow = "aeiou";

        StringBuilder result = new StringBuilder();

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < vowels[i]; j++)
            {
                result.Append(vow[i]);
            }
        }

        Console.WriteLine(result.ToString());
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        for (int i = 0; i < t; i++)
        {
            solve();

        }
    }
}
