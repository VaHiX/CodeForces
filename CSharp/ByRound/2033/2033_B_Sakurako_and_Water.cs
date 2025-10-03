using System;

namespace Div3_1
{
    class Program
    {
        static void addOneToEachElementInMainDiagonal(int[] arr, int n, int ele, int val)
        {
            // add 1 to each element in the (main diagonal of element ele)
            int eley = ele % n;
            int elex = ele / n;
            int x, y;
            int min = Math.Min(elex, eley);
            x = elex - min;
            y = eley - min;
            while (x < n && y < n)
            {
                arr[(x * n) + y] += val;
                x++;
                y++;
            }

        }
        static void Qustion()
        {
            int magicNumber = 0;
            // n = number of elements in the array row
            int n = int.Parse(Console.ReadLine());

            // s = size of the array
            int s = n * n;

            // create an array of size s
            int[] arr = new int[s];

            // read the array elements line by line
            for (int i = 0; i < n; i++)
            {
                string[] line = Console.ReadLine().Split(' ');
                for (int j = 0; j < n; j++)
                {
                    arr[i * n + j] = int.Parse(line[j]);
                }
            }

            // make all elements in array positive
            for (int i = 0; i < s; i++)
            {
                if (arr[i] < 0)
                {
                    int need = -1 * arr[i];
                    addOneToEachElementInMainDiagonal(arr, n, i, need);
                    magicNumber += need;
                }
            }
            Console.WriteLine(magicNumber);
        }
        static void Main(string[] args)
        {
            int t = int.Parse(Console.ReadLine());
            while (t-- > 0)
            {
                Qustion();
            }
        }
    }
}