using System;

class Program
{
    static void Main()
    {
        int munna = int.Parse(Console.ReadLine());
        
        while (munna-- > 0)
        {
            int sakshi = int.Parse(Console.ReadLine());
            string s = Console.ReadLine();
            
            int m = 0, u = 0;
            foreach (char c in s)
            {
                if (c == '-') m++;
                else u++;
            }
            
            if (m < 2 || u == 0)
            {
                Console.WriteLine(0);
            }
            else
            {
                Console.WriteLine((1L * m * m / 4) * u);
            }
        }
    }
}