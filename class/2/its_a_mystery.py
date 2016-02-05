# sorting alrgorithm
def mystery1(l):
    # iterate backwards
    for p in range(len(l)-1,0,-1):
        # iterate over p
        for i in range(p):
            # if current index is greater than next index
            # switch the elements
            # sets next element to current element, keep the current element
            if l[i] > l[i + 1]:
                l[i] = l[i+1]
                l[i+1] = l[i]

# rotate
def mystery2(l, n):
    # iterate over length of list
    for i in range(len(l)):
        l[i] = l[(i + n) % len(l)]
    for i in range(n):
        l[len(l) - n + i] = l[i]

def mystery3(q, d):
    # if second arg is 0, return first arg
    if d == 0:
        return q
    else:
        # recursive
        return mystery3(d, q % d)

alist = [54,26,93,17,77,31,44,55,20]
print "Original list:" + str(alist) + "\n"
mystery1(alist)
print "Mystery 1:" + str(alist) + "\n"

alist = [54,26,93,17,77,31,44,55,20]
print "Original list:" + str(alist) + "\n"
mystery2(alist, 2)
print "Mystery 2: " + str(alist) + "\n"

print "Mystery 3: " + str(mystery3(20, 8))
print mystery3(45, 8)
