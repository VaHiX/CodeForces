// Problem: CF 2132 E - Arithmetics Competition
// https://codeforces.com/contest/2132/problem/E

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import kotlin.math.max
import kotlin.math.min
typealias LL = Long
fun f(A: LongArray, B: LongArray, i: Int, z: Int): Long {
    return A[i] + B[z - i]
}
fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val tLine = br.readLine() ?: return
    var T = tLine.toInt()
    val out = StringBuilder()
    repeat(T) {
        val st1 = StringTokenizer(br.readLine())
        val n = st1.nextToken().toInt()
        val m = st1.nextToken().toInt()
        var q = st1.nextToken().toInt()
        val a = LongArray(n)
        val b = LongArray(m)
        run {
            val st = StringTokenizer(br.readLine())
            for (i in 0 until n) a[i] = st.nextToken().toLong()
        }
        run {
            val st = StringTokenizer(br.readLine())
            for (i in 0 until m) b[i] = st.nextToken().toLong()
        }
        a.sortDescending()
        b.sortDescending()
        val pa = LongArray(n + 1)
        val pb = LongArray(m + 1)
        for (i in 1..n) pa[i] = pa[i - 1] + a[i - 1]
        for (i in 1..m) pb[i] = pb[i - 1] + b[i - 1]
        repeat(q) {
            val st = StringTokenizer(br.readLine())
            var x = st.nextToken().toInt()
            var y = st.nextToken().toInt()
            val z = st.nextToken().toInt()
            x = min(x, n)
            y = min(y, m)
            if (z > x + y) {
                out.append("0\n")
                return@repeat
            }
            val L = max(0, z - y)
            val R = min(z, x)
            if (L > R) {
                out.append("0\n")
                return@repeat
            }
            var l = L
            var r = R
            while (l < r) {
                val mid = (l + r) / 2
                val v1 = f(pa, pb, mid, z)
                val v2 = f(pa, pb, mid + 1, z)
                if (v1 < v2) l = mid + 1
                else r = mid
            }
            out.append(f(pa, pb, l, z)).append("\n")
        }
    }
    print(out.toString())
}

// https://github.com/VaHiX/CodeForces/