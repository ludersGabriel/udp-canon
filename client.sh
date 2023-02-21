totalClients=(10 100 500 1000 2500 5000 7500 10000)
totalMessages=(100)

num=1

for i in "${totalClients[@]}"
do
  for j in "${totalMessages[@]}"
  do
    echo "Running test with $i clients and $j messages"
    ./client h30 8080 $i $j ./docs/logs/client/teste2/client-$i-$j-$num.txt
    sleep 7
  done
done
