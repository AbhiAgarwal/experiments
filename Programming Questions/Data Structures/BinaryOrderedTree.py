# A very simple implementation of a 
# Binary Tree in Python
class Node:
	left, right, data = None, None, 0
	def __init__(self, data):
		self.left = None
		self.right = None
		self.data = data

class BinaryTree:
	def __init__(self):
		self.root = None

	# initializes and returns Node class
	def addNode(self, data):
		return Node(data)

	# inserts into the tree
	def insert(self, root, data):
		if root == None:
			return self.addNode(data) # if there is no root
		else:
			if data <= root.data: # if smaller: placed on the left
				root.left = self.insert(root.left, data)
			else: # if bigger: placed on the right
				root.right = self.insert(root.right, data)
			return root

	# recursive lookup until finding
	def lookup(self, root, target):
		if root == None:
			return 0
		else:
			if target == root.data: # if target is root: return 1
				return 1
			else:
				if target < root.data: # target smaller than root: left
					return self.lookup(root.left, target)
				else: # target bigger than root: right
					return self.lookup(root.right, target)
	
	# finds minimum value, smallest value at the most left node
	def minValue(self, root):
		while(root.left != None):
			root = root.left
		return root.data

	# finds the maximum depth of the tree
	def maxDepth(self, root):
		if root == None:
			return 0
		else:
			LeftDepth = self.maxDepth(root.left)
			RightDepth = self.maxDepth(root.right)
			return max(RightDepth, LeftDepth) + 1

	# gets the size of the binary tree
	def size(self, root):
		if root == None:
			return 0
		else:
			return self.size(root.left) + self.size(root.right) + 1

	# Prints Binary Tree Inorder: Left Node Right
	def inOrderPrint(self, root):
		if root == None:
			pass
		else:
			self.inOrderPrint(root.left)
			print root.data
			self.inOrderPrint(root.right)

	# Prints tree in Reverse: Right Node Left
	def printReverseTree(self, root):
		if root == None:
			pass
		else:
			self.printReverseTree(root.right)
			print root.data
			self.printReverseTree(root.left)

# Testing our Binary Tree
if __name__ == "__main__":
	Tree = BinaryTree()
	root = Tree.addNode(5) # Root Node
	Tree.insert(root, 8) # Adding Data
	Tree.insert(root, 6) # Adding Data
	Tree.insert(root, 3) # Adding Data
	Tree.insert(root, 2) # Adding Data
	
	print "In Order Traversal:"
	Tree.inOrderPrint(root)
	print 

	print "Reverse Traversal:"
	Tree.printReverseTree(root)
	print

	print "Lets try find 8"
	print Tree.lookup(root, 8) # return 1 == Found
	print

	print "Minimum Value"
	print Tree.minValue(root)
	print

	print "Maximum Depth"
	print Tree.maxDepth(root)
	print

	print "Size:"
	print Tree.size(root)