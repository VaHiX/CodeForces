using System.Collections.Generic;
using System;
using System.Collections;
using System.Linq;

public class Program
{
    public static void Main()
    {

        float[] nums = Console.ReadLine().Split(' ').Select(x => float.Parse(x)).ToArray();
        float a = nums[0];
        float b = nums[1];
        float delta = a * 3 - b;
        float[] ans;
        if (a >= 0 && b < 0)
            ans = new[] { b - delta, b, Math.Abs(b) + 2 * delta };
        else if (delta < 0)
            ans = new[] { b, b, -b + delta };
        else
            ans = new[] { b - 2 * b, b, b + delta };
        Console.WriteLine(3);
        foreach (var elem in ans)
            Console.Write(elem + " ");
    }
}