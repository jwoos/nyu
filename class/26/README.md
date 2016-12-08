# Lecture 26

Unweighted single source shortest path algorithm

| Destination | Distance |
|-------------|----------|
| 1           | 0        |
| 2           |          |
| 3           |          |
| 4           |          |
| 5           |          |
| 6           |          |
| 7           |          |
| 8           |          |
| 9           |          |

```
// unweighted
initialize all destinations to infinity
set current source to zero
insert source into queue
while queue is not empty:
	node c = top of queue
	for each edge e from c:
		if distance to e.destination = infinity:
			distance to e.destination = distance to c + 1
			push e.destination on queue
		pop top of queue

// weighted
initialize all distances to infinity
set current source distance to zero
insert source into priority queue with priority zero
while priority queue is not empty:
	node c = top of priority queue
	if distance[c] = priority:
		for each edge e from c:
		if (distance[e.destination] > distance[c] + e.cost):
			distance[e.destination] = distance[c] + e.cost)
			push e.distance to priority queue with priority = distance[e.destination]
	pop top of priority queue
```
