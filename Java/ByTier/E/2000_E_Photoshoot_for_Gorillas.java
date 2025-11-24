// Problem: CF 2000 E - Photoshoot for Gorillas
// https://codeforces.com/contest/2000/problem/E

import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.*;
public class abcd {
    public static class Reader {
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;
        public Reader() {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
        public Reader(String file_name) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
        public String readLine() throws IOException {
            byte[] buf = new byte[64];
            int cnt = 0, c;
            while ((c = read()) != -1) {
                if (c == '\n') {
                    if (cnt != 0) {
                        break;
                    } else {
                        continue;
                    }
                }
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }
        public int nextInt() throws IOException {
            int ret = 0;
            byte c = read();
            while (c <= ' ') {
                c = read();
            }
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg) return -ret;
            return ret;
        }
        public long nextLong() throws IOException {
            long ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg) return -ret;
            return ret;
        }
        public double nextDouble() throws IOException {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (c == '.') {
                while ((c = read()) >= '0' && c <= '9') {
                    ret += (c - '0') / (div *= 10);
                }
            }
            if (neg) return -ret;
            return ret;
        }
        private void fillBuffer() throws IOException {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1) buffer[0] = -1;
        }
        private byte read() throws IOException {
            if (bufferPointer == bytesRead) fillBuffer();
            return buffer[bufferPointer++];
        }
        public void close() throws IOException {
            if (din == null) return;
            din.close();
        }
    }
    public static void main(String[] args) throws IOException {
        Reader sc = new Reader();
        int t = sc.nextInt();
        while (t > 0) {
            int n = sc.nextInt();
            int m = sc.nextInt();
            int k = sc.nextInt();
            int w = sc.nextInt();
            int[] gor = new int[w];
            for(int i=0;i<w;i++){
                gor[i] = sc.nextInt();
            }
            int[] arr = new int[n*m];
            int ind =0;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    // Calculate how many kxk sub-squares can have their top-left corner at position (i,j)
                    int mini = Math.max(0,i-k+1);
                    int maxi = Math.min(i,n-k);
                    int minj = Math.max(0,j-k+1);
                    int maxj = Math.min(j,m-k);
                    arr[ind++] = (maxi - mini + 1) * (maxj - minj + 1);
                }
            }
            // Sort gorillas in descending order to assign largest heights first
            Arrays.sort(gor);
            // Sort available positions by number of sub-squares they contribute to
            Arrays.sort(arr);
            long ans = 0;
            int j = n*m -1;
            // Greedily assign largest gorilla to position with highest contribution
            for(int i=w-1;i>=0;i--){
                ans += (long)gor[i] * arr[j--];
            }
            System.out.println(ans);
            t--;
        }
    }
}


// https://github.com/VaHiX/CodeForces/