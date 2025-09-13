using System;
using System.Linq;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            int n = (int.Parse)(Console.ReadLine());
            //var parts = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
            var nums = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
            //Array.Sort(nums);

            long ans = 0;
            for (int i = 0; i < n - 2; i++)
            {
                for (int j = i + 1; j < n - 1; j++)
                {
                    int val = nums[i] + nums[j];
                    int lower = GetLowerBound(nums, j + 1, n - 1, val);
                    if (lower == j) continue;
                    int k = BinarySearch(nums,val,j+1,lower,nums[n-1] );
                    //if (k == lower) continue;
                    if (k <= lower)
                    {
                        ans += lower - k + 1;
                    }
                    //ans += lower-k+1;
                }
            }
            
            Console.WriteLine(ans);
        }
    }

    static int GetLowerBound(int[] nums, int low, int high, int tar)
    {
        int ans = low - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (nums[mid] < tar)
            {
                ans = mid;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return ans;
    }
    // 11
    // 27 32 35 37 45 57 65 65 71 87 96
   //find lower bound
    static int BinarySearch(int[] nums, int sum, int low, int high, int max)
    {
        int ans = high+1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (nums[mid] + sum > max)
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }
}