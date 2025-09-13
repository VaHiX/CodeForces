using System.Globalization;
using static System.Console;

int Tests = int.Parse(ReadLine());
string[] Result = new string[Tests];

for (int i = 0; i < Tests; i++)
{
    int n = int.Parse(ReadLine());
    int[] Numbers = ReadLine().Split(' ').Select(int.Parse).ToArray();

    bool cool = true;
    int min = Numbers[0];
    for(int j = 1; j < n; j++)
    {
        if(Numbers[j] >= 2*min)
        {
            cool = false; break;
        }
        if(Numbers[j] < min)
        {
            min = Numbers[j];
        }
    }

    if (cool) { Result[i] = "Yes"; }
    else
    {
        Result[i] = "No";
    }
}

foreach (string result in Result)
{
    WriteLine(result);
}