# Lecture 19

Balanced Binary Search Tree

- Single Counter Clockwise Rotation
- Single Clockwise Rotation
- Double Counter Clockwise Rotation
	1. single CR(root -> right)
	2. single CCR(root)
- Double Clockwise Rotation

```
if height(right) > height(left):
	if height(right -> right) > height(right -> left):
		single CCR
	else:
		double CCR
else:
	if height(left -> right) > height(left -> left):
		single CR
	else:
		double CR
```
