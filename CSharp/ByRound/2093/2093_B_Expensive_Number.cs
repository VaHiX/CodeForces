using System;
public class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while(t-- > 0)
        {
            string s = Console.ReadLine();
            int n = s.Length;
            int lz = 0,cnt = 0;
            for(int i = n - 1;i >= 0;i--)
            {
                if(s[i] == '0') 
                {
                    if(lz == 0) cnt++;
                }
                else 
                {
                    if(lz == 0) lz = 1;
                    else cnt++;
                }
            }
            Console.WriteLine($"{cnt}");
        }
    }
}