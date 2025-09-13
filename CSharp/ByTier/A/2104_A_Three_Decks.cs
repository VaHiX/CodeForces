using System;
using System.Numerics;

class JustLearning
{
   

    static void Main(string[] args)
    {
        int t = Convert.ToInt32(Console.ReadLine());

        while (t > 0)
        {
            string[] numset = Console.ReadLine().Split();
            int[] intnumset = Array.ConvertAll(numset,int.Parse);
            int cardleft1stcheck = intnumset[2] - (intnumset[1] - intnumset[0]);
            if (cardleft1stcheck < intnumset[1])
            {
                Console.WriteLine("NO");
            }
            else if ((cardleft1stcheck - intnumset[1]) % 3 == 0)
            {
                Console.WriteLine("YES");
            }
            else
            {
                Console.WriteLine("NO");
            }
            
            t--;
        }

       
    }





}