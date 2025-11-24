// Problem: CF 2110 D - Fewer Batteries
// https://codeforces.com/contest/2110/problem/D

/*
 * Problem: D. Fewer Batteries
 * Purpose: Find the minimum number of batteries the robot needs at the end of the journey from checkpoint 1 to n,
 *          considering passages that require a certain number of batteries to traverse and checkpoints that can provide batteries.
 *
 * Algorithm:
 * - Binary search on the answer (number of batteries).
 * - For each candidate answer, check if it's possible to reach the last node using BFS / relaxation similar to shortest path (SPFA).
 * - Key technique: Use a modified Dijkstra/BFS with battery constraint and relaxation logic.
 *
 * Time Complexity: O(m * log(max_batteries) + n + m), where max_batteries is up to 1e9
 * Space Complexity: O(n + m)
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class temp
{
    static int []b; // Array storing batteries at each checkpoint
    static HashMap<Integer,Integer>[] g; // Graph representation where key = destination, value = min battery needed to go there
    
    /**
     * Check if it is possible to reach the last node with at most 'x' batteries.
     * Uses a modified relaxation approach (similar to SPFA or Bellman-Ford with limit).
     */
    static boolean find(int x){
        int best[]=new int[g.length]; // best[i] stores max battery we can have at checkpoint i
        int n=g.length ;
        for(int i=1;i<n;i++){
            if(i>1 && best[i]==0){ // Skip initial states or unreachable nodes unless they are source
                continue;
            }
            best[i]+=b[i]; // Add batteries available at current checkpoint
            best[i]=Math.min(best[i],x); // Limit battery at this point by max allowed (x)
            for(int v:g[i].keySet()){ // For each neighbor
                if(g[i].get(v)<=best[i]){ // If passing to v requires <= current battery
                    best[v]=Math.max(best[v],best[i]); // Relax edge: update max battery possible at neighbor
                }
            }
        }
        return best[n-1]!=0; // If we reached the last checkpoint with some battery
    }
    
    public static void main(String[] args) throws Exception{
		Scanner sc=new Scanner(System.in);
        BufferedReader rd=new BufferedReader(new InputStreamReader(System.in));
        String d[]; 
        int times=Integer.parseInt(rd.readLine());
        while(times-->0){
            d=rd.readLine().split(" ");
            int n=Integer.parseInt(d[0]); // Number of checkpoints
            int m=Integer.parseInt(d[1]); // Number of passages
            
            d=rd.readLine().split(" ");
            b=new int[n+1]; // Batteries at each checkpoint (index 1-based)
            for(int i=1;i<=n;i++){
                b[i]=Integer.parseInt(d[i-1]);
            }
            
            g=new HashMap[n+1]; // Graph
            for(int i=1;i<=n;i++){
                g[i]=new HashMap<>();
            }
            
            int a,y,w; // a = source, y = destination, w = battery needed to pass
            
            for(int i=0;i<m;i++){
                d=rd.readLine().split(" ");
                a=Integer.parseInt(d[0]);
                y=Integer.parseInt(d[1]);
                w=Integer.parseInt(d[2]);
                
                // Optimization: keep the minimum weight for same edge
                g[a].put(y,Math.min(g[a].getOrDefault(y,Integer.MAX_VALUE),w));
            }
            
            int ans=-1;
            int l=0,r=1000000000; // Binary search bounds (max possible batteries)
            int mid;
            
            while(l<=r){
                mid=(l+r)/2;
                if(find(mid)){ // Check if it's feasible with 'mid' as max allowed
                    ans=mid;
                    r=mid-1; // Try lower bound
                }
                else{
                    l=mid+1; // Try higher bound
                }
            }
            
            System.out.println(ans);           
        }
	}
}


// https://github.com/VaHiX/CodeForces/