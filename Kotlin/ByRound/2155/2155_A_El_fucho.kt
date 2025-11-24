// Problem: CF 2155 A - El fucho
// https://codeforces.com/contest/2155/problem/A

/*
 * Problem: Double Elimination Tournament
 * Purpose: Calculate total number of matches played in a double-elimination tournament with n teams.
 *
 * Algorithm/Techniques:
 * - Simulates the pairing and elimination process described in the problem.
 * - Uses two counters: 'wi' for winners group, 'lo' for losers group.
 * - In each iteration:
 *   1. Pair up teams in winners group, move losers to losers group.
 *   2. Pair up teams in losers group, eliminate losers.
 * - Continue until both groups have 1 team each, then one final match.
 *
 * Time Complexity: O(log n) per test case
 * Space Complexity: O(1)
 */

import java.util.StringTokenizer

fun solve() {
    val n = readLine()!!.toInt() // Read number of teams
    var wi = n // Initial number of teams in winners group
    var lo = 0 // Initial number of teams in losers group
    var ans = 0 // Total matches counter
    
    while (true) {
        if (wi == 1 && lo == 1) { // Both groups have one team, finalize with one match
            ans++
            break
        } else if ((wi == 1 && lo == 0) || (lo == 1 && wi == 0)) { // One group is empty, can't proceed
            break
        }
        
        val a = wi / 2 // Number of matches in winners group (a teams lose and move to losers)
        wi -= a // Update winners group size after matches
        val b = lo / 2 // Number of matches in losers group (b teams get eliminated)
        lo -= b // Update losers group size after matches
        lo += a // Add losers from winners group to losers group
        
        ans += a + b // Increment total match count
    }
    
    println(ans)
}

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        solve()
    }
}


// https://github.com/VaHiX/CodeForces/