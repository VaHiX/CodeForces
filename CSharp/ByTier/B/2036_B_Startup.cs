// Online C# Editor for free
// Write, Edit and Run your C# code using C# Online Compiler

using System;
using System.Collections.Generic;
using System.Linq;
public class HelloWorld
{
    static void program()
    {
        string[] str = Console.ReadLine().Split();
        int a = Convert.ToInt32(str[0]), b = Convert.ToInt32(str[1]);
        Dictionary<int, int> map = new Dictionary<int, int>();
        for(int i = 0; i < b; ++i)
        {
             string[] input = Console.ReadLine().Split();
             int c = Convert.ToInt32(input[0]), d = Convert.ToInt32(input[1]);
            if(map.ContainsKey(c) == false) {map.Add(c, d);}
            else{map[c] += d;}
        }
            int sum = 0, f = 0;
            foreach (var pair in map.OrderBy(pair => pair.Value).Reverse())
        {
            if(f++ < a){
            sum += pair.Value;
            }
        }
        Console.WriteLine(sum);
        
    }
    public static void Main()
    {
        int t = Convert.ToInt32(Console.ReadLine());
        while(t-- > 0)
        {
            program();
        }
    }
    
}