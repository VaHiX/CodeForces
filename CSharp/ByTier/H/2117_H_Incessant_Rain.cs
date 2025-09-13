using System;
using System.Collections.Generic;
// System.Linq is not strictly needed.
using System.Text;

/* ---------- fast scanner ---------- */
sealed class FastScanner {
    readonly byte[] buf = new byte[1 << 16]; // 64KB buffer
    int len, ptr; readonly System.IO.Stream s = Console.OpenStandardInput();
    int ReadByte() {
        if (ptr >= len) { len = s.Read(buf, 0, buf.Length); ptr = 0; if (len == 0) return -1; }
        return buf[ptr++];
    }
    public int NextInt() {
        int c, sign = 1, v = 0;
        while ((c = ReadByte()) <= 32 && c != -1) ; 
        if (c == '-') { sign = -1; c = ReadByte(); }
        for (; c > 32 && c != -1; c = ReadByte()) v = v * 10 + (c - '0');
        return v * sign;
    }
}

/* ---------- seg-tree for ±1 mask ---------- */
struct Node { public int sum, pref, suff, best; }
static class Util {
    public static Node Make(int x) => new() {
        sum = x, pref = Math.Max(0, x), suff = Math.Max(0, x), best = Math.Max(0, x)
    };
    public static Node Merge(in Node L, in Node R) => new() {
        sum = L.sum + R.sum,
        pref = Math.Max(L.pref, L.sum + R.pref),
        suff = Math.Max(R.suff, R.sum + L.suff),
        best = Math.Max(Math.Max(L.best, R.best), L.suff + R.pref)
    };
}
sealed class SegTree {
    readonly int N_pot; 
    readonly Node[] t;
    public SegTree(int m) { 
        N_pot = 1; while (N_pot < m) N_pot <<= 1;
        t = new Node[N_pot << 1]; 
        if (m > 0) Build(1, 0, N_pot - 1); 
    }
    void Build(int p, int l, int r) {
        if (l == r) { t[p] = Util.Make(-1); return; } 
        int mid = (l + r) >> 1;
        Build(p << 1, l, mid); Build(p << 1 | 1, mid + 1, r);
        t[p] = Util.Merge(t[p << 1], t[p << 1 | 1]);
    }
    public void Add(int idx, int delta) {
        Upd(1, 0, N_pot - 1, idx, delta);
    }
    void Upd(int p, int l, int r, int idx, int d) {
        if (l == r) {
            t[p].sum += d;
            int x = t[p].sum;
            t[p].pref = t[p].suff = t[p].best = Math.Max(x, 0);
            return;
        }
        int mid = (l + r) >> 1;
        if (idx <= mid) Upd(p << 1, l, mid, idx, d);
        else            Upd(p << 1 | 1, mid + 1, r, idx, d);
        t[p] = Util.Merge(t[p << 1], t[p << 1 | 1]);
    }
    public int CurK() => N_pot == 0 ? 0 : (t[1].best >> 1);
}

/* ---------- MaxKTree (replaces IntMultiset) ---------- */
sealed class MaxKTree {
    readonly int N_k_pot; 
    readonly int[] k_counts;
    readonly int[] tree_val; 
    const int MIN_VAL_K = -1; 

    public MaxKTree(int max_val_exclusive) {
        if (max_val_exclusive <= 0) max_val_exclusive = 1; 
        k_counts = new int[max_val_exclusive];
        N_k_pot = 1;
        while (N_k_pot < max_val_exclusive) N_k_pot <<= 1;
        tree_val = new int[2 * N_k_pot];
        
        for(int i=0; i < tree_val.Length; ++i) tree_val[i] = MIN_VAL_K;
    }

    public void Add(int k_val) {
        k_counts[k_val]++;
        if (k_counts[k_val] == 1) { 
            UpdateInternal(k_val, k_val);
        }
    }

    public void Remove(int k_val) {
        if (k_counts[k_val] == 0) return; 
        
        k_counts[k_val]--;
        if (k_counts[k_val] == 0) { 
            UpdateInternal(k_val, MIN_VAL_K);
        }
    }

    void UpdateInternal(int idx, int val_to_set_at_leaf) {
        int p = N_k_pot + idx;
        tree_val[p] = val_to_set_at_leaf;
        while (p > 1) {
            p >>= 1;
            tree_val[p] = Math.Max(tree_val[p << 1], tree_val[p << 1 | 1]);
        }
    }

    public int Max() {
        int max_k_found = tree_val[1];
        return max_k_found == MIN_VAL_K ? 0 : max_k_found;
    }
}


/* ---------------- main ---------------- */
static class Program {
    const int TYPE_POS_INIT = 0;
    const int TYPE_UPD = 1;
    const int TYPE_POS_FINAL = 2;

    // Static lists to reuse capacity across test cases.
    static List<(int v_color, int type, int t_time, int p_pos, int d_delta)> posEvents = new();
    static List<(int t_time, int oldK, int newK)> allChanges = new();

    static void Main() {
        var fs = new FastScanner();
        int T = fs.NextInt();
        var outSb = new StringBuilder(1 << 20); // Accumulates output for all test cases

        while (T-- > 0) {
            int n = fs.NextInt(), q = fs.NextInt();
            
            int[] initial_a_val = new int[n];
            for (int i = 0; i < n; ++i) initial_a_val[i] = fs.NextInt() - 1;

            int[] current_a_val = new int[n];
            if (n > 0) Array.Copy(initial_a_val, current_a_val, n);

            posEvents.Clear();
            allChanges.Clear();
            
            // Optional: Pre-allocate capacity if N, Q are large. Example:
            // if (posEvents.Capacity < 2 * n + 2 * q) posEvents.Capacity = 2 * n + 2 * q;
            // if (allChanges.Capacity < 2 * q) allChanges.Capacity = 2 * q;


            for (int i = 0; i < n; ++i) {
                // Ensure initial_a_val[i] is a valid color index if necessary
                // Assuming 0 <= initial_a_val[i] < n
                posEvents.Add((initial_a_val[i], TYPE_POS_INIT, -1, i, +2));
            }
            initial_a_val = null; // Eligible for GC

            for (int t = 0; t < q; ++t) {
                int p_idx = fs.NextInt() - 1;
                int v_new = fs.NextInt() - 1;
                // Assuming 0 <= p_idx < n and 0 <= v_new < n.
                // The check n > 0 handles p_idx access for empty current_a_val.
                if (n > 0 && v_new != current_a_val[p_idx]) { 
                    posEvents.Add((current_a_val[p_idx], TYPE_UPD, t, p_idx, -2));
                    posEvents.Add((v_new, TYPE_UPD, t, p_idx, +2));
                    current_a_val[p_idx] = v_new;
                }
            }
            
            for (int i = 0; i < n; ++i) {
                // Assuming 0 <= current_a_val[i] < n
                posEvents.Add((current_a_val[i], TYPE_POS_FINAL, -1, i, -2));
            }
            current_a_val = null; // Eligible for GC
            
            posEvents.Sort((e1, e2) => {
                int cmp = e1.v_color.CompareTo(e2.v_color);
                if (cmp != 0) return cmp;
                cmp = e1.type.CompareTo(e2.type);
                if (cmp != 0) return cmp;
                return e1.t_time.CompareTo(e2.t_time);
            });

            var seg = new SegTree(n); // SegTree is ~8MB for N=2e5
            var initK = new int[n]; // initK is ~0.8MB for N=2e5

            int event_idx = 0;
            while(event_idx < posEvents.Count) {
                int v_col = posEvents[event_idx].v_color;
                
                while(event_idx < posEvents.Count && posEvents[event_idx].v_color == v_col && posEvents[event_idx].type == TYPE_POS_INIT) {
                    var ev = posEvents[event_idx];
                    seg.Add(ev.p_pos, ev.d_delta);
                    event_idx++;
                }
                
                // It's critical that v_col is a valid index for initK if n > 0.
                // The problem implies colors are within 0..n-1 range.
                int k_val_for_current_v = 0;
                if (n > 0) { // Only access initK if n > 0
                     initK[v_col] = seg.CurK(); // v_col must be in [0, n-1]
                     k_val_for_current_v = initK[v_col];
                } else { // If n=0, CurK is 0.
                    k_val_for_current_v = seg.CurK();
                }

                while(event_idx < posEvents.Count && posEvents[event_idx].v_color == v_col && posEvents[event_idx].type == TYPE_UPD) {
                    var ev = posEvents[event_idx];
                    seg.Add(ev.p_pos, ev.d_delta);
                    int next_k_val = seg.CurK();
                    if (k_val_for_current_v != next_k_val) {
                        allChanges.Add((ev.t_time, k_val_for_current_v, next_k_val));
                    }
                    k_val_for_current_v = next_k_val;
                    event_idx++;
                }
                
                while(event_idx < posEvents.Count && posEvents[event_idx].v_color == v_col && posEvents[event_idx].type == TYPE_POS_FINAL) {
                    var ev = posEvents[event_idx];
                    seg.Add(ev.p_pos, ev.d_delta);
                    event_idx++;
                }
            }
            
            // MaxKTree is ~1.4MB for N=2e5
            var k_tracker = new MaxKTree(n > 0 ? (n / 2 + 1) : 1); 
            for (int v = 0; v < n; ++v) {
                // initK[v] must be valid k for MaxKTree (i.e. >=0 and < n/2+1)
                k_tracker.Add(initK[v]);
            }
            initK = null; // Eligible for GC

            allChanges.Sort((c1, c2) => c1.t_time.CompareTo(c2.t_time));
            
            int change_idx = 0;
            for (int t = 0; t < q; ++t) {
                while(change_idx < allChanges.Count && allChanges[change_idx].t_time == t) {
                    var chg = allChanges[change_idx];
                    k_tracker.Remove(chg.oldK);
                    k_tracker.Add(chg.newK);
                    change_idx++;
                }
                outSb.Append(k_tracker.Max());
                if (t < q - 1) outSb.Append(' '); 
            }
            outSb.Append('\n');
        }
        Console.Write(outSb.ToString());
    }
}