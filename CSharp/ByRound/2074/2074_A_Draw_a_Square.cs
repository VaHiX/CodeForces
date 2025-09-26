using System;
using System.Linq ;
public class Test
{
    static void Main(String[] args)
    {
        int test = int.Parse(Console.ReadLine());
        for(int i = 1 ; i<=test ; i++)
        {
            String input =  Console.ReadLine() ;
            int[] num = input.Split(' ').Select(int.Parse).ToArray();
            bool f = true ;
            for(int j=1 ; j<num.Length; j++)
            {
                if(num[j]!=num[j-1]) f =false;
            }
            if(f) Console.WriteLine("YES");
            else Console.WriteLine("NO");
        
        }
    }
        
}