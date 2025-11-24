// Problem: CF 2151 B - Incremental Path
// https://codeforces.com/contest/2151/problem/B

/*
 * Problem: B. Incremental Path
 * Purpose: Simulate a process where multiple people follow a sequence of commands,
 *          starting from cell 1, and coloring the last visited cell black.
 *          Track all final black cells after executing each prefix of commands.
 *
 * Algorithms/Techniques:
 *   - Simulation with two types of movements (A = next cell, B = next white cell)
 *   - Efficient handling of initial black cells to avoid full simulation
 *   - Use of ArrayList to store the final black cell positions
 *
 * Time Complexity: O(n + m) per test case, where n is number of commands and m is number of initial black cells.
 * Space Complexity: O(m) for storing the initial black cells.
 */
import java.util.*;
public class Main
{
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt();
		while(t-->0){
		    int l=sc.nextInt(); // length of command string
		    int n=sc.nextInt(); // number of initially black cells
		    String s=sc.next(); // command string
		    int []b=new int[n]; // array of initial black cell positions
		    for(int i=0;i<n;i++)b[i]=sc.nextInt();
		    int last=1; // current position, starts at 1
		    int i=0; // index for command string
		    int j=0; // index for black cells
		    ArrayList<Integer>a1=new ArrayList<>(); // list to store final black cell positions
		    while(i<l||j<n){
		        if(i<l){ // if there are more commands to process
		            if(s.charAt(i)=='A'){ // if command is A (move to next cell)
		                last+=1; // move one step forward
		                while(j<n&&last>=b[j]){ // while we haven't processed all black cells and current position >= black cell
		                    if(last!=b[j]) a1.add(b[j]); // add black cell if it's not the same as current position
		                    j++; // move to next black cell
		                }
		                a1.add(last); // record current position as black after moving
		            }
		            else { // if command is B (move to next white cell)
		                last++; // take one step forward
		                while(j<n&&last>=b[j]){ // while we haven't processed all black cells and current position >= black cell
		                   a1.add(b[j]); // add black cell to result
		                   if(b[j]==last) last++; // if the black cell is at current position, move past it
		                   j++; // move to next black cell
		                }
		                a1.add(last); // record current position as black after moving
		                 last++; // take another step (additional move when B command is applied)
		                  while(j<n&&last>=b[j]){ // process remaining black cells
		                    a1.add(b[j]); // add black cell to result
		                    if(b[j]==last) last++; // move past the black cell if needed
		                   j++; // move to next black cell
		                }
		            }
		        }
		        else { // all commands processed, but there are still black cells left
		            a1.add(b[j]); // add remaining black cells one by one
		            j++;
		        }
		        i++; // process next command
		    }
		    System.out.println(a1.size()); // print number of final black cells
		    for(int a:a1){ // print each black cell
		        System.out.print(a+" ");
		    }
		    System.out.println(); // newline after output per test case
		}
	}
}


// https://github.com/VaHiX/CodeForces/