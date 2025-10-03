using System;
using System.Linq;

class Program
{
    // Custom input function for reading a line
    static string MyInput()
    {
        return Console.ReadLine().Trim();
    }

    // Function to count elements in the range [x, y]
    static long CountEle(long[] arr,int imax, long x, long y)
    {   

        long i = Array.BinarySearch(arr, x);
        if (i < 0) i = ~i;
        if ( i< arr.Length  && arr[i] ==x )
        {
            while (i>0){
                if (arr[i-1] ==x ) {i = i-1;}
                else break;
            }
        }
        long j = Array.BinarySearch(arr, y);


        if (j < 0) j = ~j;
        
        {while (j < arr.Length && arr[j] == y ) j++;}

        //Console.WriteLine("lower" + i);Console.WriteLine("higher" + j);

        return Math.Max(imax, j) - Math.Max(imax,i);
    }

    // Main function to calculate the number of pairs
    static void PairsOpt(long[] list, long x, long y)
    {
        long count = 0;
        int i = 0;
        Array.Sort(list); 
        long sn = list.Sum(); 
        while (i < list.Length - 1)
        {
            long k = sn - list[i];
            long c1 = CountEle(list,i+1, k - y, k - x);
            count += c1;
            i++;
        }
        Console.WriteLine(count);
    }

    // Main execution
    static void Main(string[] args)
    {
        // Number of test cases
        long T = long.Parse(MyInput());

        // Iterate over each test case
        for (long t = 0; t < T; t++)
        {
            // Read input for each test case
            long[] list1 = MyInput().Split().Select(long.Parse).ToArray();
            long[] list2 = MyInput().Split().Select(long.Parse).ToArray();

            // Call the function with the provided list and range
            PairsOpt(list2, list1[1], list1[2]);
        }
    }
}
