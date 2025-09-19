﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace CodeForces
{
    class Program
    {
        static void Main(string[] args)
        {
            var m = Int32.Parse(Console.ReadLine());
            var arr = Console.ReadLine().Split(' ');
            var h1 = Int32.Parse(arr[0]);
            var a1 = Int32.Parse(arr[1]);
            arr = Console.ReadLine().Split(' ');
            var x1 = Int32.Parse(arr[0]);
            var y1 = Int32.Parse(arr[1]);
            arr = Console.ReadLine().Split(' ');
            var h2 = Int32.Parse(arr[0]);
            var a2 = Int32.Parse(arr[1]);
            arr = Console.ReadLine().Split(' ');
            var x2 = Int32.Parse(arr[0]);
            var y2 = Int32.Parse(arr[1]);
            Console.WriteLine(GetMinTime(m,h1,a1,x1,y1,h2,a2,x2,y2));
        }
        
        private static long GetMinTime(int[] arr)
        {
            return GetMinTime(
                arr[0],
                arr[1],
                arr[2],
                arr[3],
                arr[4],
                arr[5],
                arr[6],
                arr[7],
                arr[8]
            );
        }

        private static long BruteGetMinTime(int[] arr)
        {
            return BruteGetMinTime(
                arr[0],
                arr[1],
                arr[2],
                arr[3],
                arr[4],
                arr[5],
                arr[6],
                arr[7],
                arr[8],
                arr[9]
            );
        }
        private static long GetMinTime(int m, int h1, int a1, int x1, int y1, int h2, int a2, int x2, int y2)
        {
            var res1 = GetRes(h1,a1, x1, y1, m);
            var res2 = GetRes(h2,a2, x2, y2, m);

            if (res1.Item1 == -1 || res2.Item1 == -1)
            {
                return -1;
            }
            if (res1.Item1 ==0 && res2.Item1 == 0)
            {
                return res1.Item2 == res2.Item2 ? res1.Item2 : -1;
            }

            if (res1.Item1 == 0)
            {
                if (res1.Item2 >= res2.Item2 && (res1.Item2 - res2.Item2) % res2.Item1 == 0)
                    return res1.Item2;
                else
                    return -1;
            }

            if (res2.Item1 == 0)
            {
                if (res2.Item2 >= res1.Item2 && (res2.Item2 - res1.Item2) % res1.Item1 == 0)
                    return res2.Item2;
                else
                    return -1;
            }

            int diff = res2.Item2 - res1.Item2;
            if (diff == 0) return res1.Item2;


            // k1 * res1.Item1 +  k2 * res2.Item1 = res2.Item2 - res1.Item2;
            // k1 >=0 && k2<=0
            long k1, k2;
            if (res1.Item1 >= res2.Item1)
            {
                (k1,k2) = EXGCD(res1.Item1 , res2.Item1);
            }
            else
            {
                (k2,k1) = EXGCD(res2.Item1 , res1.Item1);
            }
            var gcd = k1 * res1.Item1 + k2 * res2.Item1;
            if (diff % gcd !=0) return -1;

            k1 *= (diff / gcd);
            k2 *= (diff / gcd);
        	
            var c1 = res1.Item1 / gcd;
            var c2 = res2.Item1 / gcd;
            if (k1 < 0)
            {
                var append = ((-k1 - 1) /c2 + 1) * c2;
                k1 += append;
                k2 -= append * c1 / c2;
            }
            else
            {
                var remove = k1 /c2 * c2;
                k1 -= remove;
                k2 += remove * c1 / c2;
            }

            if (k2 > 0)
            {
                var remove = ((k2 - 1) /c1 + 1) * c1;
                k2 -= remove;
                k1 += remove * c2 / c1;
            }

            return k1 * res1.Item1 + res1.Item2;
        }

        private static (int,int) GetRes(int h, int a, int x, int y, int m)
        {
            var map = new Dictionary<int,int>();
            var cnt = 0;
            while(!map.ContainsKey(h))
            {
                map[h] = cnt;
                h = (int)(((long)x * h + y) % m);
                cnt++;
            }

            if (!map.ContainsKey(a)) return (-1,-1);

            if (map[a] < map[h]) return (0, map[a]);

            return (cnt - map[h], map[a]);

        }

        // num0 >= num1
        private static (long, long) EXGCD(int num0, int num1)
        {
            var num2 = num0 % num1;
            if (num2 == 0) return (0,1);

            //  a * num0 + b * num1 = num2
            var a = 1;
            var b = - num0 / num1;

            var (a1,b1) = EXGCD(num1, num2);

            //  a1 * num1 + b1 * num2 = gcd

            // a * b1 * num0 + (a1 + b * b1) num1 = gcd

            return ( a * b1, a1 + b * b1);            
        }
            


        private static (int,int,int,int,int,int,int,int,int) GetTestData(Random random)
        {
            var m = random.Next(10) + 2;
            return (m, 
                random.Next(m),
                random.Next(m),
                random.Next(m),
                random.Next(m),
                random.Next(m),
                random.Next(m),
                random.Next(m),
                random.Next(m));
        }



        private static long BruteGetMinTime(int m, int h1, int a1, int x1, int y1, int h2, int a2, int x2, int y2, int limit)
        {
            for(var i = 0;i<=limit;i++)
            {
                if (h1 == a1 && h2 == a2) return i;
                h1 = (h1 * x1 + y1) % m;
                h2 = (h2 * x2 + y2) % m;
            }

            return -1;
        }

        private static void Test()
        {
            var random = new Random(Environment.TickCount);
            for(var i = 0;i<100000;i++)
            {
                var (m,h1,a1,x1,y1,h2,a2,x2,y2) = GetTestData(random);
                var res0 = (int)GetMinTime(m,h1,a1,x1,y1,h2,a2,x2,y2);
                var limit = res0 == -1 ? m * m : res0;
                var res1 = BruteGetMinTime(m,h1,a1,x1,y1,h2,a2,x2,y2, limit);
                if(res0!=res1) 
                {
                    Console.WriteLine($"{res0} {res1}");
                    Console.WriteLine($"{m} {h1} {a1} {x1} {y1} {h2} {a2} {x2} {y2}");
                    break;
                }
            }
            
        }
        
 
        

        
 
    }
}