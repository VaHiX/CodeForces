using System.Data;
using System.Net.Http.Headers;
using System.Runtime.Intrinsics.Arm;
using static System.Console;

int t = int.Parse(Console.ReadLine());
while (t-- > 0)
{
    int n = int.Parse(Console.ReadLine());
    int[] nums = ReadLine().Split(' ').Select(int.Parse).ToArray();
    Array.Sort(nums);
    long ans = 0;
    for(int i = nums.Length - 1; i >= 0; i -=2)
    {
        ans += nums[i];
    }

    WriteLine(ans);
}