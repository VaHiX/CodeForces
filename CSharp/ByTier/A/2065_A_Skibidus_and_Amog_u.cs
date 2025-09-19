using System;

public class Program
{
    public static void Main()
    {
        int c = int.Parse(Console.ReadLine());
        for (int i = 0; i < c; i++)
        {
            string s = Console.ReadLine();
            if (s.Length >= 2 && s[s.Length - 1] == 's' && s[s.Length - 2] == 'u')
            {
                s = s.Remove(s.Length - 2, 2);
                s += "i";
                
            }
            Console.WriteLine(s);
        }
    }
}
