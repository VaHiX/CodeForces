// Problem: CF 2147 A - Shortest Increasing Path
// https://codeforces.com/contest/2147/problem/A

/**
 * Problem: Shortest Increasing Path
 * 
 * Description:
 * You start at (0, 0) and want to reach (x, y). Each step must be in positive direction along x or y axis,
 * alternating between x and y axes. Odd-numbered steps are on x-axis; even-numbered on y-axis.
 * Step lengths must strictly increase. Find minimum steps needed or -1 if impossible.
 * 
 * Algorithm:
 * Based on the nature of movement (alternating axes with increasing step sizes):
 * - If y > x, then you can go directly in 2 moves: x-step, then y-step.
 * - Otherwise, check if it's possible:
 *   - If y > 1 and (x - y) > 1, then 3 steps are possible.
 *   - Else impossible (-1).
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine().toInt()
    val sb = StringBuilder()
    
    repeat(t) {
        val st = StringTokenizer(br.readLine())
        val x = st.nextToken().toLong() // x coordinate target
        val y = st.nextToken().toLong() // y coordinate target
        
        val ans = when {
            y > x -> 2 // If y > x, we can directly move y units in the second step after moving x in first
            else -> {
                val limit = x - y // difference between x and y coordinates
                if (y > 1 && limit > 1) 3 else -1 // check feasibility for 3-step path or impossibility
            }
        }
        sb.append(ans).append('\n')
    }
    print(sb.toString())
}


// https://github.com/VaHiX/CodeForces/