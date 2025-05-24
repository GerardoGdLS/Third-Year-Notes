#ENSF462 Lab 1 Part 2 Socket Programming

from socket import *
serverName = 'localhost'
serverPort = 5678
user1 = input("Enter user 1's name: ") #Enter user 1 name

print("Creating socket")
clientSocket = socket(AF_INET, SOCK_STREAM) #Create socket
print("Connecting to server")
clientSocket.connect((serverName,serverPort))
print("Sending user1 name")
clientSocket.send(user1.encode()) #Send user 1 name

print("Receiving user2 name")
user2 = clientSocket.recv(1024).decode() #Receive user 2 name
print(f"Connected to {user2}")

while True:
    
    message = input(f"{user1}: ")
    clientSocket.send(message.encode())
    
    if message.lower() == "bye":
        print("User entered bye.")
        break

    print("Waiting for a response")
    serverMessage = clientSocket.recv(1024).decode()
    print(f"{user2}: {serverMessage}")
    
    if serverMessage.lower() == "bye":
        print("Server entered bye.")
        break

print("Closing socket")
clientSocket.close()