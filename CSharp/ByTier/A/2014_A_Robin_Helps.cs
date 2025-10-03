using System;

class Program
{
    static void Main()
    {
        // 读取测试用例数量
        int t = int.Parse(Console.ReadLine());
        
        for (int i = 0; i < t; i++)
        {
            // 读取怪物数量和杀怪物的评判标准
            string[] inputs = Console.ReadLine().Split(' ');
            int n = int.Parse(inputs[0]);
            int k = int.Parse(inputs[1]);

            // 读取每个怪物身上的金币数量
            string[] coinsInput = Console.ReadLine().Split(' ');
            int[] coins = new int[n];
            for (int j = 0; j < n; j++)
            {
                coins[j] = int.Parse(coinsInput[j]);
            }

            int totalCoins = 0; // 细胞人当前拥有的金币数量
            int helpCount = 0;  // 帮助过的怪物数量

            for (int j = 0; j < n; j++)
            {
                if (coins[j] >= k)
                {
                    // 杀掉怪物并获得金币
                    totalCoins += coins[j];
                }
                else if (coins[j] == 0)
                {
                    if (totalCoins > 0)
                    {
                        // 给没有金币的怪物一枚金币
                        totalCoins--;
                        helpCount++;
                    }
                }
            }

            // 输出帮助过的怪物数量
            Console.WriteLine(helpCount);
        }
    }
}