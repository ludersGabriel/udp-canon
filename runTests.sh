totalClients=(1)
totalMessages=(1000 10000 50000 100000 250000 500000 750000 1000000 2000000 4000000)

num=4

echo "totalClients, totalMessages, totalMessagesLost, lossRate" > general-report.csv

for i in "${totalClients[@]}"
do
  for j in "${totalMessages[@]}"
  do
    echo "Running test with $i clients and $j messages"
    # instead of gonme-terminal, ssh h30 and run server
    gnome-terminal -- ./server 8080 ./docs/logs/server/teste1/server-$i-$j-$num.log
    sleep 2
    # ssh h29 and run client
    ./client glastheim 8080 $i $j ./docs/logs/client/teste1/client-$i-$j-$num.log
    sleep 9
  done
done

cp ./general-report.csv ./docs/reports/teste1/general-report-$num.csv
