#import socket module
from socket import *

serverSocket = socket(AF_INET, SOCK_STREAM)
#Prepare a server socket
#Fill in start
serverPort = 15000
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print("The server is ready to receive")
#Fill in end
while True:
    #Establish the connection
    print('Ready to serve...')
    connectionSocket, addr =  serverSocket.accept()
    try:
        message =  connectionSocket.recv(1024).decode()
        filename = message.split()[1]
        f = open(filename[1:])

        outputdata = f.read()

        #Send one HTTP header line into socket
        #Fill in start
        connectionSocket.send('HTTP/1.1 200 OK\r\n\r\n'.encode()) #The notes say this appears in the first line of server-to-client response message so I assume this is okay
        #Fill in end
        #Send the content of the requested file to the client
        for i in range(0, len(outputdata)):
            connectionSocket.send(outputdata[i].encode())
        connectionSocket.send("\r\n".encode())
        connectionSocket.close()
    except IOError:
        #Send response message for file not found
        # Fill in start
        connectionSocket.send("HTTP/1.1 404 Not Found\r\n\r\n".encode())
        # Fill in end

        #Close client socket
        # Fill in start
        connectionSocket.close()
        # Fill in end

serverSocket.close()

