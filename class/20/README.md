# Lecture 20

Red-Black trees
1. ever node is colored red or black
2. the root is black
3. if a node is red, its children must be black
4. every path from root to a null must go through the same number of black nodes

How to implement RBTree
1. new nodes are red
2. if the new node's parent is black, done
3. if the new node's parent is red
	- if the "uncle" is black (null is the same as black)
		- if the new node is "outside", single rotation at grandparent
		- if the new node is "inside", double rotation at grandparent
	- if the "uncle" is red - AVOID
4. as you go down the tree, look for black parent with two red nodes and recolor to red parent with two black children.  rotate as necessary
