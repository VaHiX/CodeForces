using System;
class demo
{
    static void Main()
    {
        int q;
        q = int.Parse(Console.ReadLine());
        long sum = 0;
        while (q > 0)
        {
            q--;
            string a;
            long b;
            a = Console.ReadLine();
            string[] parts = a.Split(' ');
            if (parts.Length == 2 && parts[0] == "P" && long.TryParse(parts[1], out b))
            {
                sum += b;
            }
            else if (parts.Length == 2 && parts[0] == "B" && long.TryParse(parts[1], out b))
            {
                if (sum >= b)
                {
                    Console.WriteLine("NO");
                    sum -= b;
                }
                else
                {
                    Console.WriteLine("YES");
                    sum = 0;
                }
            }
            else
            {
                Console.WriteLine("Định dạng đầu vào không hợp lệ");
            }
        }
    }
}