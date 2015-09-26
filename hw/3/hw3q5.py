import turtle
import math

sides = [0, 0, 0]
sides[0] = int(input('Please enter side one of the triangle: '))
sides[1] = int(input('Please enter another side of the triangle: '))
sides[2] = int(input('Please enter the last side of the triangle: '))

turtle.setup(500, 500)
turtle.pendown()

a = sides[0]
b = sides[1]
c = sides[2]

a_2 = sides[0] ** 2
b_2 = sides[1] ** 2
c_2 = sides[2] ** 2

a_angle = math.degrees(math.acos((b_2 + c_2 - a_2) / (2 * b * c)))
b_angle = math.degrees(math.acos((a_2 + c_2 - b_2) / (2 * a * c)))
c_angle = math.degrees(math.acos((a_2 + b_2 - c_2) / (2 * a * b)))

turtle.forward(a)
turtle.left(180 - c_angle)
turtle.forward(b)
turtle.left(180 - a_angle)
turtle.forward(c)

turtle.penup()
