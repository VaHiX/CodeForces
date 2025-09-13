using System;
using System.Collections.Generic;
using System.Linq;

public class Program
{
    public static void Main()
    {
        int n = int.Parse(Console.ReadLine());
        for (int i = 0; i < n; i++) {
            string input = Console.ReadLine();
            List<int> numbers = input.Split(' ').Select(int.Parse).ToList();
            int e = numbers[0];
            int p = numbers[1];
            int l = numbers[2];
            int r = numbers[3];

            int ls = 0;
            int rs = 0;

            for(int j = 0; j < p; j++)
            {
                if(!(l == 0 || ls == l))
                {
                    ls -= 1;
                    continue;
                }
                if(!( r == 0 || rs == r))
                {
                    rs += 1;
                    continue;
                }
            }
            
            Console.WriteLine($"{ls} {rs}");

        }
    }
}