using System;

using System.Linq;


namespace Zd1Olimp
{
    class Program
    {
        static void Main(string[] args)
        {
            int t = Convert.ToInt32(Console.ReadLine());

            int[][] komnati = new int[t] [];
int[] [] otvet = new int[t] [];

            for (int i = 0; i < t; i++)
            {
                int n = Convert.ToInt32(Console.ReadLine());
                

               komnati [i] =  Console.ReadLine().Split().Select(int.Parse).ToArray();
               
                otvet[i] = new int[n];


                
                for (int i1 = 0; i1 < n; i1++)
                {
                    if (i1 % 2 == 1)
                    {
                        otvet[i][i1] = -1 * komnati[i][i1 - 1];
                    }
                    else
                    {
                        otvet[i][i1] = komnati[i][i1 + 1];
                    }
                }
            }

            
            foreach (int [] i3 in otvet)
            {
                string otv = "";
                foreach (int i in i3)
                {
                    otv += i.ToString() + " ";

                }

                Console.WriteLine(otv);
             
            }

          
        }


    }
}
    
