import matplotlib.pyplot as plt
import numpy as np
import csv
import pandas as pd

def packetsReceived(): 
  x = []
  y = []

  with open('packets-received.csv') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')

    # skips headers
    next(plots)

    for row in plots:
      x.append(row[0])
      y.append(int(row[1]))
          
  plt.bar(x,y, label='Packets Received from each client')
  plt.xlabel('Client ID')
  plt.ylabel('Packets Received')
  plt.title('Packets Received from each client')
  plt.legend()
  plt.show()

def generalReport():
  with open('general-report.csv') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')

    # skips headers
    next(plots)
    
    data = {}
    data2 = []
    
    for row in plots:
      totalClients = row[0]
      totalMessages = row[1]
      totalMessagesLost = row[2]
      
      if totalClients not in data:
        data[totalClients] = [(int(totalMessages), int(totalMessagesLost))]
      else:
        data[totalClients] += [(int(totalMessages), int(totalMessagesLost))]    

      data2.append((int(totalMessages), int(totalMessagesLost)))
      
    # for key in data:
    #   x = []
    #   y = []
    #   for totalMessages, totalLost in data[key]:
    #     x.append(str(totalMessages))
    #     y.append(totalLost)
    #   print(x, y)
    #   plt.bar(x, y)
    #   plt.show()
    
    data2.sort()
    plt.plot([x for x, y in data2], [y for x, y in data2])
    plt.show()
          
def main():
  generalReport()
if __name__ == '__main__':
  main()