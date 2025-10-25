// Problem: CF 2000 A - Primary Task
// https://codeforces.com/contest/2000/problem/A

import java.util.*;
import java.io.*;
public class A_Primary_Task {
    public static void main(String[] args) {
        try {
            FastReader in=new FastReader();
            FastWriter out=new FastWriter();
            int testcases=in.nextInt();
            while(testcases-- >0){
                int n=in.nextInt();
                String str=n+"";
                // Check if the string representation of n could have been formed by writing 10^x as 10x
                // The valid cases are when the number starts with "10" and the third digit is not 0 or 1
                // Also handles cases where length > 3 and starts with "10" and third digit is not 0
                if(str.length()==3 && str.charAt(0)=='1' && str.charAt(1)=='0' && str.charAt(2)!='0' && str.charAt(2)!='1'){
                    out.println("YES");
                }
                else if(str.length()>3 && str.charAt(0)=='1' && str.charAt(1)=='0' && str.charAt(2)!='0'){
                    out.println("YES");
                }
                else{
                    out.println("NO");
                }
            }
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    static class FastReader{
        BufferedReader br;
        StringTokenizer st;
        public FastReader(){
            br=new BufferedReader(new InputStreamReader(System.in));
        }
        String next(){
            while(st==null || !st.hasMoreTokens()){
                try {
                    st=new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
        int nextInt(){
            return Integer.parseInt(next());
        }
        long nextLong(){
            return Long.parseLong(next());
        }
        double nextDouble(){
            return Double.parseDouble(next());
        }
        char nextChar() {
            return next().charAt(0);
        }
        String nextLine(){
            String str="";
            try {
                str=br.readLine().trim();
            } catch (Exception e) {
                e.printStackTrace();
            }
            return str;
        }
    }
    static class FastWriter {
        private final BufferedWriter bw;
        public FastWriter() {
            this.bw = new BufferedWriter(new OutputStreamWriter(System.out));
        }
        public void print(Object object) throws IOException {
            bw.append("" + object);
        }
        public void println(Object object) throws IOException {
            print(object);
            bw.append("\n");
        }
        public void close() throws IOException {
            bw.close();
        }
    }
}


// https://github.com/VaHiX/CodeForces/