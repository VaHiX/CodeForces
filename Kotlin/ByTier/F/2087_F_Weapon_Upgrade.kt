// Problem: CF 2087 F - Weapon Upgrade
// https://codeforces.com/contest/2087/problem/F

/*
 * Problem: F. Weapon Upgrade
 * Purpose: Calculate the minimum damage to kill all monsters by choosing optimal order and attacks.
 * Algorithm: Dynamic Programming with state (i, j) representing physical attack power i and elemental attack power j,
 *            along with tracking steps taken.
 * Time Complexity: O(n^3), due to 3 nested loops over up to 500x500 states
 * Space Complexity: O(n^2), for DP tables f and steps of size (n+1)x(n+1)
 */

import java.io.*
import java.util.*
import kotlin.math.max
import kotlin.math.min

class IOStream {
    val br = BufferedReader(InputStreamReader(System.`in`))
    var st: StringTokenizer? = null
    fun nextToken(): String? {
        while (st == null || !st!!.hasMoreTokens()) st = StringTokenizer(br.readLine())
        return st!!.nextToken()
    }
    fun nextInt(): Int {
        return nextToken()!!.toInt()
    }
    fun nextLong(): Long {
        return nextToken()!!.toLong()
    }
}

fun main(args: Array<String>) {
    val inp = IOStream()
    val out = PrintWriter(System.out)
    var n = inp.nextInt()
    var a = Array(n, { i -> inp.nextInt() })
    var b = Array(n, { i -> inp.nextInt() })
    var mxa = 0
    var mxb = 0
    for (i in 0..n - 1) {
        --a[i] // Convert to 0-based indexing
        --b[i] // Convert to 0-based indexing
        mxa = max(mxa, a[i])
        mxb = max(mxb, b[i])
    }
    val INF = 1100100100
    var f = Array(mxa + 1, { j -> Array(mxb + 1, { i -> INF }) })
    var steps = Array(mxa + 1, { j -> Array(mxb + 1, { i -> 0 }) })
    var res = -1
    f[0][0] = 0 // Initial state: 0 damage with attack power (1,1) == (0,0) in zero-based
    
    for (i in 0..mxa) for (j in 0..mxb) if (f[i][j] < INF) {
        var cnt = 0
        // Count how many monsters are killable with current attack power (physical <= i || elemental <= j)
        for (k in 0..n - 1) if (a[k] <= i || b[k] <= j) ++cnt
        var good = (cnt == n) // All monsters are killable with current state
        
        cnt = 0
        val lim = min(steps[i][j], n - 1)
        
        // Count how many of the first 'lim' monsters are killable
        for (k in 0..lim) if (a[k] <= i || b[k] <= j) ++cnt
        
        var nxt = steps[i][j] + 1 // Next monster to process
        var cur = f[i][j] // Current total damage from this state
        var exist = lim + 1 - i - j // How many monsters already "available" for later consideration
        cur += exist // Add damage from alive monsters so far

        if (good) {
            --exist // This means we can take advantage of remaining non-affected monsters
            --cur // We adjust to include the extra cost savings
            for (k in lim + 1..n - 1) cur += exist // Accumulate future cost
            while (exist > 0) {
                --exist
                cur += exist // Add further cost as needed
            }
            if (res == -1 || cur < res) res = cur // Update minimum damage if better solution found
            continue
        }

        if (cnt <= i + j) // If the current monsters are not all killable yet, try to expand
            for (k in lim + 1..n - 1) {
                if (a[k] <= i || b[k] <= j) ++cnt
                
                ++exist // We're processing another monster now
                cur += exist // Update cost with new monster consideration
                
                if (cnt > i + j) { // If we've reached an unkillable monster or full coverage
                    nxt = k + 1 // Next monster to consider after this point
                    break
                }
            }

        if (cnt > i + j) { // If now we know some are unkillable at the current attack strength
            --cur // Reduce cost due to optimization effect

            // If we can move right (i+1), update DP state with less damage
            if (i < mxa && f[i + 1][j] > cur) {
                f[i + 1][j] = cur
                steps[i + 1][j] = nxt
            }

            // If we can move down (j+1), update DP state with less damage  
            if (j < mxb && f[i][j + 1] > cur) {
                f[i][j + 1] = cur
                steps[i][j + 1] = nxt
            }
        }
    }

    out.println(res)
    out.close()
}


// https://github.com/VaHiX/codeForces/