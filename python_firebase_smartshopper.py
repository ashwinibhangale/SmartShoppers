from firebase import firebase
import serial
import threading
import json
import time
connected=False
ser=serial.Serial('COM10')

d=0
d1=0
d2=0
firebase1=firebase.FirebaseApplication('https://smartshopping-c4692.firebaseio.com/')
#firebase1=firebase.FirebaseApplication('https://makeuoft-9c9dc.firebaseio.com/makeuoft-9c9dc')
#result=firebase1.get('/makeuoft-9c9dc',None)
result=firebase1.get('/tobuy',None)
print(result)
#{'anto':'1'})
#a=json.dumps(result)
#a=result['itemlist']
#print(a)
#a=json.dumps(a)
#parsed_json=json.loads(result)

counter=[0]*6


count=0
key1=[0]*5
tot=""
tot1=""
tot2=""
for key,value in result.iteritems():
    temp=[key,value]
    
    key1[count]=key
    #print(key1[count])
    tot+=key
    tot+=','
    
    tot1+=str(value)
    tot1+=','
    counter[count]=int(value)
    #tot+=key1[count].encode('utf-8')
    count+=1
    
tot2='>'+tot+tot1+'<'
#tot='6rice,top,cot,20,30,50,7'
print(counter)
print(tot2.encode('utf-8'))
i=0
#total=key1[count].encode('utf-8')
while i<5:
    ser.write(tot2.encode('utf-8'))
    i+=1
    time.sleep(0.5)
#ser.write(','.encode('utf-8'))
time.sleep(2)
print("part 1 done")

while True:
    try:
        #x=ser.read()
        s=ser.readline()
        #print(s)
        if(s=="80\r\n"):
            print("1")
            if(counter[0]>0):
                d+=1  
                counter[0]-=1
                result=firebase1.put('tobuy',str(key1[0]),str(counter[0]))
                firebase1.put('bought',str(key1[0]),str(d))

                tot2='>'+tot+str(counter[0])+','+str(counter[1])+','+str(counter[2])+','+'<'
                for k in range(0,3):
                    print(tot2)
                    ser.write(tot2.encode('utf-8'))
                    time.sleep(0.1)

                
        if(s=="30\r\n"):
            print("2")
            if(counter[1]>0):
                d1+=1
                counter[1]-=1
                result=firebase1.put('tobuy',str(key1[1]),str(counter[1]))
                firebase1.put('bought',str(key1[1]),str(d1))

                tot2='>'+tot+str(counter[0])+','+str(counter[1])+','+str(counter[2])+','+'<'
                for k in range(0,2):
                    ser.write(tot2.encode('utf-8'))
                    print(tot2)
                    time.sleep(0.1)
                #time.sleep(0.5)

                
        if(s=="10\r\n"):
            print("2")
            if(counter[2]>0):
                d2+=1
                counter[2]-=1
                firebase1.put('tobuy',str(key1[2]),str(counter[2]))
                firebase1.put('bought',str(key1[2]),str(d2))
                
                tot2='>'+tot+str(counter[0])+','+str(counter[1])+','+str(counter[2])+','+'<'
                print(tot2)
                ser.write(tot2.encode('utf-8'))
        print(counter)
    except KeyboardInterrupt:
        print('done')
        ser.close()

    
ser.close()
#https://makeuoft-9c9dc.firebaseio.com


        


        
        
