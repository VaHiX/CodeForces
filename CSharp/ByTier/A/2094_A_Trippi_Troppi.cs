using System;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine()); // قراءة عدد الحالات

        for (int i = 0; i < t; i++)
        {
            string[] words = Console.ReadLine().Split(); // قراءة الثلاث كلمات

            // دمج أول حرف من كل كلمة
            string modernName = words[0][0] + "" + words[1][0] + "" + words[2][0];

            Console.WriteLine(modernName); // طباعة النتيجة
        }
    }
}
