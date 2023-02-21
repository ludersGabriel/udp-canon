totalClients=(1)
totalMessages=(1000 10000 50000 100000 250000 500000 750000 1000000 2000000 4000000)

num=1

echo "totalClients, totalMessages, totalMessagesLost, lossRate" > general-report.txt

for i in "${totalClients[@]}"
do
  for j in "${totalMessages[@]}"
  do
    echo "Running test with $i clients and $j messages"
    ./server 8080 ./docs/logs/server/teste1/server-$i-$j-$num.txt
  done
done

cp ./general-report.txt ./docs/reports/teste1/general-report-$num.txt
rm general-report.txt
