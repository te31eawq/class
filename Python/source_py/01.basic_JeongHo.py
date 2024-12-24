class AA:
    def __int__(this):
        this.name = 'hong gil dong'
        this.age = 99999
    def show(this):
        print(this.name)
        print(this.age)

    def set_name(this,name):
        this.name = name


#%%
#C/C++
# int / short / double / ...
# char / string
# 연속메모리 : array
# 집합 : struct
# 기능 : function
# 모듈 : class

#python
# int 정수,  float(더블을 포함한다) 실수 ,str : 문자열
# 연속메모리 : list ... container 
#       C/C++ 보다의 장점 : 모든 것을 담을 수 있다. "리스트"라는게 [everything, ..]
# 집합 : list
# 기능 : function
# 모듈 : class
#%%

aa = 123
print('aa = ', aa, '     type = ', type(aa))
aa = 123.000
print('aa = ', aa, '     type = ', type(aa))
aa = '123.000'
print('aa = ', aa, '     type = ', type(aa))
#%%

#array
#list ... data container
#dic ... read/write/searching<- 이거까지 있다.
aa = [1,2,3]
aa[0] = aa[0]+1     #data modified read/write
aa[1] = aa[1]+1
aa[2] = aa[2]+1

#tubple ... data container ... read only
aa = (1,2,3)
#aa[0] = aa[0]+1 # error

#dic ... dictionary ... data container ...
#aa = {'key': 'value'}
aa = {'ㄱ':'가족',   'ㅎ':'홍길동'}
aa = {'ㄱ':'가족',   'ㅎ':'홍길동'}
aa['a'] = 'amazon'
aa = {'ㄱ':'가족',   'ㅎ':'홍길동'}
aa[0] = '0x00'

#언팩 에러 // 왼쪽은 (2개만 받음) = (3개 줄 예정) ex.채널 = image.shape하게되면 mat클래스 속성 중에 width, height, channel
      
# %%
aa = True
aa = False

#내장 함수 예시
#len()
#type()
#print()

#C++
#int* pArr = new int[10]
#      array_size = sizeof(pArr)/sizeof(pArr[0])
#
#
#
#
#   vArr_size = vArr.size()

aa = [1,2,3,4,5]
print('aa size = ', len(aa))
aa = [1,2,3]
print('aa size = ', len(aa))
aa = [1,2,3,2,2,3,3,2,2,3,2]
print('aa size = ', len(aa))
# %%

#for + if -> gugudan

#GuGuDan Vertically Display
dan_start = 2
dan_finish = 9
step_start = 1
step_finish = 9


lines = ''
for Dan in range(dan_start,dan_finish+1):
    for Step in range(step_start, step_finish+1):
        lines += f'{Dan}x{Step} = {Dan*Step}\n'
    lines += '\n'



print(lines)

#%%
#GuGuDan Horizon Display
dan_start = 2
dan_finish = 9
step_start = 1
step_finish = 9

lines=''
for Step in range(step_start, step_finish+1):
    for Dan in range(dan_start,dan_finish+1):
        lines += f'{Dan}x{Step} = {Dan*Step}  \t'
    lines +="\n"


print(lines)
# %%
