// Problem: CF 2122 A - Greedy Grid
// https://codeforces.com/contest/2122/problem/A

/*
 * Purpose: Determines if there exists an n×m grid of nonnegative integers such that no greedy path achieves the maximum value among all down/right paths.
 * 
 * Algorithm/Techniques: Greedy Grid Analysis
 * 
 * Time Complexity: O(1) per test case, as the decision is based on a simple condition check.
 * Space Complexity: O(1), only using constant extra space regardless of input size.
 */

fun main() {
    val cin = System.`in`.bufferedReader()
    val cout = System.out.bufferedWriter()
    repeat(cin.readLine().toInt()) {
        val (n,m) = cin.readLine().split(' ').map { it.toInt() }
        // The condition checks if both dimensions are greater than 1,
        // and at least one dimension is greater than 2.
        // This ensures that the grid is large enough to allow for a non-greedy maximum path.
        cout.write(if ((n>1 && m>1) && (n>2 || m>2)) "YES" else "NO")
        cout.newLine()
    }
    cout.flush()
}


// https://github.com/VaHiX/CodeForces/