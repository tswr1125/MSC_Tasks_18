#!/usr/bin/env python3
def con2(x):
	arr = {'M':1000,'D':500,'C':100,'L':50,'X':10,'V':5,'I':1}
	ret = 0
	i = 0
	l = len(x)
	while i < l:
		cur = arr[x[i]]
		if i + 1 < l:
			if arr[x[i+1]] > arr[x[i]]: 
				cur = arr[x[i+1]] - arr[x[i]]
				i += 1
		ret += cur
		i += 1
	return ret
def con(x):
	ret = "";
	arr = {1000:'M',900:'CM',500:'D',400:'CD',100:'C',90:'XC',50:'L',40:'XL',10:'X',9:'IX',5:'V',4:'IV',1:'I'}
	for key,value in arr.items():
		while x >= key:
			ret += value
			x -= key;
	return ret

s = input()
if s.isdigit(): print(con(int(s)))
else: print(con2(s))
