// Problem: CF 2145 C - Monocarp's String
// https://codeforces.com/contest/2145/problem/C

/*
C. Monocarp's String

Algorithm: 
This problem uses a prefix sum technique with a balance tracking approach. We transform the string into a balance array where 'a' contributes +1 and 'b' contributes -1. The goal is to find the shortest substring such that removing it makes the remaining string have equal counts of 'a' and 'b'. 

We compute suffix balances to know what balance we need to reach at any index. Then, for each prefix, we check if there exists a previous prefix which when removed results in a balanced string (i.e., equal number of a's and b's).

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n), due to storing the balance arrays.

*/
fun main() {
    val cin = System.`in`.bufferedReader()
    val cout = System.out.bufferedWriter()
    repeat(cin.readLine().toInt()) {
        val n = cin.readLine().toInt()
        val s = cin.readLine()
        var ans = n
        val acnt = s.count { it == 'a' }
        val bcnt = n - acnt
        if (acnt == bcnt) ans = 0  // Already balanced
        else if (acnt == 0 || bcnt == 0) {
            ans = -1  // All a's or all b's, impossible to balance
        } else {
            val suffbal = IntArray(n + 1)  // Suffix balances: suffbal[i] is balance from index i to end
            var bal = 0
            for (i in n - 1 downTo 0) {
                bal += if (s[i] == 'a') 1 else -1  // Add 1 for 'a', subtract 1 for 'b'
                suffbal[i] = bal
            }
            val balances = IntArray(2 * n) { -2 }  // Index mapping for balance values to first occurrence
            balances[n] = -1  // Initial balance of 0 at index -1 (before start)
            bal = 0  // Current balance while traversing prefix
            for (r in 0 until n) {
                val targetbal = -suffbal[r + 1]  // What balance we need to reach at this point
                val l = balances[n + targetbal]
                if (l != -2) ans = minOf(ans, r - l)  // Update minimum length if valid
                bal += if (s[r] == 'a') 1 else -1  // Update current balance
                balances[n + bal] = r  // Store first occurrence of this balance
            }
        }
        if (ans == n) ans = -1  // If we had to remove entire string
        cout.write("$ans\n")
    }
    cout.flush()
}


// https://github.com/VaHiX/CodeForces/