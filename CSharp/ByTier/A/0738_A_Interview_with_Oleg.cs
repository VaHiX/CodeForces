using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace First
{
    class Program
    {
        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            string s = Console.ReadLine();
            string ans = "";
            for (int i = 0; i < n; i++)
            {
                if (s[i] == 'o')
                {
                    bool b = false;
                    bool br = false;
                    if (i + 2 >= n)
                    {
                        ans += s[i];
                    }
                    else
                    {
                        while (i + 2 < n)
                        {
                            if (s[i + 1] == 'g' && s[i + 2] == 'o')
                            {
                                b = true;
                                i += 2;
                            }
                            else if (b)
                            {
                                ans += "***";
                                br = true;
                                break;
                            }
                            else
                            {
                                ans += s[i];
                                br = true;
                                break;
                            }
                        }
                        if (i + 2 >= n && !br && b)
                        {
                            ans += "***";
                        }
                    }
                }
                else
                    ans += s[i];
            }
            Console.WriteLine(ans);
        }
    }
}
