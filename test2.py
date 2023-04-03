import os,time
import requests

from tkinter import messagebox
fir=['' for i in range(10)]
headers = {'Proxy-Connection': 'keep-alive',
'Pragma': 'no-cache',
'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/97.0.4692.71 Safari/537.36',
'Cookie':'zg_did=%7B%22did%22%3A%20%2217e2deb791fa00-059c89b0fd7694-4303066-384000-17e2deb7920a16%22%7D; zg_=%7B%22sid%22%3A%201641447913762%2C%22updated%22%3A%201641447913765%2C%22info%22%3A%201641447913764%2C%22superProperty%22%3A%20%22%7B%7D%22%2C%22platform%22%3A%20%22%7B%7D%22%2C%22utm%22%3A%20%22%7B%7D%22%2C%22referrerDomain%22%3A%20%22ehall.xidian.edu.cn%22%2C%22cuid%22%3A%20%2220049200261%22%7D; JSESSIONID=6B17EEBEE0EF7B00F1097AA2227F33B3',
'Content-Type': 'application/x-www-form-urlencoded',
}
payload = ['timeId=6&teachingId=43&parameter=&pageIndex=0&pageSize=20&sortField=&sortOrder=',
'timeId=6&teachingId=44&parameter=&pageIndex=0&pageSize=20&sortField=&sortOrder=',
'timeId=6&teachingId=46&parameter=&pageIndex=0&pageSize=20&sortField=&sortOrder=',
'timeId=6&teachingId=72&parameter=&pageIndex=0&pageSize=20&sortField=&sortOrder=',
'timeId=6&teachingId=75&parameter=&pageIndex=0&pageSize=20&sortField=&sortOrder=',
'timeId=6&teachingId=51&parameter=&pageIndex=0&pageSize=20&sortField=&sortOrder=',
'timeId=6&teachingId=60&parameter=&pageIndex=0&pageSize=20&sortField=&sortOrder=',
'timeId=6&teachingId=40&parameter=&pageIndex=0&pageSize=20&sortField=&sortOrder=',
]
s = requests.Session()
s.trust_env = False
ff=''
while True:
    for i in range(8):

        q=s.post('http://tybjxgl.xidian.edu.cn/admin/chooseCurriculum/showTeachingCurriculum',data=payload[i],headers=headers)
        if(q.status_code==200):
            str=q.text
            #print(str)
            if(len(fir[i])!=0 and str!=fir[i]):
                
                messagebox.showinfo("提示",str)
                time.sleep(100)
            fir[i] = str
    time.sleep(2)