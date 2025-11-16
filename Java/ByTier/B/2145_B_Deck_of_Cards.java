// Problem: CF 2145 B - Deck of Cards
// https://codeforces.com/contest/2145/problem/B

/**
 * Problem: B. Deck of Cards
 * 
 * Purpose: 
 * Given a deck of cards numbered from 1 to n, and a sequence of k actions,
 * determine for each card whether it remains in the deck (+), has been removed (-),
 * or might be both (?). The actions can remove either top (0), bottom (1), or any (2).
 * 
 * Algorithm:
 * - Use two pointers approach to simulate removing cards from start and end.
 * - For each character in moves string: 
 *   - if '0': remove from front
 *   - if '1': remove from back
 *   - if '2': increment counter of uncertain removals
 * - Once all fixed actions are processed:
 *   - If uncertain moves exceed remaining cards, all remaining cards must be removed.
 *   - Else, assign '?' to the middle portion and '-' to others.
 * 
 * Time Complexity: O(n) per test case, since each card is visited at most once in main loop
 * Space Complexity: O(n) for storing result array and input strings
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;
public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        int t = Integer.parseInt(br.readLine());
        while(t-->0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int len = Integer.parseInt(st.nextToken());
            int noOfMoves = Integer.parseInt(st.nextToken());
            String moves = new StringTokenizer(br.readLine()).nextToken();
            char[] result = new char[len];
            Arrays.fill(result, '+'); // Initially all cards are in deck ('+')
            int start=0, end=len-1;
            int cnt=0; int twoCnt=0;
            while(start<=end && cnt<noOfMoves) {
                if(moves.charAt(cnt)=='0') {
                    result[start++] = '-'; // Remove from front, mark as removed
                } else if(moves.charAt(cnt)=='1') {
                    result[end--]='-'; // Remove from back, mark as removed
                } else {
                    twoCnt++; // Count uncertain removals
                }
                cnt++;
            }
                if(twoCnt>end-start) { // If more uncertain moves than available cards
                    while(start<=end){
                        result[start++]='-';
                        result[end--]='-';
                    }
                }
             else {
                while(start<=end && twoCnt-->0){ // Assign '?' to middle portion
                    result[start++]='?';
                    result[end--]='?';
                }
            }
         pw.println(new String(result));
        }
        pw.flush();
    }
}


// https://github.com/VaHiX/CodeForces/