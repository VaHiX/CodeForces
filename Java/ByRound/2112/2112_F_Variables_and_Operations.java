// Problem: CF 2112 F - Variables and Operations
// https://codeforces.com/contest/2112/problem/F

/**
 * This code solves a problem where we have n variables and m operations that can be applied to these variables.
 * Each operation updates a variable's value as the minimum of its current value and another variable's value plus a constant.
 * The goal is to determine, for each variable, if it's possible to make it "unstable" (i.e., result depends on operation order)
 * by decreasing initial values at most k times.
 *
 * Algorithm:
 * - Build a directed graph representing the operations with weights.
 * - Use Floyd-Warshall algorithm to compute all-pairs shortest paths.
 * - For each query:
 *   - Determine the minimum reachable value for each node based on initial weights and edges.
 *   - Check for each node whether it can be made unstable within k changes.
 *
 * Time Complexity: O(n^3 + q*n^2)
 * Space Complexity: O(n^2)
 */
import java.util.*;
import java.io.*;
public class GraphPathAnalyzer {
    private static final long INF = Long.MAX_VALUE / 2;
    private static class Graph {
        private final int vertexCount;
        private final long[][] directEdges;  // Direct edge weights
        private final long[][] shortestPaths;  // All-pairs shortest paths after Floyd-Warshall
        public Graph(int n) {
            this.vertexCount = n;
            this.directEdges = new long[n+1][n+1];
            this.shortestPaths = new long[n+1][n+1];
            for (int i = 1; i <= n; i++) {
                Arrays.fill(directEdges[i], INF);
                Arrays.fill(shortestPaths[i], INF);
                directEdges[i][i] = 0;
                shortestPaths[i][i] = 0;
            }
        }
        public void addEdge(int from, int to, long weight) {
            // Store the minimum weight for each edge (reverse direction)
            directEdges[to][from] = Math.min(directEdges[to][from], weight);
            shortestPaths[to][from] = directEdges[to][from];
        }
        public void computeAllShortestPaths() {
            // Floyd-Warshall algorithm to compute shortest paths
            for (int k = 1; k <= vertexCount; k++) {
                for (int i = 1; i <= vertexCount; i++) {
                    for (int j = 1; j <= vertexCount; j++) {
                        if (shortestPaths[i][k] + shortestPaths[k][j] < shortestPaths[i][j]) {
                            shortestPaths[i][j] = shortestPaths[i][k] + shortestPaths[k][j];
                        }
                    }
                }
            }
        }
        public String processQuery(long threshold, long[] vertexWeights) {
            // Initialize minReach with current vertex weights
            long[] minReach = Arrays.copyOf(vertexWeights, vertexWeights.length);
            for (int src = 1; src <= vertexCount; src++) {
                for (int dest = 1; dest <= vertexCount; dest++) {
                    // Update minimum reach by considering direct edge from src to dest
                    minReach[dest-1] = Math.min(minReach[dest-1], 
                                             vertexWeights[src-1] + directEdges[src][dest]);
                }
            }
            StringBuilder result = new StringBuilder(vertexCount);
            for (int v = 1; v <= vertexCount; v++) {
                long minValue = INF;
                for (int u = 1; u <= vertexCount; u++) {
                    // Check if path from u to v is shorter than direct edge (indicating cycle)
                    if (shortestPaths[u][v] < directEdges[u][v]) {
                        // Compute potential instability measure
                        long current = vertexWeights[u-1] + shortestPaths[u][v] - (minReach[v-1] - 1);
                        minValue = Math.min(minValue, current);
                    }
                }
                // Append '1' if the minimum value is within threshold, otherwise '0'
                result.append(minValue <= threshold ? '1' : '0');
            }
            return result.toString();
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
        String[] firstLine = reader.readLine().split(" ");
        int n = Integer.parseInt(firstLine[0]);
        int m = Integer.parseInt(firstLine[1]);
        Graph graph = new Graph(n);
        for (int i = 0; i < m; i++) {
            String[] edgeInfo = reader.readLine().split(" ");
            int from = Integer.parseInt(edgeInfo[0]);
            int to = Integer.parseInt(edgeInfo[1]);
            long weight = Long.parseLong(edgeInfo[2]);
            graph.addEdge(from, to, weight);
        }
        graph.computeAllShortestPaths();
        int q = Integer.parseInt(reader.readLine());
        while (q-- > 0) {
            long k = Long.parseLong(reader.readLine());
            long[] vertexWeights = new long[n];
            String[] weights = reader.readLine().split(" ");
            for (int i = 0; i < n; i++) {
                vertexWeights[i] = Long.parseLong(weights[i]);
            }
            writer.write(graph.processQuery(k, vertexWeights));
            writer.newLine();
        }
        writer.flush();
    }
}


// https://github.com/VaHiX/CodeForces/