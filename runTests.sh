totalClients=(10 100 500 1000 2500 5000 7500 10000)
totalMessages=(100)

num=4

echo "totalClients, totalMessages, totalMessagesLost, lossRate" > general-report.txt

for i in "${totalClients[@]}"
do
  for j in "${totalMessages[@]}"
  do
    echo "Running test with $i clients and $j messages"
    gnome-terminal -- ./server 8080 ./docs/logs/server/teste2/server-$i-$j-$num.txt
    sleep 2
    ./client glastheim 8080 $i $j ./docs/logs/client/teste2/client-$i-$j-$num.txt
    sleep 9
  done
done

cp ./general-report.txt ./docs/reports/teste2/general-report-$num.txt
rm general-report.txt
