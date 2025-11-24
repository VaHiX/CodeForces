// Problem: CF 2113 E - From Kazan with Love
// https://codeforces.com/contest/2113/problem/E

/*
 * Problem: E. From Kazan with Love
 * 
 * Purpose: Find the earliest time Marat can reach his work without meeting any enemies.
 * 
 * Algorithms/Techniques:
 * - BFS to compute shortest paths from each enemy's home to work
 * - BFS traversal for Marat's movement with time tracking
 * - Preprocessing enemy paths and checking for conflicts at each time step
 * 
 * Time Complexity: O(n * m + n^2) where n is number of vertices, m is number of enemies
 * Space Complexity: O(n * m + n^2) for storing enemy paths and graph
 * 
 * Approach:
 * 1. Build the tree graph
 * 2. For each enemy, find their shortest path from home (a_i) to work (b_i)
 * 3. Use BFS for Marat's movement with time tracking
 * 4. At each time step, check if Marat can move without meeting enemies
 * 5. Return earliest time to reach work or -1 if impossible
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;
public class Main {
    public static void main(String args[]) {new Main().run();}
    FastReader in = new FastReader();
    PrintWriter out = new PrintWriter(System.out);
    void run() {
        for(int q=ni();q>0;q--){
            work();
        }
        out.flush();
    }
    long mod=998244353;
    int inf=1999999999;
    long gcd(long a,long b) {
        return a==0?b:gcd(b%a,a);
    }
    void work(){
        int n=ni(),m=ni(),x=ni()-1,y=ni()-1;
        ArrayList<Integer>[] graph=ng(n,n-1);
        int[] B=new int[n];
        int[][] rec=new int[n][201];
        Deque<Integer> queue=new ArrayDeque<>();
        int[] vis=new int[n];
        int[] pre=new int[n];
        for(int c=1,k=0;k<m;k++,c++){
            int s=ni()-1;
            int e=ni()-1;
            queue.add(e);
            vis[e]=c;
            out:
            while(true){
                Integer node = queue.poll();
                for(int nn:graph[node]){
                    if(vis[nn]!=c){
                        vis[nn]=c;
                        pre[nn]=node;
                        if(nn==s){
                            queue.clear();
                            break out;
                        }
                        queue.add(nn);
                    }
                }
            }
            for(int i=s,t=0;;i=pre[i],t++){
                rec[t][B[t]++]=i;
                if(i==e)break;
            }
        }
        boolean[] curSet=new boolean[n];
        int[] list=new int[2*n];
        int idx1=0;
        list[idx1++]=x;
        Arrays.fill(vis,-1);
        int size=0;
        int ret=0;
        while(true){
            int idx2=idx1<n?n:0;
            int s1=idx1<n?0:n;
            for(int i=s1;i<idx1;i++){
                curSet[list[i]]=true;
                size++;
            }
            if(ret<n){
                for(int i=0;i<B[ret];i++){
                    int nn=rec[ret][i];
                    if(curSet[nn]){
                        curSet[nn]=false;
                        size--;
                    }
                }
            }
            for(int i=s1;i<idx1;i++){
                if(!curSet[list[i]])continue;
                for(int nn:graph[list[i]]){
                    if(vis[nn]==ret||curSet[nn])continue;
                    list[idx2++]=nn;
                    vis[nn]=ret;
                }
            }
            if(ret<n){
                for(int i=0;i<B[ret];i++){
                    int node=rec[ret][i];
                    if(vis[node]==ret||curSet[node])continue;
                    for(int n2:graph[node]){
                        if(curSet[n2]){
                            list[idx2++]=node;
                            break;
                        }
                    }
                    vis[node]=ret;
                }
            }
            if(curSet[y]){
                out.println(ret+1);
                return;
            }
            if(size==0)break;
            ret++;
            idx1=idx2;
        }
        out.println(-1);
    }
    private ArrayList<Integer>[] ng(int n, int m) {
        ArrayList<Integer>[] graph=(ArrayList<Integer>[])new ArrayList[n];
        for(int i=0;i<n;i++) {
            graph[i]=new ArrayList<>();
        }
        for(int i=1;i<=m;i++) {
            int s=in.nextInt()-1,e=in.nextInt()-1;
            graph[s].add(e);
            graph[e].add(s);
        }
        return graph;
    }
    private ArrayList<long[]>[] ngw(int n, int m) {
        ArrayList<long[]>[] graph=(ArrayList<long[]>[])new ArrayList[n];
        for(int i=0;i<n;i++) {
            graph[i]=new ArrayList<>();
        }
        for(int i=1;i<=m;i++) {
            long s=in.nextLong()-1,e=in.nextLong()-1,w=in.nextLong();
            graph[(int)s].add(new long[] {e,w});
            graph[(int)e].add(new long[] {s,w});
        }
        return graph;
    }
    private int ni() {
        return in.nextInt();
    }
    private long nl() {
        return in.nextLong();
    }
    private double nd() {
        return in.nextDouble();
    }
    private String ns() {
        return in.next();
    }
    private long[] na(int n) {
        long[] A=new long[n];
        for(int i=0;i<n;i++) {
            A[i]=in.nextLong();
        }
        return A;
    }
    private int[] nia(int n) {
        int[] A=new int[n];
        for(int i=0;i<n;i++) {
            A[i]=in.nextInt();
        }
        return A;
    }
}
class FastReader
{
    BufferedReader br;
    StringTokenizer st;
    InputStreamReader input;
    public FastReader()
    {
        br=new BufferedReader(new InputStreamReader(System.in));
    }
    public FastReader(boolean isBuffer)
    {
        if(!isBuffer){
            input=new InputStreamReader(System.in);
        }else{
            br=new BufferedReader(new InputStreamReader(System.in));
        }
    }
    public boolean hasNext(){
        try{
            String s=br.readLine();
            if(s==null){
                return  false;
            }
            st=new StringTokenizer(s);
        }catch(IOException e){
            e.printStackTrace();
        }
        return true;
    }
    public String next()
    {
        if(input!=null){
            try {
                StringBuilder sb=new StringBuilder();
                int ch=input.read();
                while(ch=='\n'||ch=='\r'||ch==32){
                    ch=input.read();
                }
                while(ch!='\n'&&ch!='\r'&&ch!=32){
                    sb.append((char)ch);
                    ch=input.read();
                }
                return sb.toString();
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        while(st==null || !st.hasMoreElements())
        {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return st.nextToken();
    }
    public int nextInt()
    {
        return (int)nextLong();
    }
    public long nextLong() {
        try {
            if(input!=null){
                long ret=0;
                int b=input.read();
                while(b<'0'||b>'9'){
                    b=input.read();
                }
                while(b>='0'&&b<='9'){
                    ret=ret*10+(b-'0');
                    b=input.read();
                }
                return ret;
            }
        }catch (Exception e){
            e.printStackTrace();
        }
        return Long.parseLong(next());
    }
    public double nextDouble()
    {
        return Double.parseDouble(next());
    }
}


// https://github.com/VaHiX/CodeForces/