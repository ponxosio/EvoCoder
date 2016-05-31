class Test(object):

	def __init__(self, name):
		self.name = name[0];
		
	def saluda(self,a):
		print str(self.name) + ": " + str(a.getI());