
using System;
using System.Linq;
using System.Runtime.CompilerServices;
using static System.Net.Mime.MediaTypeNames;

public class MysteriousScript
{
    public static void Main()
    {
        string z = Console.ReadLine();

        string[] y = z.Split(' ');

        string A = y[0];
        string B = y[1];

        double a = 0;
        double b = 0;

        char[] A1 = A.ToCharArray();
        char[] B1 = B.ToCharArray();

        string[] A2 = new string[A.Length];
        string[] B2 = new string[B.Length];

        for (int i = 0; i < A.Length; i++)
        {
            A2[i] = A1[i].ToString();
        }
        for (int i = 0; i < B.Length; i++)
        {
            B2[i] = B1[i].ToString();
        }

        int[] a1 = new int[A.Length];
        int[] b1 = new int[B.Length];

        for (int i = 0; i < A.Length; i++)
        {
            if (A2[i] == "l")
            {
                if (A2[i + 1] == "a")
                {
                    a1[i] = 9;
                }
                else if (A2[i + 1] == "e")
                {
                    a1[i] = 1;
                }
                else if (A2[i + 1] == "o")
                {
                    a1[i] = 2;
                }
            }
            else if (A2[i] == "h")
            {
                if (A2[i + 1] == "a")
                {
                    a1[i] = 3;
                }
                else if (A2[i + 1] == "e")
                {
                    a1[i] = 4;
                }
                else if (A2[i + 1] == "o")
                {
                    a1[i] = 5;
                }
            }
            else if (A2[i] == "t")
            {
                if (A2[i + 1] == "a")
                {
                    a1[i] = 6;
                }
                else if (A2[i + 1] == "e")
                {
                    a1[i] = 7;
                }
                else if (A2[i + 1] == "o")
                {
                    a1[i] = 8;
                }
            }
        }
        for (int i = 0; i < B.Length; i++)
        {
            if (B2[i] == "l")
            {
                if (B2[i + 1] == "a")
                {
                    b1[i] = 9;
                }
                else if (B2[i + 1] == "e")
                {
                    b1[i] = 1;
                }
                else if (B2[i + 1] == "o")
                {
                    b1[i] = 2;
                }
            }
            else if (B2[i] == "h")
            {
                if (B2[i + 1] == "a")
                {
                    b1[i] = 3;
                }
                else if (B2[i + 1] == "e")
                {
                    b1[i] = 4;
                }
                else if (B2[i + 1] == "o")
                {
                    b1[i] = 5;
                }
            }
            else if (B2[i] == "t")
            {
                if (B2[i + 1] == "a")
                {
                    b1[i] = 6;
                }
                else if (B2[i + 1] == "e")
                {
                    b1[i] = 7;
                }
                else if (B2[i + 1] == "o")
                {
                    b1[i] = 8;
                }
            }
        }

        a1 = a1.Where(x => x != 0).ToArray();
        b1 = b1.Where(x => x != 0).ToArray();

        for (int i = 0; i < a1.Length; i++)
        {
            if (a1[i] == 9)
            {
                a1[i] = 0;
            }
        }
        for (int i = 0; i < b1.Length; i++)
        {
            if (b1[i] == 9)
            {
                b1[i] = 0;
            }
        }

        double aplusb10 = 0;

        for (int i = 0; i < a1.Length; i++)
        {
            double p = Math.Pow(9, a1.Length - i - 1);
            a = a + (a1[i] * p);
        }
        for (int i = 0; i < b1.Length; i++)
        {
            double p = Math.Pow(9, b1.Length - i - 1);
            b = b + (b1[i] * p);
        }

        aplusb10 = a + b;

        static string tentonine(int n)
        {
            if (n == 0) return "0";

            char[] digits = new char[32];
            int i = 0;

            while (n > 0)
            {
                digits[i++] = (char)('0' + (n % 9));
                n /= 9;
            }

            Array.Reverse(digits, 0, i);
            return new string(digits, 0, i);
        }

        double aplusb9 = double.Parse(tentonine(int.Parse(aplusb10.ToString())));

        char[] ab9 = aplusb9.ToString().ToCharArray();

        string[] AB9 = new string[ab9.Length];

        for (int i = 0; i < ab9.Length; i++)
        {
            AB9[i] = ab9[i].ToString();
        }

        string result = "";

        for (int i = 0; i < ab9.Length; i++)
        {
            if (AB9[i] == "0")
            {
                result = result + "la";
            }
            else if (AB9[i] == "1")
            {
                result = result + "le";
            }
            else if (AB9[i] == "2")
            {
                result = result + "lon";
            }
            else if (AB9[i] == "3")
            {
                result = result + "sha";
            }
            else if (AB9[i] == "4")
            {
                result = result + "she";
            }
            else if (AB9[i] == "5")
            {
                result = result + "shon";
            }
            else if (AB9[i] == "6")
            {
                result = result + "ta";
            }
            else if (AB9[i] == "7")
            {
                result = result + "te";
            }
            else if (AB9[i] == "8")
            {
                result = result + "ton";
            }
        }

        Console.WriteLine(result + "s");
    }
}







