
import socket
import websocket
import _thread
import time
from threading import Thread, Lock
lock = Lock()
ws=0
keyint = 0
key=bytes(32)
start=0
id=0
def load_new():
    global ws,key,start,id,keyint
    #ws = websocket.WebSocket()
    #ws.connect('wss://shake-challenge.konge.pw:1443/ws')
    if(True):
        keyint += 1
        key = bytearray(32)
        key[1:32] = keyint.to_bytes(31, 'big')
        key[0:1]=(1).to_bytes(1,'big')
        id = id + 1
        start = 0


def main_logic():
    global ws,key,start,id,keyint
    ws = websocket.WebSocket()
    ws.connect('wss://shake-challenge-internal.konge.pw/ws')
    while True:
        key = ws.recv()
        id = id + 1
        start = 0
        if(id>24900):
            print(id,key)
        #c.send(key)

step = 500000

def main_server(c):
    global dic,id,start,time_start,ws,step
    while (True):
        res = c.recv(1024)
        tid = int.from_bytes(res[0:8], byteorder='little')
        with lock:
            if ((not tid in dic) and tid == id):
                tans = res[8:16]
                #print(int.from_bytes(tans[3:4], byteorder='big'))
                if(int.from_bytes(tans[3:4], byteorder='big') == 255):
                    start = start + step
                else:
                    #print("found {}".format(tid))
                    #print(tans)
                    if(tid%1000==0):
                        time_end = time.time()
                        print("{} time:{}".format(tid,time_end-time_start))
                    dic[tid]=True
                    #load_new()
                    ws.send(tans,0x2)
                    start = start + step

        tres = bytearray(48)
        tres[0:8] = id.to_bytes(8, byteorder='little')
        tres[8:16] = start.to_bytes(8, byteorder='little')                                                                                                                                               
        tres[16:48] = key                                                                                                                                                                                
        #print("job {} {}".format(id,start))                                                                                                                                                             
        #print(tres)                                                                                                                                                                                     
        c.send(tres)     

#websocket.enableTrace(True)
s = socket.socket()
host = '0.0.0.0'
port = 12345
s.bind((host, port))

s.listen(5)

_thread.start_new_thread(main_logic,())

#load_new()
dic={0:True}
time_start=time.time()

while True:
    c,addr = s.accept()
    _thread.start_new_thread(main_server,(c,))
    #time.sleep(1)