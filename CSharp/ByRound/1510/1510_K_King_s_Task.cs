using System;
using System.Linq;

namespace CompetCSharp
{
    class Program
    {
        public static void Main()
        {
            int n = int.Parse(Console.ReadLine());
            string[] numbers = Console.ReadLine().Split(" ");
            int[] array = new int[n * 2];
            for (int i = 0; i < n * 2; i++) {
                array[i] = int.Parse(numbers[i]);
            }
            if (isSorted(array))
            {
                Console.WriteLine("0");
                return;
            }
            int[] array1 = new int[n * 2];
            int[] array2 = new int[n * 2];
            Array.Copy(array, array1, n * 2);
            Array.Copy(array, array2, n * 2);
            int a = SwappingFirstThanSecond(array1, array, n);
            int b = SwappingSecondThanFirst(array2, array, n);
            if (a != -1 && b != -1)
            {
                Console.WriteLine(Math.Min(a, b));
            } else if (a == -1 && b == -1)
            {
                Console.WriteLine("-1");
            } else
            {
                Console.WriteLine(Math.Max(a, b));
            }
        }

        public static int SwappingFirstThanSecond(int[] array, int[] sourcearray, int n)
        {
            int steps = 0;
            while (true)
            {
                SwapFirst(array, n);
                steps++;
                if (Enumerable.SequenceEqual(array, sourcearray))
                {
                    return -1;
                }
                if (isSorted(array))
                {
                    return steps;
                }
                SwapSecond(array, n);
                steps++;
                if (Enumerable.SequenceEqual(array, sourcearray))
                {
                    return -1;
                }
                if (isSorted(array))
                {
                    return steps;
                }
            }
        }

        public static int SwappingSecondThanFirst(int[] array, int[] sourcearray, int n)
        {
            int steps = 0;
            while (true)
            {
                SwapSecond(array, n);
                steps++;
                if (Enumerable.SequenceEqual(array, sourcearray))
                {
                    return -1;
                }
                if (isSorted(array))
                {
                    return steps;
                }
                SwapFirst(array, n);
                steps++;
                if (Enumerable.SequenceEqual(array, sourcearray))
                {
                    return -1;
                }
                if (isSorted(array))
                {
                    return steps;
                }
            }
        }

        public static bool isSorted(int[] a)
        {
            int i = a.Length - 1;
            if (i <= 0) return true;
            if ((i & 1) > 0) { if (a[i] < a[i - 1]) return false; i--; }
            for (int ai = a[i]; i > 0; i -= 2)
                if (ai < (ai = a[i - 1]) || ai < (ai = a[i - 2])) return false;
            return a[0] <= a[1];
        }

        public static void SwapFirst(int[] array, int n)
        {
            for (int i = 0; i < n * 2; i += 2)
            {
                int temp = array[i];
                int temp2 = array[i + 1];
                array[i] = temp2;
                array[i + 1] = temp;
            }
        }

        public static void SwapSecond(int[] array, int n)
        {
            for (int i = 0; i < n; i++)
            {
                int temp = array[i];
                int temp2 = array[n + i];
                array[i] = temp2;
                array[n + i] = temp;
            }
        }
    }
}
