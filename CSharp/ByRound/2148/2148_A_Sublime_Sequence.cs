using System;

public class HelloWorld
{
    public static void Main(string[] args)
    {
        int T = int.Parse(Console.ReadLine());
        for(int i=0;i<T;i++){
            int[] input = Array.ConvertAll(Console.ReadLine().Split(),int.Parse);
            int x = input[0];
            int y = input[1];
            int ans = 0;
            if(y%2==1){
                ans = x;
            }
            Console.WriteLine(ans);
        }
    }
}