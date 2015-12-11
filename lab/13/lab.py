class BankAccount:
	def __init__(self, account, bal):
		self.account_number = account
		self.balance = bal
	
	def withdraw(self, amount):
		if self.balance >= amount:
			self.balance -= amount
		else:
			print('Insufficient funds')
		return self.balance
	
	def deposit(self, amount):
		self.balance += amount
		return self.balance

	def getbalance(self):
		return self.balance

x = BankAccount('ANACC1', 100)
print(x.account_number)
print(x.balance)
x.deposit(700)
print(x.balance)
