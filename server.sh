i=$1 
j=$2 
num=$3

serverCommand="./server 8080 ./docs/logs/server/teste1/server-$i-$j-$num.txt"

ssh -tt gl19@h30 -J gl19@ssh.c3sl.ufpr.br -C "cd ./udp-canon; $serverCommand"