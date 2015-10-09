import operator

# Make a lookup table to connect string operators to actual operations
operation_val = {
  '+' : operator.add,
  '-' : operator.sub,
  '/': operator.truediv,
  '*': operator.mul
}
operation_input = input('Please enter two numbers and an operation: ')

op_list = operation_input.split(' ')

print('%s %s %s = %s' % (op_list[0], op_list[1], op_list[2], operation_val[op_list[1]](int(op_list[0]), int(op_list[2]))))
