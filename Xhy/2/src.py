def toRnum(num):
    if(num<=0):
        print("Please input a positive number")
    else:
        ret=""
        for i in range(13):
            while(num >= nums[i]):
                num -= nums[i]
                ret += rnums[i]
        print(ret)

#似乎有bug
def toNum(rnum):
    rnum = rnum.upper()
    ret=0
    length = len(rnum)
    jump =-1
    for i in range(length):
        if(i == jump):
            continue
        else:
            if(i<length-1):
                if(dic[rnum[i]] < dic[rnum[i+1]]):
                    ret += dic[rnum[i+1]]-dic[rnum[i]]
                    jump=i+1
                else:
                    ret += dic[rnum[i]]
            else:
                 ret += dic[rnum[i]]

    print(str(ret))


nums=[1000,900,500,400,100,90,50,40,10,9,5,4,1]
rnums=["M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"]
dic={"M":1000,"D":500,"C":100,"L":50,"X":10,"V":5,"I":1}

text = input("Please input number by your counting method:\n")
try:
    num=int(text)
    toRnum(num)
except ValueError:
   toNum(text)