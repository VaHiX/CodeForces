using System;
using System.Collections.Generic;

public class GraphDegreeCalculator
{
    public static void Main(string[] args)
    {
        var inputScanner = new Scanner();
        int testCasesCount = int.Parse(inputScanner.ReadLine());

        while (testCasesCount-- > 0)
        {
            int totalNodes = int.Parse(inputScanner.ReadLine());
            
            var graphAdjacencyList = new List<List<int>>();
            var nodeDegreeArray = new int[totalNodes + 1];

            for (int i = 0; i <= totalNodes; i++)
            {
                graphAdjacencyList.Add(new List<int>());
            }

            for (int i = 0; i < totalNodes - 1; i++)
            {
                var nodes = inputScanner.ReadLine().Split(' ');
                int firstNode = int.Parse(nodes[0]);
                int secondNode = int.Parse(nodes[1]);
                graphAdjacencyList[firstNode].Add(secondNode);
                graphAdjacencyList[secondNode].Add(firstNode);
                nodeDegreeArray[firstNode]++;
                nodeDegreeArray[secondNode]++;
            }

            var nodeList = new List<int>();
            for (int i = 1; i <= totalNodes; i++)
            {
                nodeList.Add(i);
            }

            nodeList.Sort((a, b) =>
            {
                if (nodeDegreeArray[a] != nodeDegreeArray[b])
                {
                    return nodeDegreeArray[b].CompareTo(nodeDegreeArray[a]);
                }
                return a.CompareTo(b);
            });

            for (int i = 1; i <= totalNodes; i++)
            {
                graphAdjacencyList[i].Sort();
            }

            long highestDegreeWithoutEdge = 0;

            for (int i = 0; i < totalNodes; i++)
            {
                int nodeA = nodeList[i];
                for (int j = i + 1; j < totalNodes; j++)
                {
                    int nodeB = nodeList[j];

                    if (graphAdjacencyList[nodeA].BinarySearch(nodeB) < 0)
                    {
                        long potentialDegree = (long)nodeDegreeArray[nodeA] + nodeDegreeArray[nodeB] - 1;
                        highestDegreeWithoutEdge = Math.Max(highestDegreeWithoutEdge, potentialDegree);
                        break;
                    }
                }
            }

            long highestDegreeWithEdge = 0;

            for (int nodeA = 1; nodeA <= totalNodes; nodeA++)
            {
                foreach (int nodeB in graphAdjacencyList[nodeA])
                {
                    if (nodeA < nodeB)
                    {
                        long potentialDegree = (long)nodeDegreeArray[nodeA] + nodeDegreeArray[nodeB] - 2;
                        highestDegreeWithEdge = Math.Max(highestDegreeWithEdge, potentialDegree);
                    }
                }
            }

            Console.WriteLine(Math.Max(highestDegreeWithoutEdge, highestDegreeWithEdge));
        }
    }

    public class Scanner
    {
        private string[] tokens;
        private int currentIndex;

        public string ReadLine()
        {
            string input = Console.ReadLine();
            tokens = input.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            currentIndex = 0;
            return input;
        }

        public string NextToken()
        {
            return tokens[currentIndex++];
        }

        public int NextInt()
        {
            return int.Parse(tokens[currentIndex++]);
        }
    }
}
