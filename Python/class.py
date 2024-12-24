
#%%
#c/c++
# int / short / double ...
#  char/ string
# 연속 메모리 : array
# 집함 : struct
# 기능 : function
# 모듈 : 클래스

# int : 정수  / float 실수, str : 문자열...
#  char/ string
# 연속 메모리 : list ... container
#           [everything, ...]
# 집함 : list
# 기능 : function
# 모듈 : 클래스
aa = 123
print('aa= ', aa, '    type = ', type(aa))
aa = 123.000
print('aa = ', aa, '    type = ', type(aa))
aa = '123.000'
print('aa = ', aa, '    type = ', type(aa))
# %%

#list

aa = [1,2,3]
print('aa= ', aa, '    type = ', type(aa))
aa[0] = aa[0] + 1
print('aa = ', aa, '    type = ', type(aa))
aa[1] = aa[1] + 1
print('aa = ', aa, '    type = ', type(aa))
aa[2] = aa[2] + 1
print('aa = ', aa, '    type = ', type(aa))

#tuple ... data container = lst와 비슷하지만 read only
aa = (1,2,3) # []가 아님
print('aa = ', aa, '    type = ', type(aa))
# aa[0] = aa[0] + 1 => error

#dic... dictionary ... data container
# => aa = {'key' : 'value'}
aa = {'ㄱ': '가족','ㅎ' : '홍길동'}
print('aa = ', aa, '    type = ', type(aa))
aa = {'a' :'apple', 'g' : 'google'}
aa['a'] = 'amazon'
aa  = {0 :'0000', 1: '0001', 2:'0010'}
aa[0] = '0x00'
# %%

aa = True
aa = False

#len()
#type()
#print()

#c++
#int* pArr = new int[10]
#array_size = sizeof(pArr)/sizeof(pArr[0])
#vector<int> vArr;
#vArr.push_back(10);
#vArr.push_back(20);
#vArr.push_back(30);
#vArr_size = vArr.size()
aa = [1,2,3,4,5]
print('aa size = ', len(aa))
# %%
x=3
y = x*2
y = x**3

x=9
y = x/2
y = x//2

#%%
hello = 'hello'
world = 'world'
print(hello)
print(len(hello))
print(world)
print(len(world))
hw = hello + ' ' + world
print(hw)
print(len(hw))
fmt = '%s %s %d' % (hello, world, 777)
print(fmt, '     type = ' , type(fmt))
fmt = f'{hello:10s} + {world:10s} + {77777:010d}'
print(fmt, '     type = ' , type(fmt))
fmt = f'{hello:10s} + {world:10s} + {77777:010d}'

import numpy as np
print(np.pi)
fmt = f'{hello:10s} + {world:10s} + {123123:0.6f}'
print(fmt, '     type = ' , type(fmt))

# %%
s = "hello"
print(s.capitalize())
print(s.upper())
print(s.rjust(7))
print(s.ljust(7))
print(s.center(7))
print(s.replace('l', '(ell)'))

print('   wow'.strip())

print(s[0:1+1]) # 0<= s <2
print(s[1:2+1])
print(s[2:3+1])
print(s[4])


for i in range(0,9+1,1):
    print(s[0:i+1])
# %%
nums = list(range(5))
print(nums)
print(nums[2:4])
print(nums[2:])
print(nums[:2])
print(nums[:])
print(nums[ :-1])
nums[2:4] = [8,9]
print(nums)

# %%



cond = True
if cond and True:
    if cond or False:
        print('True')
    else:
        print('False')
else:
    print('False')
# %%

for i in range(0,10,1): #for(int i = 0; i < 10 ; i++)
    print('i = ', i)


aa = [1,2,3,4,5,6,7,8,9,10]
for data in aa:
    print(data)
for i, data in enumerate(aa):
    if i%2 != 0:
        print(f'aa[{i}] = {data}')

print('next')
for i in range(0, len(aa),2):
    print(f'aa[{i}] = {aa[i]}')

# %%

for rows in range(1,9+1, 1):
    for cols in range(1, 9+1, 1):
        result = rows*cols
        print(f'{cols:1d} x {rows:1d} = {result:-2d}', end=' | ')
    print('\n')
    
# %%
xs = [3,1,2]
print(xs, xs[2])
print(xs[-2])
xs[2] = 'foo' # change
print(xs)
xs.append('bar') #add
print(xs)
x = xs.pop()  # 마지막 값을 반환하고 뺌
print(x,xs) # 그래서 x에 boo가 추가돼고 xs에서 boo가 제거된거임
#%%
nums = [0,1,2,3,4]
print('nums = ', nums, '   type = ', type(nums))
nums = list(range(5))
print('nums = ', nums, '   type = ', type(nums))
suqares = [x**2 for x in nums]
print('suqares = ', suqares, '   type = ', type(suqares))

'''
int* pSquare = new int[n];
std::vector<int> vSequares;
for(int i = 0; i < 5; i++)
{
    int tmp = nums[i]*nums[i];
    int temp = std::pow(nums[i],2.0);
    vSequares.push_back(tmp);
    pSquare[i] = tmp;
}
'''
# %%

animals = ['cat', 'dog', 'monkey', 1,2,3, 1.123,2.123,3.123]
for animal in animals:
    print(animal)
for idx, animal in enumerate(animals):
    print('#%d : %s' % (idx+1, animal))
# %%

step = list(range(1,10))
dan = list(range(1,10))


startdan = 2
finishdan= 9
startstep = 1
finishstep = 9

ggd = [
    f'{dan}x{step} = {dan*step}' 
       for dan in range(startdan, finishdan +1)
       for step in range(startstep, finishstep + 1)]

print(ggd[:9])
print(ggd[9:18])
print(ggd[18:27])
print('ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ')
for i in range(0, finishdan- startdan+1):
    print(ggd[(i)*finishstep:(i+1)*finishstep])

 #%%

def sum_div(a,b):
    return (a+b,a/b)
def calc(a,b):
    return (a+b, a-b, a*b, a/b)

a = 10
b = 20
c,d = sum_div(a,b)

print(f'{c} = {a}+{b}')
print(f'{d} = {a}/{b}')

c,d,e,f = calc(a,b)
print(f'{c} = {a}+{b}')
print(f'{d} = {a}-{b}')
print(f'{e} = {a}*{b}')
print(f'{f} = {a}/{b}')
print('ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ')
print('list 함수')
def calc_list(a,b):
    return [a+b, a-b, a*b, a/b]

cc = calc_list(a,b)
print(f'{cc[0]} = {a}+{b}')
print(f'{cc[1]} = {a}-{b}')
print(f'{cc[2]} = {a}*{b}')
print(f'{cc[3]} = {a}/{b}')
print(cc)
# %%
def GuGuDan(a,b):
    return f'{a} x {b} = {a*b}'

danset = list(range(1,10))
stepset = list(range(1,10))

ggd = [f'{GuGuDan(dan,step)}' for dan in range(1,10,1)
for step in range(1,10,1)]

print(ggd[:9])
print(ggd[9:18])



