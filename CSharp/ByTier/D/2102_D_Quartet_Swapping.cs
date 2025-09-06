using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static int CalculateInversionParity(List<int> elements)
    {
        int count = elements.Count;
        List<int> sortedElements = new List<int>(elements);
        Dictionary<int, int> valueToIndex = new Dictionary<int, int>();
        
        sortedElements.Sort();
        for (int i = 0; i < count; i++)
            valueToIndex[sortedElements[i]] = i;

        int[] binaryIndexedTree = new int[count + 1];
        int parity = 0;

        Action<int> UpdateTree = (index) => {
            for (++index; index <= count; index += index & -index)
                binaryIndexedTree[index]++;
        };

        Func<int, int> QueryTree = (index) => {
            int result = 0;
            for (++index; index > 0; index -= index & -index)
                result += binaryIndexedTree[index];
            return result;
        };

        for (int i = count - 1; i >= 0; i--)
        {
            int compressedIndex = valueToIndex[elements[i]];
            parity ^= QueryTree(compressedIndex - 1) % 2;
            UpdateTree(compressedIndex);
        }
        return parity;
    }

    static List<int> MergeVectors(List<int> evenElements, List<int> oddElements)
    {
        int totalSize = evenElements.Count + oddElements.Count;
        List<int> merged = new List<int>(totalSize);
        int evenIndex = 0, oddIndex = 0;
        
        for (int i = 0; i < totalSize; i++)
        {
            merged.Add((i % 2 == 0) ? evenElements[evenIndex++] : oddElements[oddIndex++]);
        }
        return merged;
    }

    static void ProcessTestCases()
    {
        int testCases = int.Parse(Console.ReadLine());
        while (testCases-- > 0)
        {
            int elementCount = int.Parse(Console.ReadLine());
            List<int> elements = Console.ReadLine().Split().Select(int.Parse).ToList();
            List<int> evenPositionElements = new List<int>();
            List<int> oddPositionElements = new List<int>();
            
            for (int i = 0; i < elementCount; i++)
            {
                if (i % 2 == 0)
                    evenPositionElements.Add(elements[i]);
                else
                    oddPositionElements.Add(elements[i]);
            }

            List<int> sortedEven = new List<int>(evenPositionElements);
            List<int> sortedOdd = new List<int>(oddPositionElements);
            sortedEven.Sort();
            sortedOdd.Sort();

            int evenParity = CalculateInversionParity(evenPositionElements);
            int oddParity = CalculateInversionParity(oddPositionElements);

            List<int> result;

            if (evenParity == oddParity)
            {
                result = MergeVectors(sortedEven, sortedOdd);
            }
            else
            {
                List<int> modifiedEven = new List<int>(sortedEven);
                List<int> modifiedOdd = new List<int>(sortedOdd);

                if (modifiedEven.Count >= 2)
                {
                    int temp = modifiedEven[modifiedEven.Count - 1];
                    modifiedEven[modifiedEven.Count - 1] = modifiedEven[modifiedEven.Count - 2];
                    modifiedEven[modifiedEven.Count - 2] = temp;
                }

                if (modifiedOdd.Count >= 2)
                {
                    int temp = modifiedOdd[modifiedOdd.Count - 1];
                    modifiedOdd[modifiedOdd.Count - 1] = modifiedOdd[modifiedOdd.Count - 2];
                    modifiedOdd[modifiedOdd.Count - 2] = temp;
                }

                List<int> candidate1 = MergeVectors(modifiedEven, sortedOdd);
                List<int> candidate2 = MergeVectors(sortedEven, modifiedOdd);

                result = (candidate1.SequenceCompareTo(candidate2) <= 0) ? candidate1 : candidate2;
            }

            Console.WriteLine(string.Join(" ", result));
        }
    }

    static void Main()
    {
        ProcessTestCases();
    }
}

// Extension method for sequence comparison
static class Extensions
{
    public static int SequenceCompareTo<T>(this IEnumerable<T> first, IEnumerable<T> second) where T : IComparable<T>
    {
        using (var e1 = first.GetEnumerator())
        using (var e2 = second.GetEnumerator())
        {
            while (e1.MoveNext())
            {
                if (!e2.MoveNext())
                    return 1;
                
                int comparison = e1.Current.CompareTo(e2.Current);
                if (comparison != 0)
                    return comparison;
            }
            return e2.MoveNext() ? -1 : 0;
        }
    }
}