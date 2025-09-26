var samples = int.Parse(Console.ReadLine());

for (int i = 0; i < samples; i++)
{
    var input = Console.ReadLine().Split(' ');
    var n = int.Parse(input[0]);
    var x = int.Parse(input[1]);
    var numbers = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();

    var firstIdx = -1;
    var lastIdx = 0;

    for (int k = 0; k < n; k++)
    {
        if (numbers[k] == 1)
        {
            if (firstIdx == -1) firstIdx = k;
            lastIdx = k;
        }
    }

    var maxLen = lastIdx - firstIdx + 1;
    if (maxLen <= x)
    {
        Console.WriteLine("YES");
    }
    else
    {
        Console.WriteLine("NO");
    }
}