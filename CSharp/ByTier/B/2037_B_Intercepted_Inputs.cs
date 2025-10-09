using System;
using System.Linq;
public class Solutions
{
    public static void Main()
    {
        int t= int.Parse(Console.ReadLine());

        for (int i = 0; i < t; i++)
        {
            int inp = int.Parse(Console.ReadLine());

            int[] c = new int[inp + 1];

            string s = Console.ReadLine();

            int[] arr = s.Split(' ').Select(int.Parse).ToArray();

            for (int l = 0; l < arr.Length; l++)
            {
                c[arr[l]]++;
            }

            inp -= 2;


            for (int k = 1; k <= inp; k++)
            {
                if (inp % k == 0)
                {
                    if (k * k == inp)
                    {
                        if (c[k] >= 2)
                        {
                            Console.WriteLine($"{k} {k}");
                            break;
                        }
                    }
                    else
                    {
                        if (c[k] > 0 && c[inp / k] > 0)
                        {
                            Console.WriteLine($"{k} {inp/k}");
                            break;
                        }
                    }
                }
            }

        }
    }
}
