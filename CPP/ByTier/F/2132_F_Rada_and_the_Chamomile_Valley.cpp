/**
 * Problem: CF2132F - Rada and the Chamomile Valley
 * 
 * This program finds the closest bridge to each node in a graph where bridges
 * are edges whose removal increases the number of connected components.
 * 
 * Approach:
 * 1. Identify all bridges in the graph using Tarjan's algorithm
 * 2. Perform BFS from node 1 to find the parent of each node
 * 3. Mark the bridges on the path from node n to node 1
 * 4. Perform multi-source BFS from all bridge endpoints to find the closest bridge to each node
 * 
 * Time Complexity: O(T * (n + m))
 *   - T: Number of test cases
 *   - n: Number of nodes
 *   - m: Number of edges
 *   - Each test case involves DFS and BFS traversals
 * 
 * Space Complexity: O(n + m)
 *   - Adjacency list: O(n + m)
 *   - Arrays for DFS and BFS: O(n)
 */
 #include <bits/stdc++.h>
 using namespace std;
 
 // Pair of integers for storing node information
 using NodePair = pair<int, int>;
 
 // Graph constants and data structures
 const int MAX_NODES = 2e5 + 50;
 const int INF = 0x3f3f3f3f;
 
 // Graph representation
 struct Edge {
     int next;  // Next edge in adjacency list
     int to;    // Destination node
 };
 
 int numNodes, numEdges;
 int head[MAX_NODES];      // Head of adjacency list for each node
 int edgeCount;            // Total number of edges
 int discoveryTime[MAX_NODES];  // Discovery time in DFS
 int lowLink[MAX_NODES];        // Low link value for bridge finding
 int parentEdgeId[MAX_NODES];   // Parent edge ID for BFS tree
 bool isBridge[MAX_NODES * 2];  // Mark if edge is a bridge
 NodePair minBridgeDist[MAX_NODES]; // Closest bridge info: (distance, bridge ID)
 
 vector<Edge> edges(2);  // Edges (1-based indexing)
 
 // Add an undirected edge to the graph
 inline void addEdge(int from, int to) {
     edges.push_back({head[from], to});
     head[from] = ++edgeCount;
     isBridge[edgeCount] = false;
 }
 
 /**
  * Tarjan's algorithm to find bridges in the graph
  * @param currentNode Current node being visited
  * @param parentEdgeId ID of the edge used to reach current node (to avoid revisiting parent)
  */
 void findBridges(int currentNode, int parentEdgeId) {
     static int timeCounter = 0;
     discoveryTime[currentNode] = lowLink[currentNode] = ++timeCounter;
     
     for (int edgeId = head[currentNode]; edgeId; edgeId = edges[edgeId].next) {
         // Skip the edge we came from
         if ((edgeId ^ 1) == parentEdgeId) continue;
         
         int neighbor = edges[edgeId].to;
         
         if (!discoveryTime[neighbor]) {
             // Tree edge
             findBridges(neighbor, edgeId);
             lowLink[currentNode] = min(lowLink[currentNode], lowLink[neighbor]);
             
             // Check for bridge
             if (lowLink[neighbor] > discoveryTime[currentNode]) {
                 isBridge[edgeId] = isBridge[edgeId ^ 1] = true;
             }
         } else {
             // Back edge
             lowLink[currentNode] = min(lowLink[currentNode], discoveryTime[neighbor]);
         }
     }
 }
 
 void solve() {
     // Read input
     cin >> numNodes >> numEdges;
     
     // Initialize data structures
     edgeCount = 1;  // Start from 1 to allow XOR operation for reverse edge
     edges = vector<Edge>(2);  // Reset edges (1-based indexing)
     
     fill_n(head, numNodes + 1, 0);
     fill_n(discoveryTime, numNodes + 1, 0);
     fill_n(lowLink, numNodes + 1, 0);
     fill_n(parentEdgeId, numNodes + 1, -1);
     fill_n(isBridge, 2 * numEdges + 2, false);
     
     // Read edges
     for (int i = 0; i < numEdges; ++i) {
         int u, v;
         cin >> u >> v;
         addEdge(u, v);
         addEdge(v, u);  // Add reverse edge
     }
     
     // Find all bridges in the graph
     findBridges(1, 0);
     
     // BFS to find parent edges
     queue<int> q;
     q.push(1);
     parentEdgeId[1] = 0;  // Mark root as visited
     
     while (!q.empty()) {
         int current = q.front();
         q.pop();
         
         for (int edgeId = head[current]; edgeId; edgeId = edges[edgeId].next) {
             int neighbor = edges[edgeId].to;
             if (parentEdgeId[neighbor] == -1) {
                 parentEdgeId[neighbor] = edgeId;
                 q.push(neighbor);
             }
         }
     }
     
     // Initialize distances
     for (int i = 1; i <= numNodes; ++i) {
         minBridgeDist[i] = {INF, -1};
     }
     
     // Mark bridges on the path from n to 1
     int currentNode = numNodes;
     while (currentNode != 1) {
         int edgeId = parentEdgeId[currentNode];
         if (isBridge[edgeId]) {
             int u = edges[edgeId ^ 1].to;  // Parent node
             minBridgeDist[currentNode] = {0, edgeId / 2};
             minBridgeDist[u] = {0, edgeId / 2};
         }
         currentNode = edges[edgeId ^ 1].to;  // Move to parent
     }
     
     // Multi-source BFS to find closest bridge to each node
     queue<int> bfsQueue;
     for (int i = 1; i <= numNodes; ++i) {
         if (minBridgeDist[i].first == 0) {
             bfsQueue.push(i);
         }
     }
     
     while (!bfsQueue.empty()) {
         int current = bfsQueue.front();
         bfsQueue.pop();
         
         auto [currentDist, bridgeId] = minBridgeDist[current];
         
         for (int edgeId = head[current]; edgeId; edgeId = edges[edgeId].next) {
             int neighbor = edges[edgeId].to;
             
             if (minBridgeDist[neighbor].first > currentDist + 1) {
                 minBridgeDist[neighbor] = {currentDist + 1, bridgeId};
                 bfsQueue.push(neighbor);
             }
         }
     }
     
     // Process queries
     int numQueries;
     cin >> numQueries;
     while (numQueries--) {
         int queryNode;
         cin >> queryNode;
         cout << minBridgeDist[queryNode].second << ' ';
     }
     cout << '\n';
 }
 
 int main() {
     ios::sync_with_stdio(false);
     cin.tie(nullptr);
     cout.tie(nullptr);
     
     int testCases;
     cin >> testCases;
     while (testCases--) {
         solve();
     }
     return 0;
 }