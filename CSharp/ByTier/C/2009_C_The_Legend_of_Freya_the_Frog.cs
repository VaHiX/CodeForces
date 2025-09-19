using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Concurrent;

class Program
{
    static void Main()
    {        
        int fieldName = int.Parse(Console.ReadLine());

        for(int i = 0; i < fieldName; i++)
        {
            string[] input = Console.ReadLine().Split();
            int x = int.Parse(input[0]);
            int y = int.Parse(input[1]);
            int k = int.Parse(input[2]);
            
            int xSteps = 0;
            int ySteps = 0;
            
            if(x % k == 0)
                xSteps = x / k;
            else
                xSteps = x / k + 1;
                
            if(y % k == 0)
                ySteps = y / k;
            else
                ySteps = y / k + 1;
                
            if(xSteps > ySteps)
                Console.Write(Math.Max(xSteps, ySteps) * 2 - 1);
            else
                Console.Write(Math.Max(xSteps, ySteps) * 2);
            
            Console.Write("\n");
        }

        //Console.WriteLine("Hello, World!");
    }

    static int ExampleMethod(int exampleParameter)
    {        
        exampleParameter = 0;

        return exampleParameter;
    }
}