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

P.title("Cumulative round-trip delays for different payload sizes with Time-to-live value of x")
P.xlabel("Payload size (Bytes)")
P.ylabel("Cumulative round-trip delay (Micro-seconds)")

P.xticks([0,100,200,300,400,500,600,700,800,900,1000])

#Sub-plot for TTL=x
x = []
y = []
Xmedians = []
Ymedians = []
for i in range(1,11):
    with open('TTL-x_' + str(i) + '00.txt') as file:
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

P.scatter(xPoints,yPoints,15|20,color = "*")
P.plot(XmedianPoints,YmedianPredicted,color = "*")

P.show()