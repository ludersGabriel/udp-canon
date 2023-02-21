totalClients=(10 100 500 1000 2500 5000 7500 10000)
totalMessages=(100)

num=1

echo "totalClients, totalMessages, totalMessagesLost, lossRate" > general-report.txt

for i in "${totalClients[@]}"
do
  for j in "${totalMessages[@]}"
  do
    echo "Running test with $i clients and $j messages"
    ./server 8080 ./docs/logs/server/teste2/server-$i-$j-$num.txt
  done
done

cp ./general-report.txt ./docs/reports/teste2/general-report-$num.txt
rm general-report.txt
