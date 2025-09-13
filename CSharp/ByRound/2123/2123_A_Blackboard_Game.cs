
using System;
class HelloWorld {
  static void Main() {
    int x = 0;
    int t = 0;
    int sum = 0;
    x = int.Parse(Console.ReadLine());
    
    for (int i=0; i<x; i++)
    {
        sum = 0;
        t = int.Parse(Console.ReadLine());
        if (t % 2 != 0) Console.WriteLine("Alice");
        else{
            for (int j=0; j<t; j++)
            {
                sum += j;
            }
            if (sum % 2 != 0)
            {
                Console.WriteLine("Alice");
            }
            else Console.WriteLine("Bob");
        }
    }
  }
}