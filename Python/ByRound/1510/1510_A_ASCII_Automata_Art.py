# Problem: CF 1510 A - ASCII Automata Art
# https://codeforces.com/contest/1510/problem/A

"""
Algorithm/Techniques: Recursive descent parsing, string manipulation, stack-based expression evaluation
Time Complexity: O(n^2) where n is the length of input string due to repeated string operations and nested parsing
Space Complexity: O(n^2) for storing intermediate boxes and recursion stack in worst case

This code parses a regular expression-like input string and converts it into an ASCII art representation
of a finite automaton. It handles concatenation, alternation (|), and Kleene star (+, ?, *) operators.
The parsing is done recursively with a stack-based approach to manage nested parentheses and operator precedence.
"""

def box_letters(term):
    length = len(term)
    hyps = "-" * (length + 2)
    return [f"+{hyps}+", f"+ {term} +", f"+{hyps}+"]


def apply_plus(box):
    length = len(box[0])
    res = []
    res.append(f"   {box[0]}   ")  # Top border with padding
    res.append(f"+->{box[1]}->+")  # Middle line with arrows
    for i in range(2, len(box)):   # Body lines
        res.append(f"|  {box[i]}  |")
    res.append(f"|{' '*(length+4)}|")  # Bottom padding line
    res.append(f"+<{'-'*(length+3)}+")  # Bottom border with arrow
    return res


def apply_qm(box):
    length = len(box[0])
    res = []
    res.append(" " * (length + 6))  # Top padding
    res.append("+" + "-" * (length + 3) + ">+")  # Top arrow border
    res.append("|" + " " * (length + 4) + "|")  # Middle padding
    res.append("|  " + box[0] + "  |")  # Content line
    res.append("+->" + box[1] + "->+")  # Bottom arrow
    for i in range(2, len(box)):  # Body lines
        res.append("   " + box[i] + "   ")
    return res


def apply_ast(box):
    length = len(box[0])
    res = []
    res.append(" " * (length + 6))  # Top padding
    res.append("+" + "-" * (length + 3) + ">+")  # Top arrow
    res.append("|" + " " * (length + 4) + "|")  # Middle padding
    res.append("|  " + box[0] + "  |")  # Content line
    res.append("+->" + box[1] + "->+")  # Bottom arrow
    for i in range(2, len(box)):  # Body lines
        res.append("|  " + box[i] + "  |")
    res.append("|" + " " * (length + 4) + "|")  # Middle padding
    res.append("+<" + "-" * (length + 3) + "+")  # Bottom arrow
    return res


def connect_atoms(boxes):
    res = []
    height = max(len(box) for box in boxes)  # Max height of all boxes
    between = "  "  # Space between boxes initially
    for i in range(height):
        if i == 1:  # Special handling for middle row
            between = "->"
        res.append(
            between.join(box[i] if i < len(box) else " " * len(box[0]) for box in boxes)
        )
        if i == 1:  # Restore normal spacing after middle row
            between = "  "
    return res


def join_terms(boxes):
    res = []
    length = max(len(box[0]) for box in boxes)  # Width of widest box
    border = "|"  # Border character
    for i, box in enumerate(boxes):
        rem_len = length - len(box[0])  # Remaining space to pad
        blanks = " " * (rem_len + 2)  # Padding spaces
        if i == 0:
            border = " "  # No left border for first box
        res.append(f"{border}  {box[0]}{blanks}{border}")  # Top line
        res.append(f"+->{box[1]}{'-'*(rem_len)}->+")  # Middle line with connecting dashes
        if i == 0:
            border = "|"
        if i == len(boxes) - 1:
            border = " "  # No right border for last box
        for j in range(2, len(box) - 1):  # Body lines
            res.append(f"{border}  {box[j]}{blanks}{border}")
        res.append(f"{border}  {box[-1]}{blanks}{border}")  # Bottom line
        if i != len(boxes) - 1:
            res.append(f"|{' '*(length+4)}|")  # Empty line between terms
    return res


def apply_oper(box, oper):
    if oper == "+":
        return apply_plus(box)
    if oper == "?":
        return apply_qm(box)
    if oper == "*":
        return apply_ast(box)


def eval_expr(expr: str):
    idx = 0

    def _eval():
        nonlocal idx
        stk_box = []  # Stack for holding box representations
        bef_oper = 0  # Position where last operator appeared
        enter = idx  # Track start position
        while idx < len(expr):
            ltr = expr[idx]
            if "A" <= ltr <= "Z":  # Letter detected
                j = idx + 1
                while j < len(expr) and "A" <= expr[j] <= "Z":  # Parse entire sequence of letters
                    j += 1
                if j < len(expr) and expr[j] in "+?*":  # If next char is an operator
                    j -= 1  # Adjust to not include operator yet
                term_letters = expr[idx:j]  # Extract term
                if len(term_letters) != 0:
                    stk_box.append(box_letters(term_letters))  # Convert to box format
                if j + 1 < len(expr) and "A" <= expr[j] <= "Z" and expr[j + 1] in "+?*":
                    stk_box.append(box_letters(expr[j]))
                    j += 1
                idx = j
                continue
            if ltr in "+?*":  # Operator handling
                prev_box = stk_box.pop()  # Pop previous box
                stk_box.append(apply_oper(prev_box, ltr))  # Apply operator function
            if ltr == "(":  # Parentheses handling
                idx += 1
                stk_box.append(_eval())  # Recursive call for nested expression
                continue
            if ltr == ")":  # End of parentheses
                idx += 1
                break
            if ltr == "|":  # Alternation handling
                connected = connect_atoms(stk_box[bef_oper:])  # Connect boxes up to last operator
                stk_box = stk_box[:bef_oper] + [connected]  # Replace part with combined result
                bef_oper = len(stk_box)  # Update operator position
            idx += 1
        stk_box = stk_box[:bef_oper] + [connect_atoms(stk_box[bef_oper:])]  # Connect remaining terms
        return join_terms(stk_box) if len(stk_box) >= 2 else stk_box[0]  # Return joined terms or single term

    return _eval()


if __name__ == "__main__":
    res = eval_expr(input())  # Parse input string
    print(len(res), len(res[0]) + 6)  # Output height and width
    for i in range(len(res)):
        if i == 1:  # Special handling for second row
            print(f"S->{res[i]}->F")
        else:
            print(f"   {res[i]}   ", end="" if i == len(res) - 1 else "\n")  # Print line with padding


# https://github.com/VaHiX/CodeForces/