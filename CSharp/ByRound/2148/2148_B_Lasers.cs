using System;

public class HelloWorld
{
    public static void Main(string[] args)
    {
        int T = int.Parse(Console.ReadLine());
        for(int i=0;i<T;i++){
            int[] input = Array.ConvertAll(Console.ReadLine().Split(),int.Parse);
            int n = input[0];
            int m = input[1];
            int x = input[2];
            int y = input[3];
            Console.ReadLine();
            Console.ReadLine();
            Console.WriteLine(n+m);
            
        }
    }
}