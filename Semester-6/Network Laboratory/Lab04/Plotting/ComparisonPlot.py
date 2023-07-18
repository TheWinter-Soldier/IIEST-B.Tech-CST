import statistics as S
import matplotlib.pyplot as P
import numpy as N
from sklearn.linear_model import LinearRegression

#Function to enforce stochastic analysis
def stochasticEnforce(arr):
    mu = S.mean(arr)
    sigma = S.stdev(arr)
    
    new = []
    for i in range(0,50):
        if arr[i] <= (mu + sigma):     #Only letting values which are below (mu + sigma)
            new.append(arr[i])
        else:
            continue

    return new

F, figures = P.subplots(3, sharex = True, sharey = False)
F.suptitle("Analysis of Cumulative round-trip delays for various TTL values")
F.supxlabel("Payload size (Bytes)")
F.supylabel("Cumulative round-trip delay (Micro-seconds)")

P.xticks([0,100,200,300,400,500,600,700,800,900,1000])
P.subplots_adjust(hspace = 0.30)

#Sub-plot for TTL=2
x = []
y = []
Xmedians = []
Ymedians = []
for i in range(1,11):
    with open('TTL-2_' + str(i) + '00.txt') as file:
        Xmedians.append(100*i)

        temp = []
        focused = []
        while(True):
            line = file.readline()
            
            if len(line) < 1:
                break
            else:
                tokens = line.split()
                
                x.append(int(tokens[0]))
                y.append(int(tokens[1]))

                temp.append(int(tokens[1]))
        
        focused = stochasticEnforce(temp)
        Ymedians.append(S.median(focused))

    file.close()

xPoints = N.array(x)
yPoints = N.array(y)

XmedianPoints = N.array(Xmedians).reshape(-1,1)
YmedianPoints = N.array(Ymedians)

model = LinearRegression()
model.fit(XmedianPoints,YmedianPoints)

YmedianPredicted = model.predict(XmedianPoints)

figures[0].set_title("TTL=2",loc = 'right')

figures[0].scatter(xPoints,yPoints,15,color = 'red')
figures[0].plot(XmedianPoints,YmedianPredicted,color = 'red')

#Sub-plot for TTL=8
x = []
y = []
Xmedians = []
Ymedians = []
for i in range(1,11):
    with open('TTL-8_' + str(i) + '00.txt') as file:
        Xmedians.append(100*i)

        temp = []
        focused = []
        while(True):
            line = file.readline()
            
            if len(line) < 1:
                break
            else:
                tokens = line.split()
                
                x.append(int(tokens[0]))
                y.append(int(tokens[1]))

                temp.append(int(tokens[1]))
        
        focused = stochasticEnforce(temp)
        Ymedians.append(S.median(focused))

    file.close()

xPoints = N.array(x)
yPoints = N.array(y)

XmedianPoints = N.array(Xmedians).reshape(-1,1)
YmedianPoints = N.array(Ymedians)

model = LinearRegression()
model.fit(XmedianPoints,YmedianPoints)

YmedianPredicted = model.predict(XmedianPoints)

figures[1].set_title("TTL=8",loc = 'right')

figures[1].scatter(xPoints,yPoints,15,color = 'green')
figures[1].plot(XmedianPoints,YmedianPredicted,color = 'green')

#Sub-plot for TTL=16
x = []
y = []
Xmedians = []
Ymedians = []
for i in range(1,11):
    with open('TTL-16_' + str(i) + '00.txt') as file:
        Xmedians.append(100*i)

        temp = []
        focused = []
        while(True):
            line = file.readline()
            
            if len(line) < 1:
                break
            else:
                tokens = line.split()
                
                x.append(int(tokens[0]))
                y.append(int(tokens[1]))

                temp.append(int(tokens[1]))
        
        focused = stochasticEnforce(temp)
        Ymedians.append(S.median(focused))

    file.close()

xPoints = N.array(x)
yPoints = N.array(y)

XmedianPoints = N.array(Xmedians).reshape(-1,1)
YmedianPoints = N.array(Ymedians)

model = LinearRegression()
model.fit(XmedianPoints,YmedianPoints)

YmedianPredicted = model.predict(XmedianPoints)

figures[2].set_title("TTL=16",loc = 'right')

figures[2].scatter(xPoints,yPoints,20)
figures[2].plot(XmedianPoints,YmedianPredicted)

P.show()