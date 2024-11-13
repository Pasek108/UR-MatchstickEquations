find_lhs_minus(R) :-
  between(0, 9, N1),
  between(0, 9, N2),
  R =:= N1 - N2,
  write("{ "), write(N1), write(", "), write("0"), write(", "), write(N2), write(" },"),
  write(" // "), write(N1), write("-"), write(N2), write(" = "), writeln(R),
  fail, !.

find_lhs_plus(R) :-
  between(0, 9, N1),
  between(0, 9, N2),
  R =:= N1 + N2,
  write("{ "), write(N1), write(", "), write("1"), write(", "), write(N2), write(" },"),
  write(" // "), write(N1), write("+"), write(N2), write(" = "), writeln(R),
  fail, !.

find_lhs() :-
  between(0, 9, R),
  writeln(""),
  (
  find_lhs_minus(R);
  find_lhs_plus(R)
  ),
  fail, !.

/*

Array created by using above predicates

{{
  { 0, 0, 0 }, // 0-0 = 0
  { 1, 0, 1 }, // 1-1 = 0
  { 2, 0, 2 }, // 2-2 = 0
  { 3, 0, 3 }, // 3-3 = 0
  { 4, 0, 4 }, // 4-4 = 0
  { 5, 0, 5 }, // 5-5 = 0
  { 6, 0, 6 }, // 6-6 = 0
  { 7, 0, 7 }, // 7-7 = 0
  { 8, 0, 8 }, // 8-8 = 0
  { 9, 0, 9 }, // 9-9 = 0
  { 0, 1, 0 }, // 0+0 = 0
}, {
  { 1, 0, 0 }, // 1-0 = 1
  { 2, 0, 1 }, // 2-1 = 1
  { 3, 0, 2 }, // 3-2 = 1
  { 4, 0, 3 }, // 4-3 = 1
  { 5, 0, 4 }, // 5-4 = 1
  { 6, 0, 5 }, // 6-5 = 1
  { 7, 0, 6 }, // 7-6 = 1
  { 8, 0, 7 }, // 8-7 = 1
  { 9, 0, 8 }, // 9-8 = 1
  { 0, 1, 1 }, // 0+1 = 1
  { 1, 1, 0 }, // 1+0 = 1
},{
  { 2, 0, 0 }, // 2-0 = 2
  { 3, 0, 1 }, // 3-1 = 2
  { 4, 0, 2 }, // 4-2 = 2
  { 5, 0, 3 }, // 5-3 = 2
  { 6, 0, 4 }, // 6-4 = 2
  { 7, 0, 5 }, // 7-5 = 2
  { 8, 0, 6 }, // 8-6 = 2
  { 9, 0, 7 }, // 9-7 = 2
  { 0, 1, 2 }, // 0+2 = 2
  { 1, 1, 1 }, // 1+1 = 2
  { 2, 1, 0 }, // 2+0 = 2
},{
  { 3, 0, 0 }, // 3-0 = 3
  { 4, 0, 1 }, // 4-1 = 3
  { 5, 0, 2 }, // 5-2 = 3
  { 6, 0, 3 }, // 6-3 = 3
  { 7, 0, 4 }, // 7-4 = 3
  { 8, 0, 5 }, // 8-5 = 3
  { 9, 0, 6 }, // 9-6 = 3
  { 0, 1, 3 }, // 0+3 = 3
  { 1, 1, 2 }, // 1+2 = 3
  { 2, 1, 1 }, // 2+1 = 3
  { 3, 1, 0 }, // 3+0 = 3
},{
  { 4, 0, 0 }, // 4-0 = 4
  { 5, 0, 1 }, // 5-1 = 4
  { 6, 0, 2 }, // 6-2 = 4
  { 7, 0, 3 }, // 7-3 = 4
  { 8, 0, 4 }, // 8-4 = 4
  { 9, 0, 5 }, // 9-5 = 4
  { 0, 1, 4 }, // 0+4 = 4
  { 1, 1, 3 }, // 1+3 = 4
  { 2, 1, 2 }, // 2+2 = 4
  { 3, 1, 1 }, // 3+1 = 4
  { 4, 1, 0 }, // 4+0 = 4
}, {
  { 5, 0, 0 }, // 5-0 = 5
  { 6, 0, 1 }, // 6-1 = 5
  { 7, 0, 2 }, // 7-2 = 5
  { 8, 0, 3 }, // 8-3 = 5
  { 9, 0, 4 }, // 9-4 = 5
  { 0, 1, 5 }, // 0+5 = 5
  { 1, 1, 4 }, // 1+4 = 5
  { 2, 1, 3 }, // 2+3 = 5
  { 3, 1, 2 }, // 3+2 = 5
  { 4, 1, 1 }, // 4+1 = 5
  { 5, 1, 0 }, // 5+0 = 5
}, {
  { 6, 0, 0 }, // 6-0 = 6
  { 7, 0, 1 }, // 7-1 = 6
  { 8, 0, 2 }, // 8-2 = 6
  { 9, 0, 3 }, // 9-3 = 6
  { 0, 1, 6 }, // 0+6 = 6
  { 1, 1, 5 }, // 1+5 = 6
  { 2, 1, 4 }, // 2+4 = 6
  { 3, 1, 3 }, // 3+3 = 6
  { 4, 1, 2 }, // 4+2 = 6
  { 5, 1, 1 }, // 5+1 = 6
  { 6, 1, 0 }, // 6+0 = 6
}, {
  { 7, 0, 0 }, // 7-0 = 7
  { 8, 0, 1 }, // 8-1 = 7
  { 9, 0, 2 }, // 9-2 = 7
  { 0, 1, 7 }, // 0+7 = 7
  { 1, 1, 6 }, // 1+6 = 7
  { 2, 1, 5 }, // 2+5 = 7
  { 3, 1, 4 }, // 3+4 = 7
  { 4, 1, 3 }, // 4+3 = 7
  { 5, 1, 2 }, // 5+2 = 7
  { 6, 1, 1 }, // 6+1 = 7
  { 7, 1, 0 }, // 7+0 = 7
}, {
  { 8, 0, 0 }, // 8-0 = 8
  { 9, 0, 1 }, // 9-1 = 8
  { 0, 1, 8 }, // 0+8 = 8
  { 1, 1, 7 }, // 1+7 = 8
  { 2, 1, 6 }, // 2+6 = 8
  { 3, 1, 5 }, // 3+5 = 8
  { 4, 1, 4 }, // 4+4 = 8
  { 5, 1, 3 }, // 5+3 = 8
  { 6, 1, 2 }, // 6+2 = 8
  { 7, 1, 1 }, // 7+1 = 8
  { 8, 1, 0 }, // 8+0 = 8
}, {
  { 9, 0, 0 }, // 9-0 = 9
  { 0, 1, 9 }, // 0+9 = 9
  { 1, 1, 8 }, // 1+8 = 9
  { 2, 1, 7 }, // 2+7 = 9
  { 3, 1, 6 }, // 3+6 = 9
  { 4, 1, 5 }, // 4+5 = 9
  { 5, 1, 4 }, // 5+4 = 9
  { 6, 1, 3 }, // 6+3 = 9
  { 7, 1, 2 }, // 7+2 = 9
  { 8, 1, 1 }, // 8+1 = 9
  { 9, 1, 0 }, // 9+0 = 9
}};

N1  - first number of LHS
OP  - opeartion + or -
N2  - second number of LHS
R   - RHS, result of operation on N1 and N2
LHS - left-hand side of an equation
RHS - right-hand side of an equation

       LHS       =  RHS
  N1   OP    N2  =   R
(0-9) (+-) (0-9) = (0-9)

Observations:
- There is always 11 LHS combinations for each RHS
- For substraction:
  - N1 goes from RHS to 9
  - N2 goes from 0 to 9-RHS
- For addition:
  - N1 goes from 0 to RHS
  - N2 goes from RHS to 0

Genaration of equation:
R  = random 0 to 9
OP = random 0 to 1

if OP == 0:
   N1 = random R to 9
   N2 = N1 - R

if OP == 1:
   N1 = random 0 to R
   N2 = R - N1

*/
