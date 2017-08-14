import math

class Point:
	def __init__(self, new_x, new_y):
		self.x = new_x
		self.y = new_y

	def __str__(self):
		return '(' + str(self.x) + ', ' + str(self.y) + ')'

	def distance(self):
		return ((self.x ** 2) + (self.y ** 2)) ** (1/2)

class Circle:
	def __init__(self, center, radius):
		self.center = center
		self.radius = radius

	def __str__(self):
		return 'Center: ' + str(self.center) + ' | ' + 'Radius: ' + str(self.radius)
	
	def area(self):
		return (self.radius ** 2) * math.pi

	def circumference(self):
		return self.radius * 2 * math.pi
