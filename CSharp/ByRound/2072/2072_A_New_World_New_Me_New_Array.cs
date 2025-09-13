using System;
using System.Collections.Generic;
 
class Solution
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            var inputs = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
            var n = inputs[0];
            var k = Math.Abs(inputs[1]);
            var p = inputs[2];

            int ceilingResult = (k / p) + (k % p == 0 ? 0 : 1);

            if(ceilingResult <= n) Console.WriteLine(ceilingResult);
            else Console.WriteLine("-1");
           
        }
    }
}