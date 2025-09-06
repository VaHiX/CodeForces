# Contest 1510, Problem A: ASCII Automata Art
# URL: https://codeforces.com/contest/1510/problem/A

import sys
from collections import deque


def box_letters(term):
    length = len(term)
    
    hyps = '-'*(length+2)
    
    return [f"+{hyps}+",
            f"+ {term} +",
            f"+{hyps}+"]


def apply_plus(box):
    length = len(box[0])
    
    res = []
    res.append(f"   {box[0]}   ")
    res.append(f"+->{box[1]}->+")
    
    for i in range(2, len(box)):
        res.append(f"|  {box[i]}  |")
    
    res.append(f"|{' '*(length+4)}|")
    res.append(f"+<{'-'*(length+3)}+")
    
    return res


def apply_qm(box):
    length = len(box[0])
    
    res = []
    res.append(" "*(length+6))
    res.append("+"+"-"*(length+3)+">+")
    res.append("|"+" "*(length+4)+"|")
    res.append("|  "+box[0]+"  |")
    res.append("+->"+box[1]+"->+")
    
    for i in range(2, len(box)):
        res.append("   "+box[i]+"   ")
    
    return res


def apply_ast(box):
    length = len(box[0])
    
    res = []
    res.append(" "*(length+6))
    res.append("+"+"-"*(length+3)+">+")
    res.append("|"+" "*(length+4)+"|")
    res.append("|  "+box[0]+"  |")
    res.append("+->"+box[1]+"->+")
    
    for i in range(2, len(box)):
        res.append("|  "+box[i]+"  |")
    
    res.append("|"+" "*(length+4)+"|")
    res.append("+<"+"-"*(length+3)+"+")
    
    return res


def connect_atoms(boxes):
    res = []
    
    height = max(len(box) for box in boxes)
    
    between = "  "
    for i in range(height):
        if i == 1:
            between = "->"
        res.append(between.join(box[i] if i < len(box) else " "*len(box[0]) for box in boxes))
        if i == 1:
            between = "  "
    
    return res


def join_terms(boxes):
    res = []
    
    length = max(len(box[0]) for box in boxes)
    
    border = "|"
    
    for i, box in enumerate(boxes):
        rem_len = length - len(box[0])
        blanks = ' '*(rem_len+2)
        
        if i == 0:
            border = " "
        
        res.append(f"{border}  {box[0]}{blanks}{border}")
        res.append(f"+->{box[1]}{'-'*(rem_len)}->+")
        
        if i == 0:
            border = "|"
        
        if i == len(boxes)-1:
            border = " "
        
        for j in range(2, len(box)-1):
            res.append(f"{border}  {box[j]}{blanks}{border}")
        
        res.append(f"{border}  {box[-1]}{blanks}{border}")
        
        if i != len(boxes)-1:
            res.append(f"|{' '*(length+4)}|")
    
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
        
        stk_box = []
        bef_oper = 0
        
        enter = idx
        
        while idx < len(expr):
            ltr = expr[idx]
            
            if "A" <= ltr <= "Z":
                j = idx+1
                
                while j < len(expr) and "A" <= expr[j] <= "Z":
                    j += 1
                if j < len(expr) and expr[j] in "+?*":
                    j -= 1
                
                term_letters = expr[idx:j]
                if len(term_letters) != 0:
                    stk_box.append(box_letters(term_letters))
                if j+1 < len(expr) and "A" <= expr[j] <= "Z" and expr[j+1] in "+?*":
                    stk_box.append(box_letters(expr[j]))
                    j += 1
                idx = j
                continue
            
            if ltr in "+?*":
                prev_box = stk_box.pop()
                stk_box.append(apply_oper(prev_box, ltr))
            
            if ltr == "(":
                idx += 1
                stk_box.append(_eval())
                continue
            
            if ltr == ")":
                idx += 1
                break
            
            if ltr == "|":
                connected = connect_atoms(stk_box[bef_oper:])
                stk_box = stk_box[:bef_oper] + [connected]
                bef_oper = len(stk_box)
            
            idx += 1
        
        stk_box = stk_box[:bef_oper] + [connect_atoms(stk_box[bef_oper:])]
        
        return join_terms(stk_box) if len(stk_box) >= 2 else stk_box[0]
    
    return _eval()


if __name__ == "__main__":
    res = eval_expr(input())
    
    print(len(res), len(res[0])+6)
    for i in range(len(res)):
        if i == 1:
            print(f"S->{res[i]}->F")
        else:
            print(f"   {res[i]}   ", end="" if i == len(res)-1 else "\n")
