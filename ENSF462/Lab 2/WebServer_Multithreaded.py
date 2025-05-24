from socket import *
import threading

def handle_client(connectionSocket, addr):
    try:
        message = connectionSocket.recv(1024).decode()
        filename = message.split()[1]
        f = open(filename[1:])
        outputdata = f.read()

        # Send one HTTP header line into socket
        connectionSocket.send('HTTP/1.1 200 OK\r\n\r\n'.encode())

        # Send the content of the requested file to the client
        connectionSocket.send(outputdata.encode())

    except IOError:
        #Send response message for file not found
        connectionSocket.send("HTTP/1.1 404 Not Found\r\n\r\n".encode())
    
    finally:
        # Close the client connection
        connectionSocket.close()

serverPort = 16000
serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind(('',serverPort))
serverSocket.listen(1)
print('The server is ready to receive')
while True:
    connectionSocket, addr = serverSocket.accept()
    print(f"Accepted connection from {addr[0]}:{addr[1]}")
    # start a new thread to handle the client
    thread = threading.Thread(target=handle_client, args=( connectionSocket, addr,))
    thread.start()