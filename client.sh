totalClients=(1)
totalMessages=(1000 10000 50000 100000 250000 500000 750000 1000000 2000000 4000000)

num=1

for i in "${totalClients[@]}"
do
  for j in "${totalMessages[@]}"
  do
    echo "Running test with $i clients and $j messages"
    ./client h30 8080 $i $j ./docs/logs/client/teste1/client-$i-$j-$num.txt
    sleep 7
  done
done
