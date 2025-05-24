#ENSF462 Lab 1 Part 2 Socket Programming

from socket import *
serverPort = 5678

user2 = input("Enter user 2's name: ") #Get name for user2

print("Setting up server to receive requests")
serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind(('',serverPort))
serverSocket.listen(1)
connectionSocket, addr = serverSocket.accept()
print('The server is ready to receive')

print("Receiving user1 name")
user1 = connectionSocket.recv(1024).decode() #Receive name for user1

print("Sending user2 name")
connectionSocket.send(user2.encode())

while True:
    print("Waiting for a response")
    sentence = connectionSocket.recv(1024).decode()
    print(f"{user1}: {sentence}")

    if (sentence.lower() == "bye"):
        print("Client entered bye")
        break
    
    message = input(f"{user2}: ")
    connectionSocket.send(message.encode())

    if (message.lower() == "bye"):
        print("Server entered bye")
        break

print("Closing socket")
connectionSocket.close()
    