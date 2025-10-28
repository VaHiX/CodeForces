// Problem: CF 2063 C - Remove Exactly Two
// https://codeforces.com/contest/2063/problem/C

/*
 * Problem: C. Remove Exactly Two
 * Purpose: Given a tree with n nodes, remove exactly two vertices such that the number of connected components is maximized.
 * Algorithm:
 *   - Build adjacency list representation of the tree.
 *   - For each pair of non-adjacent nodes (u,v), compute the potential number of components as degree(u) + degree(v) - 1.
 *   - For each edge (u,v), compute the potential number of components as degree(u) + degree(v) - 2.
 *   - Return the maximum from all computed values.
 * Time Complexity: O(n^2) in worst case due to checking all pairs, but optimized using sorting and early termination.
 * Space Complexity: O(n) for storing adjacency list and degrees.
 */

using System;
using System.Collections.Generic;
public class GraphDegreeCalculator {
  public static void Main(string[] args) {
    var inputScanner = new Scanner();
    int testCasesCount = int.Parse(inputScanner.ReadLine());
    while (testCasesCount-- > 0) {
      int totalNodes = int.Parse(inputScanner.ReadLine());
      var graphAdjacencyList = new List<List<int>>();
      var nodeDegreeArray = new int[totalNodes + 1];
      for (int i = 0; i <= totalNodes; i++) {
        graphAdjacencyList.Add(new List<int>()); // Initialize adjacency list for each node
      }
      for (int i = 0; i < totalNodes - 1; i++) {
        var nodes = inputScanner.ReadLine().Split(' ');
        int firstNode = int.Parse(nodes[0]);
        int secondNode = int.Parse(nodes[1]);
        graphAdjacencyList[firstNode].Add(secondNode); // Add edge in both directions (undirected graph)
        graphAdjacencyList[secondNode].Add(firstNode);
        nodeDegreeArray[firstNode]++; // Increment degree for both nodes
        nodeDegreeArray[secondNode]++;
      }
      var nodeList = new List<int>();
      for (int i = 1; i <= totalNodes; i++) {
        nodeList.Add(i); // Create list of all nodes
      }
      nodeList.Sort((a, b) => { // Sort by degree descending, then by node id ascending
        if (nodeDegreeArray[a] != nodeDegreeArray[b]) {
          return nodeDegreeArray[b].CompareTo(nodeDegreeArray[a]);
        }
        return a.CompareTo(b);
      });
      for (int i = 1; i <= totalNodes; i++) {
        graphAdjacencyList[i].Sort(); // Sort adjacency lists to enable binary search
      }
      long highestDegreeWithoutEdge = 0;
      for (int i = 0; i < totalNodes; i++) {
        int nodeA = nodeList[i];
        for (int j = i + 1; j < totalNodes; j++) {
          int nodeB = nodeList[j];
          if (graphAdjacencyList[nodeA].BinarySearch(nodeB) < 0) { // Check if nodes are NOT adjacent
            long potentialDegree =
                (long)nodeDegreeArray[nodeA] + nodeDegreeArray[nodeB] - 1;
            highestDegreeWithoutEdge =
                Math.Max(highestDegreeWithoutEdge, potentialDegree);
            break; // Since sorted, no need to check further for this nodeA
          }
        }
      }
      long highestDegreeWithEdge = 0;
      for (int nodeA = 1; nodeA <= totalNodes; nodeA++) {
        foreach (int nodeB in graphAdjacencyList[nodeA]) {
          if (nodeA < nodeB) { // Avoid duplicate edge processing.
            long potentialDegree =
                (long)nodeDegreeArray[nodeA] + nodeDegreeArray[nodeB] - 2;
            highestDegreeWithEdge =
                Math.Max(highestDegreeWithEdge, potentialDegree);
          }
        }
      }
      Console.WriteLine(
          Math.Max(highestDegreeWithoutEdge, highestDegreeWithEdge));
    }
  }
  public class Scanner {
    private string[] tokens;
    private int currentIndex;
    public string ReadLine() {
      string input = Console.ReadLine();
      tokens =
          input.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
      currentIndex = 0;
      return input;
    }
    public string NextToken() { return tokens[currentIndex++]; }
    public int NextInt() { return int.Parse(tokens[currentIndex++]); }
  }
}


// https://github.com/VaHiX/codeForces/