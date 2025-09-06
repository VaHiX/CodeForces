using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class Program
    {
        static void Main(string[] args)
        {
               int i=int.Parse(Console.ReadLine());
            string n;
          for(var j=0;j<i;j++)
            {
                int coun = 0;
                 n=Console.ReadLine();
                for(var c=0;c<n.Length-1;c++)
                {
                    
                    if (n[c] == n[c+1])
                    {
                        coun++;
                        
                          
                    }
                }
                Console.WriteLine(coun>0?1:n.Length);
            }
        }
    }
}
