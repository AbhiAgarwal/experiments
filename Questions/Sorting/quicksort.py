array_x = [88, 12, 78, 87, 89, 95, 16, 82]

def QuickSort(L, U, A):
	if L >= U: return
	if A[L] < A[U]:
		print 'Made Call Swap(L, U, A)'
		swap(L, U, A)
	P = A[U]
	B = L
	T = U
	print 'P =', P, 'B =', B, 'T =', T
	while True:
		print 'Made Call Swap(B, T, A)'
		swap(B, T, A)
		while True:
			B += 1
			if (A[B] >= P): break
		while True:
			T -= 1
			if (A[T] <= P): break
		if B >= T: break
	print 'P =', P, 'B =', B, 'T =', T
	print 'Made Call Swap(L, T, A)'
	swap(L, T, A)
	print 'Called Quicksort(L, T - 1, A)'
	QuickSort(L, T - 1, A)
	print 'Called QuickSort(T + 1, U, A)'
	QuickSort(T + 1, U, A)
	print array_x

def swap(L, U, A):
	temp = A[L]
	A[L] = A[U]
	A[U] = temp

if __name__ == '__main__':
	QuickSort(0, 7, array_x)
	print array_x