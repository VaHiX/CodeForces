using System;
using System.Linq;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        string[] elements = Console.ReadLine().Split();
        int equalIdx = Array.IndexOf(elements, "=");
        int n = int.Parse(elements[equalIdx + 1]);
        string[] leftPart = elements.Take(equalIdx).ToArray();

        List<char> operators = new List<char>();
        int variablesCount = 0;
        
        foreach (string elem in leftPart)
        {
            if (elem == "?")
            {
                variablesCount++;
            }
            else if (elem == "+" || elem == "-")
            {
                operators.Add(elem[0]);
            }
        }

        List<int> s = new List<int> { 1 };
        foreach (char op in operators)
        {
            s.Add(op == '+' ? 1 : -1);
        }

        int sumMax = 0, sumMin = 0;
        foreach (int si in s)
        {
            if (si == 1)
            {
                sumMax += n * si;
                sumMin += 1 * si;
            }
            else
            {
                sumMax += 1 * si;
                sumMin += n * si;
            }
        }

        if (n < sumMin || n > sumMax)
        {
            Console.WriteLine("Impossible");
        }
        else
        {
            int delta = sumMax - n;
            List<int> a = s.Select(si => si == 1 ? n : 1).ToList();

            for (int i = 0; i < a.Count; i++)
            {
                if (delta <= 0) break;
                int si = s[i];
                if (si == 1)
                {
                    int maxReduce = a[i] - 1;
                    int take = Math.Min(delta, maxReduce);
                    a[i] -= take;
                    delta -= take;
                }
                else
                {
                    int maxIncrease = n - a[i];
                    int take = Math.Min(delta, maxIncrease);
                    a[i] += take;
                    delta -= take;
                }
            }

            if (delta != 0)
            {
                Console.WriteLine("Impossible");
            }
            else
            {
                bool valid = a.All(num => num >= 1 && num <= n);
                if (!valid)
                {
                    Console.WriteLine("Impossible");
                }
                else
                {
                    List<string> output = new List<string>();
                    int currentVar = 0;
                    
                    foreach (string elem in leftPart)
                    {
                        if (elem == "?")
                        {
                            output.Add(a[currentVar].ToString());
                            currentVar++;
                        }
                        else
                        {
                            output.Add(elem);
                        }
                    }
                    output.Add("=");
                    output.Add(n.ToString());
                    
                    Console.WriteLine("Possible");
                    Console.WriteLine(string.Join(" ", output));
                }
            }
        }
    }
}