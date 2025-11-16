// Problem: CF 2107 D - Apple Tree Traversing
// https://codeforces.com/contest/2107/problem/D

/*
 * Problem: D. Apple Tree Traversing
 * 
 * Purpose:
 *   This program finds the lexicographically largest sequence of apple paths 
 *   to traverse a tree, where each path consists of nodes with apples and 
 *   results in appending (d, u, v) to the output list after removing apples.
 *   
 *   The approach uses DFS-based diameter finding and greedy removal:
 *     - For each connected component (unvisited nodes), find the farthest pair of nodes (diameter)
 *     - Record the path information (d, u, v) where u is the larger node ID
 *     - Mark all nodes on this path as removed (to simulate apple removal)
 *     - Repeat until no more apples exist
 *     
 * Algorithms/Techniques:
 *   - DFS to find diameter of a tree using two BFS/DFS passes
 *   - Greedy selection strategy to always pick the maximum diameter path first
 *   - Path tracking through parent array
 *   
 * Time Complexity: O(n^2) in worst case due to repeated DFS on components.
 * Space Complexity: O(n)
 */

import java.util.*;
public class Main{
         static class Pair{
                  int dis;
                  int node;
                  Pair(int dis,int node){
                           this.dis=dis;
                           this.node=node;
                  }
         }
         static boolean[] vis,remove;  // vis tracks visited nodes during DFS; remove marks removed nodes
         static int[] parent;          // parent keeps track of parent of each node in DFS traversal
         static List<List<Integer>> adj; // adjacency list for tree structure
         static Pair dfs(int node,int par){  // DFS to find farthest node from 'node'
                  vis[node]=true;
                  parent[node]=par;
                  Pair res=new Pair(1,node);
                  for(int ngbr:adj.get(node)){
                           if(ngbr!=par && !remove[ngbr]){  // Skip parent and already removed nodes
                                    Pair temp=dfs(ngbr,node);   // Recursive DFS on neighbor
                                    temp.dis+=1;                 // Increment distance
                                    if(temp.dis>res.dis || (temp.dis==res.dis && temp.node>res.node)){
                                             res=temp;
                                    }
                           }
                  }
                  return res;  // Returns farthest node and its distance from current node
         }
         public static void main(String[] args){
                 Scanner sc=new Scanner(System.in);
                 int t=sc.nextInt();
                 while(t-- > 0){
                          int n=sc.nextInt();
                          adj=new ArrayList<>();
                          for(int i=0;i<=n;i++){
                                   adj.add(new ArrayList<>());  // Initialize adjacency list
                          }
                          vis=new boolean[n+1];
                          remove=new boolean[n+1];
                          parent=new int[n+1];
                          for(int i=1;i<n;i++){
                                   int u=sc.nextInt();
                                   int v=sc.nextInt();
                                   adj.get(u).add(v);
                                   adj.get(v).add(u);  // Add edges to undirected tree
                          }
                          List<int[]> res=new ArrayList<>();
                          while(true){
                                   boolean hasUnused=false;
                                   for(int i=1;i<=n;i++){
                                            if(!remove[i]){  // Check if some node is still unremoved
                                                  hasUnused=true;
                                                  break;
                                            }
                                   }
                                   if(!hasUnused){  // No more nodes to process
                                            break;
                                   }
                                   Arrays.fill(vis,false);  // Reset visited flag
                                   for(int i=1;i<=n;i++){
                                            if(!vis[i] && !remove[i]){  // Start DFS from unvisited and unremoved node
                                                     Pair x=dfs(i,-1);  // First DFS to find one end of diameter
                                                     Pair y=dfs(x.node,-1);  // Second DFS to find other end of diameter
                                                     int d=y.dis;  // Diameter length (number of apples in path)
                                                     int u=Math.max(x.node,y.node);  // Larger node ID
                                                     int v=Math.min(x.node,y.node);  // Smaller node ID
                                                     res.add(new int[]{d,u,v});  // Push result to list
                                                     int curr=y.node;
                                                     while(curr!=-1){  // Mark entire path as removed
                                                              remove[curr]=true;
                                                              curr=parent[curr];  // Backtrack via parent array
                                                     }
                                            }
                                   }
                          }
                          res.sort((a,b)->{   // Sort by lexicographical order (descending)
                                   for (int i = 0; i < 3; i++) {
                                      if (b[i] != a[i]) return b[i] - a[i];
                                  }
                                  return 0;
                          });
                          for (int[] arr : res) {
                                  System.out.print(arr[0] + " " + arr[1] + " " + arr[2] + " ");
                          }
                          System.out.println();
                 }
         }
}


// https://github.com/VaHiX/CodeForces/