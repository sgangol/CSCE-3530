#     CSCE 3530:    Computer Networks
#     CSCE 3530:    Computer Networks
#     ASSIGNMENT:   Program Assignment 2
#     AUTHOR:       Srizan Gangol
#     DATE:         10/21/2017
#     DESCRIPTION:  Compiles all programs and Runs Server by default

mkdir cache
mkdir bin

echo -e "\n[Starting Compilation]"
echo -e   "----------------------"
echo -n "Fetch [.."
javac -d ./bin -cp bin src/fetch/*.java
echo -e "OK]"

echo -n "Server [.."
javac -d ./bin -cp bin src/Server.java
echo -e "OK]"

echo -n "Client [.."
javac -d ./bin -cp bin src/Client.java
echo -e "OK]\n"

echo -e "> COMPILATION COMPLETED!!"
echo -e "-----------------------\n"

java -cp bin Server $1
