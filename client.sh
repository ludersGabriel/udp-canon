i=$1 
j=$2 
num=$3

clientCommand="./client h30 8080 $i $j ./docs/logs/client/teste1/client-$i-$j-$num.txt"

ssh -tt gl19@h29 -J gl19@ssh.c3sl.ufpr.br -C "cd ./udp-canon; $clientCommand"