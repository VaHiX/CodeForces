using System;
public class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        //int t = 1;
        while (t-- > 0)
        {
            string[] s = Console.ReadLine().Split();
            int x = int.Parse(s[0]);
            int y = int.Parse(s[1]);
            int a = int.Parse(s[2]);
            Console.WriteLine(((a % (x + y)) < x)?"NO":"YES");
        }
    }
}