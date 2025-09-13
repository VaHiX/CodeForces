using static System.Console;
int TestsCount = int.Parse(ReadLine());

int[] Coin = new int[TestsCount];

for (int i = 0; i < TestsCount; i++)
{
    int[] Data = ReadLine().Split(' ').Select(int.Parse).ToArray();
    int n = Data[0];
    int c = Data[1];

    List<long> Trashes = ReadLine().Split(' ').Select(long.Parse).ToList();
    while (Trashes.Count > 0)
    {
        int sus = 0;
        bool cool = false;
        for (int j = 0; j < Trashes.Count; j++)
        {
            if (Trashes[j] <= c)
            {
                cool = true; sus = j; break;
            }
        }
        if (!cool)
        {
            Coin[i] += Trashes.Count;
            break;
        }

        for (int j = 0; j < Trashes.Count; j++)
        {
            if (Trashes[j] > Trashes[sus] && Trashes[j] <= c)
            {
                sus = j;
            }
        }

        Trashes.RemoveAt(sus);
        for (int j = 0; j < Trashes.Count; j++)
        {
            Trashes[j] *= 2;
        }
    }
}

foreach (int n in Coin)
{
    WriteLine(n);
}












/*
for (int i = 1; i <= TestsCount; i++)
{
    int[] Data = ReadLine().Split(' ').Select(int.Parse).ToArray();
    int n = Data[0];
    int c = Data[1];

    long[] Trashes = ReadLine().Split(' ').Select(long.Parse).ToArray();

    while (Trashes.Sum() > 0)
    {
        bool cool = false;
        for (int j = 0; j < n; j++)
        {
            if(Trashes[j] > 0 && Trashes[j] <= c)
            {
                cool = true; break;
            }
        }
        if (!cool)
        {
            for(int j = 0;j < n; j++)
            {
                if(Trashes[j] > 0)
                {
                    Coin[i-1]++;
                }
            }

            break;
        }

        int sus = 0;
        for (int j = 1; j < n; j++)
        {
            if (Trashes[j] > Trashes[sus] && Trashes[j] <= c)
            {
                sus = j;
            }
        }

        Trashes[sus] = 0;

        for (int j = 0; j < n; j++)
        {
            Trashes[j] *= 2;
        }
    }
}

foreach (int n in Coin)
{
    WriteLine(n);
}
*/