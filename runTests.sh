totalClients=(1)
totalMessages=(1000 10000 50000 100000 250000 500000 750000 1000000 2000000 4000000)

echo "totalClients, totalMessages, totalMessagesLost, lossRate" > general-report.csv

for i in "${totalClients[@]}"
do
  for j in "${totalMessages[@]}"
  do
    echo "Running test with $i clients and $j messages"
    gnome-terminal -- ./server 8080 silent
    sleep 2
    ./client glastheim 8080 $i $j silent
    sleep 9
  done
done