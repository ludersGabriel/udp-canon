import matplotlib.pyplot as plt
import csv

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

def main():
  packetsReceived()

if __name__ == '__main__':
  main()