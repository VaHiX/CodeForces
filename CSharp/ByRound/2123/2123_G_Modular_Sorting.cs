using System;
using System.Buffers;
using System.Collections.Generic;
using System.IO;
using System.Text;

class Program {
    static void Main() {
        var reader = new FastInput();
        var sb = new StringBuilder();

        int T = reader.ReadInt();
        while (T-- > 0) {
            int n = reader.ReadInt();
            int m = reader.ReadInt();
            int q = reader.ReadInt();

            // read a[1..n]
            var a = new int[n + 2];
            for (int i = 1; i <= n; i++) {
                a[i] = reader.ReadInt();
            }

            // read queries, collect needed gcds > 1
            var queries = new (int type, int x, int y)[q];
            var needSet = new HashSet<int>();
            for (int i = 0; i < q; i++) {
                int t = reader.ReadInt();
                if (t == 1) {
                    int idx = reader.ReadInt();
                    int x = reader.ReadInt();
                    queries[i] = (1, idx, x);
                } else {
                    int k = reader.ReadInt();
                    queries[i] = (2, k, 0);
                    int d = Gcd(m, k);
                    if (d > 1) needSet.Add(d);
                }
            }

            // build sorted list of needed d's and map to index
            var needList = new List<int>(needSet);
            needList.Sort();
            int D = needList.Count;
            var dIndex = new Dictionary<int,int>(D);
            for (int i = 0; i < D; i++) {
                dIndex[needList[i]] = i;
            }

            // S[i] = # of descents for d = needList[i]
            var S = new int[D];
            for (int di = 0; di < D; di++) {
                int d = needList[di];
                int cnt = 0;
                int prev = a[1] % d;
                for (int j = 2; j <= n; j++) {
                    int cur = a[j] % d;
                    if (cur < prev) cnt++;
                    prev = cur;
                }
                S[di] = cnt;
            }

            // process queries
            foreach (var qu in queries) {
                if (qu.type == 1) {
                    int i = qu.x;
                    int x = qu.y;
                    int old = a[i];
                    if (old != x) {
                        for (int di = 0; di < D; di++) {
                            int d = needList[di];
                            int oldR = old % d, newR = x % d;
                            // border (i-1, i)
                            if (i > 1) {
                                int p = a[i - 1] % d;
                                if (oldR < p) S[di]--;
                                if (newR < p) S[di]++;
                            }
                            // border (i, i+1)
                            if (i < n) {
                                int nxt = a[i + 1] % d;
                                if (nxt < oldR) S[di]--;
                                if (nxt < newR) S[di]++;
                            }
                        }
                        a[i] = x;
                    }
                } else {
                    int k = qu.x;
                    int d = Gcd(m, k);
                    if (d == 1) {
                        sb.AppendLine("YES");
                    } else {
                        int di = dIndex[d];
                        int maxWraps = m / d - 1;
                        sb.Append(S[di] <= maxWraps ? "YES\n" : "NO\n");
                    }
                }
            }
        }

        Console.Write(sb);
    }

    static int Gcd(int a, int b) {
        while (b != 0) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
}

// fast integer reader
class FastInput {
    const int BUF_SIZE = 1 << 16;
    private readonly Stream _stream = Console.OpenStandardInput();
    private readonly byte[] _buf = new byte[BUF_SIZE];
    private int _bufLen = 0, _bufPos = 0;

    private int Read() {
        if (_bufPos >= _bufLen) {
            _bufPos = 0;
            _bufLen = _stream.Read(_buf, 0, BUF_SIZE);
            if (_bufLen <= 0) return -1;
        }
        return _buf[_bufPos++];
    }

    public int ReadInt() {
        int c, x = 0;
        do {
            c = Read();
            if (c == -1) return -1;
        } while (c <= ' ');
        bool neg = false;
        if (c == '-') {
            neg = true;
            c = Read();
        }
        for (; c >= '0' && c <= '9'; c = Read()) {
            x = x * 10 + (c - '0');
        }
        return neg ? -x : x;
    }
}