using System.Data;
using System.Net.Http.Headers;
using static System.Console;

int t = int.Parse(ReadLine());
while (t-- > 0)
{
    int n = int.Parse(ReadLine());
    int[] nums = ReadLine().Split(' ').Select(int.Parse).ToArray();

    int ans = 1;
    int last = nums[0];
    for(int i = 1;  i < nums.Length; i++)
    {
        if (nums[i] > nums[i - 1] + 1) { last = nums[i]; ans++; }
        else if (nums[i] == nums[i - 1] + 1 && last != nums[i-1]) { last = nums[i]; ans++; }
    }

    WriteLine(ans);
}