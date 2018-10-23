#!/usr/bin/env python3
def con(x):
	ret = "";
	arr = {1000:'M',900:'CM',500:'D',400:'CD',100:'C',90:'XC',50:'L',40:'XL',10:'X',9:'IX',5:'V',4:'IV',1:'I'}
	for key,value in arr.items():
		while x >= key:
			ret += value
			x -= key;
	return ret
x = int(input())
print(con(x))
