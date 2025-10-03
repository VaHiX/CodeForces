using System;
using static System.Math;


namespace matsu
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int n = Convert.ToInt32(Console.ReadLine());
            
            for ( int i = 0; i < n; ++ i )
            {
                int x = 0, y = 0, z = 0;
               
                String s = Console.ReadLine() , ano = "";
                for ( int j = 0; j < s.Length; ++j)
                {
                    if ( s[ j ] == ' ' )
                    {
                        x = Convert.ToInt32(ano);
                        ano = "";
                        continue;
                    }
                    ano += s[j];
                }

                y = Convert.ToInt32(ano);

                if ( x >= y )
                {
                    z = x;
                }

                else if ( y - x <= x )
                {
                    z = x - (y - x);
                }

                Console.WriteLine( Math.Max ( 0 , z ) );
            }

            //Console.ReadKey();
        }
    }
}
