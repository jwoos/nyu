# Lecture 23

### Priority Queue

| Method  | complexity |
|---------|------------|
| top     | O(1)       |
| push    | O(log(n))  |
| pop     | O(log(n))  |
| clear   |            |
| isEmpty | O(1)       |

Use a binary tree, the parents must have a higher priority than the children

Use an array but in a tree like way - the current index must be greater than the element in 2 * index
