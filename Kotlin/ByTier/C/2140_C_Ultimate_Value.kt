// Problem: CF 2140 C - Ultimate Value
// https://codeforces.com/contest/2140/problem/C

/*
 * Problem: C. Ultimate Value
 * 
 * Purpose:
 * This code computes the optimal value of f(a) for an array a, where:
 * f(a) = cost + (a[0] - a[1] + a[2] - a[3] + ... +/- a[n-1])
 * Players (Alice and Bob) take turns swapping elements to maximize/minimize f(a).
 * Alice goes first and tries to maximize f(a), Bob tries to minimize it.
 * 
 * The algorithm uses dynamic programming and greedy strategies:
 * - First calculates base value of f(a) with no swaps.
 * - Then, for each possible swap operation (l,r), calculates the effect on cost and final value.
 * - Uses optimized state tracking to determine best moves under optimal play.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

const val NEG = -9000000000000000000L 

fun solve(reader: FastScanner) {
    val n = reader.nextInt()
    val a = LongArray(n) { reader.nextLong() }
    var ans = 0L
    for (i in 0 until n) {
        if (i % 2 == 0) ans += a[i]
        else ans -= a[i]
    }
    var bo = NEG   // best odd index value tracking  
    var be = NEG   // best even index value tracking
    var fo = -1    // first odd index
    var lo = -1    // last odd index
    var fe = -1    // first even index
    var le = -1    // last even index
    var cr = NEG   // current maximum gain from a swap
    for (i in 0 until n) {
        val p = (i + 1).toLong()
        if (p % 2 == 1L) { // current position is odd (1-indexed)
            if (be != NEG) {
                val cnt = p - 2L * a[i] + be // calculate gain when swapping with even element
                if (cnt > cr) cr = cnt
            }
            val value = -p - 2L * a[i]   // update best odd value
            if (value > bo) bo = value
            if (fo == -1) fo = p.toInt() // first odd index
            lo = p.toInt()
        } else { // current position is even (1-indexed)
            if (bo != NEG) {
                val cnt = p + 2L * a[i] + bo // calculate gain when swapping with odd element
                if (cnt > cr) cr = cnt
            }
            val value = -p + 2L * a[i]   // update best even value
            if (value > be) be = value
            if (fe == -1) fe = p.toInt() // first even index
            le = p.toInt()
        }
    }
    
    var s = NEG
    if (fo != -1 && lo > fo) s = maxOf(s, (lo - fo).toLong())  // length of odd sequence
    if (fe != -1 && le > fe) s = maxOf(s, (le - fe).toLong())  // length of even sequence
    
    var b = maxOf(s, cr)  // max possible gain from a single swap or largest sequence
    if (b < 0) b = 0     // no negative gain allowed
  
    println(ans + b)
}

fun main() {
    val reader = FastScanner()
    val t = reader.nextInt()
    repeat(t) {
        solve(reader)
    }
}

class FastScanner {
    private val br = BufferedReader(InputStreamReader(System.`in`))
    private var st: StringTokenizer? = null
    fun next(): String {
        while (st == null || !st!!.hasMoreElements()) {
            st = StringTokenizer(br.readLine())
        }
        return st!!.nextToken()
    }
    fun nextInt(): Int = next().toInt()
    fun nextLong(): Long = next().toLong()
}


// https://github.com/VaHiX/codeForces/