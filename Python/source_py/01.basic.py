
#%%
#c/c++
# int / short / double / ...
# char / string
# 연속메모리 : array
# 집합 : struct
# 기능 : function
# 모듈 : class 

#python
# int : 정수, float 실수, str : 문자열
# 연속메모리 : list ... container
#          [everything, ..]
# 집합 : list
# 기능 : function
# 모듈 : class 
# %%

aa = 123
print('aa = ', aa, '   type = ', type(aa))
aa = 123.000
print('aa = ', aa, '   type = ', type(aa))
aa = '123.000'
print('aa = ', aa, '   type = ', type(aa))
# %%

#array
#list ... data container
#tuple ... data container ... read only
#dict ... dictionary ... data container ... read/write/searching

aa = [1,2,3]
print('aa = ', aa, '   type = ', type(aa))
aa[0] = aa[0]+1 # data modified read/write
print('aa = ', aa, '   type = ', type(aa))
aa[1] = aa[1]+1
print('aa = ', aa, '   type = ', type(aa))
aa[2] = aa[2]+1
print('aa = ', aa, '   type = ', type(aa))

#tuple ... data container ... read only
aa = (1,2,3)
print('aa = ', aa, '   type = ', type(aa))
#aa[0] = aa[0]+1 # error

#dict ... dictionary ... data container ... read/write/searching
#aa = {'key':'value'}
aa = {'ㄱ':'가족', 'ㅎ':'홍길동'}
print('aa = ', aa, '   type = ', type(aa))
aa = {'a':'apple', 'g':'google'}
print('aa = ', aa, '   type = ', type(aa))
aa['a'] = 'amazon'
print('aa = ', aa, '   type = ', type(aa))
aa = {0:'0000', 1:'0001', 2:'0010'}
print('aa = ', aa, '   type = ', type(aa))
aa[0] = '0x00'
print('aa = ', aa, '   type = ', type(aa))


# %%
aa = True
aa = False


#len()
#type()
#print()

#c++
#int* pArr = new int[10]
#   array_size = sizeof(pArr)/sizeof(pArr[0])
#vector<int> vArr;
#vArr.push_back(10);
#vArr.push_back(20);
#vArr.push_back(30);
#   vArr_size = vArr.size()

aa = [1,2,3,4,5]
print('aa size = ', len(aa))
aa = [1,2,3]
print('aa size = ', len(aa))
aa = [1,2,3,2,2,3,3,2,2,3,2]
print('aa size = ', len(aa))

# %%
x=3
y = x*2
print('y = ', y)
y = x**3
print('y = ', y)

x = 9
y = x/2
print('y = ', y)
y = x//2
print('y = ', y)



# %%
hello = 'hello'
world = "world"
print(hello)
print(len(hello))
print(world)
print(len(world))
hw = hello + ' ' + world
print(hw)
print(len(hw), '   type = ', type(hw))
fmt = '%s %s %d' % (hello, world, 777)
print(fmt, '   type = ', type(fmt))
fmt = f'{hello:10s} {world:10s} {7777:10d}'
print(fmt, '   type = ', type(fmt))
fmt = f'{hello:10s} {world:10s} {7777:010d}'
print(fmt, '   type = ', type(fmt))

import numpy as np
print(np.pi)
fmt = f'{hello:10s} {world:10s} {123.123456:0.6f}'
print(fmt, '   type = ', type(fmt))



# %%
s = "hello"
print(s.capitalize())  # Capitalize a string; prints "Hello"
print(s.upper())       # Convert a string to uppercase; prints "HELLO"
print(s.rjust(7))      # Right-justify a string, padding with spaces; prints "  hello"
print(s.center(7))     # Center a string, padding with spaces; prints " hello "
print(s.replace('l', '(ell)'))  # Replace all instances of one substring with another;
                                # prints "he(ell)(ell)o"
print('  world '.strip()) 
#['h', 'e', 'l', 'l', 'o']
print(s[0:1+1])#h
print(s[1:2+1])#e
print(s[2:3+1])#l

for i in range(0,9+1,1):
    print('i=', i)
# %%
nums = list(range(5))     # range is a built-in function that creates a list of integers
print(nums)               # Prints "[0, 1, 2, 3, 4]"
print(nums[2:3+1])          # Get a slice from index 2 to 4 (exclusive); prints "[2, 3]"
print(nums[2:])           # Get a slice from index 2 to the end; prints "[2, 3, 4]"
print(nums[:1+1])           # Get a slice from the start to index 2 (exclusive); prints "[0, 1]"
print(nums[:])            # Get a slice of the whole list; prints "[0, 1, 2, 3, 4]"
print(nums[:-1])          # Slice indices can be negative; prints "[0, 1, 2, 3]"
nums[2:4] = [8, 9]        # Assign a new sublist to a slice
print(nums)               # Prints "[0, 1, 8, 9, 4]"



# %%
'''
True and True -> True      1 and  1   1
True and False -> False    1 and  0   0
False and True -> False    0 and  1   0
False and False -> False   0 and  0   0

True or True -> True      1 or  1   1
True or False -> True    1 or  0   1
False or True -> True    0 or  1   1
False or False -> False   0 or  0   0
'''
#comments
cond = True
if (cond) and (True):
    if cond or False:
        if cond :
            print('True')
        else:
            print('False')
    else:
        print('False')

# %%

for i in range(0,10,1):#for(int i=0; i<10; i++)
    print('i = ', i)

datas = [1,2,3,4,5,6,7,8,9,10]
for i in range(0,len(datas),1):
    print(f'datas[{i}] = {datas[i]}')

#for(int i=0; i<10; i++)
#for(const auto& data : datas)
for data in datas:
    print(data)
    #print(f'datas[{i}] = {datas[i]}')
for i, data in enumerate(datas):
    #print(data)
    if i%2 != 0:
        print(f'datas[{i}] = {data}')

for i in range(1,len(datas),2):
    print(f'datas[{i}] = {datas[i]}')



# %%
# for + if -> gugudan 
# reference 01.basic_JeongHo.py


# %%
xs = [3, 1, 2]    # Create a list
print(xs, xs[2])  # Prints "[3, 1, 2] 2"
print(xs[-1])     # Negative indices count from the end of the list; prints "2"
xs[2] = 'foo'     # Lists can contain elements of different types
print(xs)         # Prints "[3, 1, 'foo']"
xs.append('bar')  # Add a new element to the end of the list
print(xs)         # Prints "[3, 1, 'foo', 'bar']"
x = xs.pop()      # Remove and return the last element of the list
print(x, xs)      # Prints "bar [3, 1, 'foo']"



# %%
nums = [0, 1, 2, 3, 4]
print('nums = ', nums, '   type = ', type(nums))
nums = list(range(5)) 
print('nums = ', nums, '   type = ', type(nums))
squares = [x**2 for x in nums]
print('squares = ', squares, '   type = ', type(squares))
'''
int* pSquare = new int[n];
std::vector<int> vSequares;
for(int i=0; i<5; i++)
{
    int tmp = nums[i]*nums[i]
    int tmmp = std::pow(nums[i],2.0)
    vSequares.push_back(tmp);
    pSquare[i] = tmp;
}
'''
#%%
animals = ['cat', 'dog', 'monkey', 1,2,3, 1.123,2.123,3.123, ['cat', 'dog', 'monkey', 1,2,3, 1.123,2.123,3.123]]
for animal in animals:
    print(animal)
for idx, animal in enumerate(animals):
    print('#%d: %s' % (idx + 1, animal))



# %%
nums = list(range(1,10)) 
dans = list(range(2,10)) 

dan_start = 3
dan_finish = 7
step_start = 1
step_finish = 5
ggd = [
    f'{dan}x{step} = {dan*step}' 
    for dan in range(dan_start, dan_finish + 1)
    for step in range(step_start, step_finish + 1)
]
print(ggd)
print('=========='*5)
print (ggd[:9])
print (ggd[9:18])
print (ggd[18:27])
print('─────'*10)

for i in range(0,dan_finish-dan_start+1):
    print (ggd[(i)*step_finish:(i+1)*step_finish])


# %%
def sum(a,b):
    return a+b
def sum_div(a,b):
    return (a+b,a/b)
def calc(a,b):
    return (a+b, a-b, a*b, a/b)

a = 10
b = 20
c = sum(a,b)
c,d = sum_div(a,b)

print(f'{c} = {a}+{b}')
print(f'{d} = {a}/{b}')

c,d,e,f = calc(a,b)
print(f'{c} = {a}+{b}')
print(f'{d} = {a}-{b}')
print(f'{e} = {a}*{b}')
print(f'{f} = {a}/{b}')


def calc_list(a,b):
    return [a+b, a-b, a*b, a/b]

cc = calc_list(a,b)
print(f'{cc[0]} = {a}+{b}')
print(f'{cc[1]} = {a}-{b}')
print(f'{cc[2]} = {a}*{b}')
print(f'{cc[3]} = {a}/{b}')


# %%
def gugudan(dan_start,dan_finish,step_start,step_finish):
    ggd = [
        f'{dan}x{step} = {dan*step}' 
        for dan in range(dan_start, dan_finish + 1)
        for step in range(step_start, step_finish + 1)
        ]
    return ggd

dan_start = 3
dan_finish = 7
step_start = 1
step_finish = 5
ggd = gugudan(dan_start,dan_finish,step_start,step_finish)
for i in range(0,dan_finish-dan_start+1):
    print (ggd[(i)*step_finish:(i+1)*step_finish])
# %%
