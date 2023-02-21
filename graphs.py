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
  num = '4'
  with open('./docs/reports/teste2/general-report-' + num + '.txt') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')

    # skips headers
    next(plots)
    
    data = {}
    data2 = []
    
    for row in plots:
      totalClients = row[0]
      totalMessages = row[1]
      totalMessagesLost = row[2]
      lossRate = row[3]

      data2.append((str(totalClients), float(lossRate)))
    
    average = sum([y for x, y in data2]) / len([y for x, y in data2])
    print(data2)
    plt.bar([x for x, y in data2], [y for x, y in data2])
    fig = plt.gcf()
    fig.set_size_inches(18, 9)
    plt.title('Loss Rate vs Total Clients (100 messages per client) ' + num)
    plt.axhline(average, color='r', linestyle='--', label='Average Loss Rate')
    plt.ylabel('Loss Rate (%)')
    plt.xlabel('Total Clients')
    plt.legend()
    plt.text(
      0, 
      average, 
      "{:.2f}".format(average) + '%', 
      color='black', 
      fontsize=14, 
      ha='right', 
      va='bottom'
    )
  
    plt.savefig('./docs/graphs/loss-rate-vs-total-clients-' + num + '.png')
    plt.show()
          
def main():
  generalReport()
if __name__ == '__main__':
  main()