totalClients=(1 2 4 8 16 32 64 128 256)
totalMessages=(100 200 400 800 1600 3200 6400)

echo "totalClients, totalMessages, totalMessagesLost" > general-report.csv

for i in "${totalClients[@]}"
do
  for j in "${totalMessages[@]}"
  do
    echo "Running test with $i clients and $j messages"
    gnome-terminal -- ./server 8080 silent
    sleep 1
    ./client glastheim 8080 $i $j silent
    sleep 7
  done
done