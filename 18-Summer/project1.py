#float 형 2진수 만들기 함수

number = float(input('10진수 입력 : ')) #

def makeFloat(n): #float형 number를 입력받았을 때 소수점 이하 몇 자리까지인지 자리수 구하는 함수
    i = 1 # 소수점이하 자리수 변수

    intPart = int(n // 1)
    floatPart = n - intPart

    while int(number * 10**i) != intPart * 10**i + floatPart * 10**i:
        # print(int(number * 10**i))
        # print(intPart * 10**i + floatPart * 10**i) ## 자리수 구하는 과정이 잘 출력되는지 확인하는 부분
        i += 1
    return i #소수점이하 자리수 리턴

def floatToInt(floatPart, floatPoint): #소수부분을 정수로 리턴하는 함수
    return int(floatPart * 10**floatPoint)


def floatToBinary(fip, floatPoint): # float 부분의 수를 2진수로 바꾸고
    reg = [] #2진수로 변환된 수를 int type으로 받을 list
    regFlag = 0 #소수점이하 자릿수를 제어해줄 flag
    while fip != 0:
        if fip >= 10 ** floatPoint:
            fip -= 10 ** floatPoint
            reg.append(1)
            regFlag += 1
        else:
            reg.append(0)
            regFlag += 1
        fip *= 2

        if regFlag > 10: # 소수점 이하 10자리까지만 출력
            break
    return reg #리스트를 리턴


def binFloat(floatN): # 정의해둔 함수들을 호출해 float형 10진수 입력받아 str형 2진수를 반환하는 함수

    floatPoint = makeFloat(floatN)  # 입력받은 number의 소수자리수를 변수 floatPoint에 저장
    floatingPart = floatToInt(floatN - int(floatN // 1),floatPoint)
    segment = floatToBinary(floatingPart, floatPoint)
    binaryFloat = ''  # 2진수로 표현될 소수부분의 수 str형
    for i in range(1,len(segment)):  # binaryFloat 변수에 2진수를 차례대로 저장해줄 for문
        binaryFloat += str(segment[i])
    binaryFloat = bin(int(floatN // 1)) + '.' + binaryFloat

    return binaryFloat

print(binFloat(number))

print(type(binFloat(number))) # str타입으로 잘 변환되었는지 확인