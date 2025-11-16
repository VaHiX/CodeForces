// Problem: CF 2123 D - Binary String Battle
// https://codeforces.com/contest/2123/problem/D

/*
D. Binary String Battle
Algorithms/Techniques: Game theory, greedy approach, analysis of subsequence vs substring operations.

Time Complexity: O(n) per test case, where n is the length of the string s.
Space Complexity: O(1) excluding input storage.

The problem involves a game between Alice and Bob on a binary string:
- Alice (goes first) can choose any subsequence of length k and set all its characters to '0'.
- Bob (goes second) can choose any substring of length k and set all its characters to '1'.
- Alice wins if the entire string becomes zeros at any point.
- We are to determine the winner assuming both play optimally.

Key insight:
Alice wants to reduce the number of '1's in the string. 
If there are ≤ k ones, she can remove them all in one move and win immediately.
Otherwise, if k > n/2, Alice has a higher chance due to overlapping subsequences allowing her to cover more ground.
In other cases, Bob can always interfere effectively by turning back parts of the string that Alice tries to zero out.

This implementation computes the total count of '1's in the string and makes decisions based on:
- If the number of '1's is <= k → Alice wins (can eliminate all in one move).
- Else if k > n/2 → Alice wins (enough overlap in subsequences to clear the string eventually).
- Otherwise Bob wins (his ability to reset segments prevents Alice from winning).
*/
fun main() = repeat(readLine()!!.toInt()){
    var (n, k) = readLine()!!.split(' ').map {it.toInt()} // Read n and k
    var a = readLine()!! // Read the binary string
    var d = a.count{it=='1'} // Count number of '1's in the string
    var e = "Bob" // Default winner is Bob
    if(d<=k) e = "Alice" // If number of 1s <= k, Alice can clear all in one go
    else if(k>n/2) e = "Alice" // If k > n/2, overlapping subsequences allow Alice to clear the string
    println(e)
}


// https://github.com/VaHiX/CodeForces/