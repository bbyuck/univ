#과제 2

import urllib.request as req
import urllib.parse as parse
import re
import sys
orig_stdout = sys.stdout

f = open('result.csv', 'w', encoding = "utf_8")
sys.stdout = f

url = 'https://finance.naver.com/sise/'


data = req.urlopen(url).read()
html = data.decode("EUC_KR")

# print(data)
# print(html)

top = re.findall(r'<!-- Top 종목 -->.+?<!-- //Top 종목 -->', html, re.DOTALL) #Top 종목 끌어오기
# print(top)
# print(len(top))

tabName = re.findall(r'<em>(.+)</em>', top[0]) + re.findall(r'</em>(.+)</h3>', top[0])

cname = []
tabBar = []
uratio = [] #전일비
num = [] #숫자형태
percent1 = [] #퍼센트형태
percent2 = []
zper = []
for item in top:
    key = re.findall(r'<tr>(.+?)</tr>', item, re.DOTALL) #
    # print(len(key)) # Top 종목의 class 소스
    # name = re.findall(r'(">.+?)</a>', item)
    # print(name)
    # cost = re.findall(r'<td class="number">(.+?)</td>', item) # 표에 표시된 숫자
    # print(cost)
    for  k in key:
        name = re.findall(r'">(.+?)</a>', k)
        for n in name:
            cname.append(n)
        ratio = re.findall(r'<th class="tr">(.+비)', k)  # 전일비
        for r in ratio:
            if ratio != []:
                uratio.append(r)
        tab = re.findall(r'<th>(.+?)</th>', k, re.DOTALL)
        for t in tab:
            if tab != []: #표의 메뉴
                tabBar.append(t)
        cost = re.findall(r'<td class="number">(.+?)</td>', k) # 표에 표시된 숫자
        for c in cost:
            if cost != []:
                num.append(c)

        per = re.findall(r'<span class="tah p11">(.+?)</span>', k) # 0%표현한 비율
        for p in per:
            zper.append(p)


        spanlow = re.findall(r'<span class="tah p11 nv01">(.+?)</span>', k, re.DOTALL) # [0] 전일비 [1] 등락률
        for sl in spanlow:
            percent1.append(sl)
        spanhigh = re.findall(r'<span class="tah p11 red01">(.+?)</span', k, re.DOTALL) # [0] 전일비 [1] 등락률
        for sh in spanhigh:
            percent1.append(sh)


mp = [] #[전일비, 등락률]

for p1 in percent1:
    per1 = re.findall(r'\S.+\S', p1)
    for pe1 in per1:
        mp.append(pe1)

# print(mp)

tabName = ['상한가', '하한가', '상승', '보합', '하락', '거래량상위', '고가대비급락', '시가총액상위'] #탭 인덱스마다의 탭이름

def printTab(tabIndex):
    print(tabName[tabIndex])
    fileRow = ''
    tabCode = 0 #탭마다 탭 메뉴 개수
    if tabIndex <= 1:
        tabCode = 10
    elif tabIndex <= 4:
        tabCode = 9
    else:
        tabCode = 8

    for j in range(0, tabCode - 1): #탭 메뉴
        if tabBar[0] == '현재가':
            fileRow += tabBar[0]
            fileRow += uratio[0]
            print(str(tabBar.pop(0)).ljust(15), end='\t')
            print(str(uratio[0]).ljust(5), end='\t')
            j += 1
        fileRow += tabBar[0]
        print(str(tabBar.pop(0)).ljust(15), end = '\t')

    print('\n')

    rankCode = 0 #탭마다 순위 개수
    if tabIndex <= 1:
        if tabIndex == 0:
            rankCode = 6
        elif tabIndex == 1:
            rankCode = 4;
        for i in range(0, rankCode): #표 내용부
            row = str(i+1).rjust(4) + str(num.pop(0)).rjust(19) + str(num.pop(0)).rjust(20) + str(cname.pop(0)).rjust(19) + str(num.pop(0)).rjust(20) + str(mp.pop(0)).rjust(17) + str(mp.pop(0)).rjust(12)
            row = row + str(num.pop(0)).rjust(20) + str(num.pop(0)).rjust(17) + str(num.pop(0)).rjust(18) + str(num.pop(0)).rjust(19)
            print(row)
            fileRow += row
    elif tabIndex == 2:
        for i in range(0, 10):
            row = str(i+1).rjust(4) + str(cname.pop(0)).rjust(19) + str(num.pop(0)).rjust(20) + str(mp.pop(0)).rjust(19) + str(mp.pop(0)).rjust(12) + str(num.pop(0)).rjust(17)
            row = row + str(num.pop(0)).rjust(20) + str(num.pop(0)).rjust(17) + str(num.pop(0)).rjust(18)+ str(num.pop(0)).rjust(19)
            print(row)

    elif tabIndex == 4:
        for i in range(0, 10):
            row = str(i + 1).rjust(4) + str(cname.pop(0)).rjust(19) + str(num.pop(0)).rjust(20) + str(mp.pop(0)).rjust(
                19) + str(mp.pop(0)).rjust(12) + str(num.pop(0)).rjust(17)
            row = row + str(num.pop(0)).rjust(20) + str(num.pop(0)).rjust(17) + str(num.pop(0)).rjust(18) + str(
                num.pop(0)).rjust(19)
            print(row)

    elif tabIndex == 3:
        for i in range(0, 10):
            row = str(i + 1).rjust(4) + str(cname.pop(0)).rjust(19) + str(num.pop(0)).rjust(20) + str(zper.pop(0)).rjust(
                19) + str(zper.pop(0)).rjust(12) + str(num.pop(0)).rjust(17)
            row = row + str(num.pop(0)).rjust(20) + str(num.pop(0)).rjust(17) + str(num.pop(0)).rjust(18) + str(
                num.pop(0)).rjust(19)
            print(row)
    else:
        for i in range(0, 10):
            row = str(i+1).rjust(4) + str(cname.pop(0)).rjust(19) + str(num.pop(0)).rjust(20) + str(mp.pop(0)).rjust(19) + str(mp.pop(0)).rjust(12) + str(num.pop(0)).rjust(17)
            row = row + str(num.pop(0)).rjust(20) + str(num.pop(0)).rjust(17) + str(num.pop(0)).rjust(18)
            print(row)
for i in range(0, 7): # 탭의 갯수만큼 for문
    printTab(i)
    print('\n')

sys.stdout = orig_stdout
f.close()

