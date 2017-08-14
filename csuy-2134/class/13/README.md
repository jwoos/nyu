# Lecture 13

### Stacks
Last in first out

| methods | list | vector      |
|---------|------|-------------|
| top     | O(1) | O(1)        |
| push    | O(1) | O(1) / O(n) |
| pop     | O(1) | O(1)        |
| isempty | O(1) | O(1)        |
| clear   | O(n) | O(1)        |

use list because push will be called a lot more often than clear


### call stack
1. If the character is not relevant, continue
2. If the character is "open", push it on the stack
3. If the character is "close", examine the top of the stack for a match
	- if not match, syntax error
	- pop the "open" from the stack
4. when there is no more input, the stack must be empty


2 + 3 * 4 - 2 = 12

Precedence
- PEMDAS
Associativity
- order of operations for two adjacent operators of the same precedence level

eps = smallest float
eps / 2 = eps
(eps / 2) + (eps / 2) = eps
eps + eps = eps

### steps for infix to postfix
1. if the item is an operand, output it
2. if the item is an open parentheses, push it on the stack
3. if the item is a closed parentheses, pop all the operators on the stack to output until the open parentheses, which we then remove
4. if the item is a higher precedence than the item on the top of the stack, push it
	- if they are the same precedence, use associativity, left associative means the item on the stack has higher precedence
5. if the item has a lower precedence, than the item on the stack, pop and send to output until this item can be pushed on the stack
6. when input finishes, pop and send all items on the stack to output

### steps for evaluating postfix to a value
1. if the item is an operand, push it
2. if the item is an operator, pop two items from the stack, perform the operaion (the second item popped is the left hand sude if the operation), push the result
3. when the input is done, the value will be on the top of the stack
