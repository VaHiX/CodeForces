using System;

public class HelloWorld
{
    public static void Main(){
        int a = int.Parse(Console.ReadLine());
        for(int i = 0; i < a ; i++){
            long num = long.Parse(Console.ReadLine());
            Console.WriteLine(nn(num));
        }
    }
    public static long nn(long n)
    {
        if( n <= 3){
            return 1;
        }
        return 2*nn(n / 4);
            
        }
    }
