using System;
using System.Collections.Generic;

class Program
{
    const int MOD = 998244353;

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());

        // n يمكن أن يصل إلى 200000، لذا نحتاج إلى حساب القوى حتى قيمة أكبر قليلاً
        const int MAXP = 200005;
        long[] pow2 = new long[MAXP];
        long[] invPow2 = new long[MAXP];

        // حساب القوى (2^i) % MOD مسبقًا
        pow2[0] = 1;
        for (int i = 1; i < MAXP; i++)
        {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        // حساب معكوس القوى (2^(-i)) % MOD باستخدام خاصية MOD الأولي
        long inv2 = 499122177; // لأن (2 * 499122177) % MOD == 1
        invPow2[0] = 1;
        for (int i = 1; i < MAXP; i++)
        {
            invPow2[i] = (invPow2[i - 1] * inv2) % MOD;
        }

        // معالجة كل حالة اختبار
        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine());
            int[] a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);

            long ans = 0;
            long sumOnes = 0; // مجموع أوزان كل 1 تمت مشاهدته
            int countOnes = 0; // عدد الـ 1 التي تمت مشاهدتها
            int count2 = 0;    // عدد الـ 2 التي تمت مشاهدتها

            // المرور على المصفوفة من اليسار إلى اليمين
            for (int i = 0; i < n; i++)
            {
                if (a[i] == 1)
                {
                    // لكل 1، نسجل وزنه كـ 2^(-count2) % MOD
                    sumOnes = (sumOnes + invPow2[count2]) % MOD;
                    countOnes++;
                }
                else if (a[i] == 2)
                {
                    count2++;
                }
                else if (a[i] == 3)
                {
                
                    long contrib = ((pow2[count2] * sumOnes) % MOD - countOnes) % MOD;
                    if (contrib < 0) contrib += MOD;
                    ans = (ans + contrib) % MOD;
                }
            }

            Console.WriteLine(ans);
        }
    }
}