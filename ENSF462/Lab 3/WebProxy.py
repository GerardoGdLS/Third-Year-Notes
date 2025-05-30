from socket import *
import os

# Create a server socket, bind it to a port and start listening
proxySerSock = socket(AF_INET, SOCK_STREAM)
#fill in start.
serverPort = 12345
proxySerSock.bind(('', serverPort))
proxySerSock.listen(1)
#fill in end.

while 1:
    print('Ready to serve...')
    #accept connection from clients 
    proxyCliSock, addr = proxySerSock.accept()
    print('Received a connection from:', addr)

    # get the http request from client
    message = proxyCliSock.recv(1024).decode()
    print(message)

    # if message is not a GET request send a response 400 Bad request to the client
    #close the connection and go to the next iteration of while loop waiting for another request
    #from the same or a different client
    if not message.startswith("GET"):
        print("message is not a GET")
        # fill in start.
        proxyCliSock.send('HTTP/1.1 400 Bad Request\r\n\r\n'.encode())
        proxyCliSock.close()
        # fill in end.
        continue

    # Extract the pathname(including the filename) and hostname from the given message
    slashPlusUrl = message.split()[1]
    url = slashPlusUrl.partition("/")[2]
    # fill in start
    hostn = url.split('/')[0]
    pathname = url.split('/')[1:]
    # fill in end.
    pathname = "/" + "/".join(pathname)
    # remove "www." from the hostname if it starts with "www."
    if hostn.startswith("www."):
        hostn = hostn.replace("www.", "", 1)

    print("pathname: " , pathname)
    print("hostname: ", hostn)

    fileExist = "false"

    directory = "./cache/" + url.replace("/", "_")

    try:
        # Check whether the file exist in the cache using open() method
        # If file exists it opens file and reads otherwise it throws as exception
        f = open(directory, "rb")
        object = f.read()

        # Send http response header and object
        #fill in start
        proxyCliSock.send('HTTP/1.1 200 OK\r\nConnection: close\r\n\r\n'.encode())
        proxyCliSock.send(object)
        #fill in end

        fileExist = "true"
        print('Read from cache')
        #close socket and file
        #fill in start
        f.close()
        proxyCliSock.close()
        #fill in end

    except IOError: # Error handling for file not found in cache

        if fileExist == "false":
            # Create a socket on the proxyserver to connect to the original server on port 80
            proxyAsClientSocket = socket(AF_INET, SOCK_STREAM)
            # Connect to the original server on port 80
            proxyAsClientSocket.connect((hostn, 80))

            #create a get request message and send the message to the server using the socket just created in above lines
            # Hint : use pathname and hostn in the request message

            #fill in start
            new_message = f"GET {pathname} HTTP/1.1\r\nHost: {hostn}\r\nConnection: close\r\n\r\n"
            proxyAsClientSocket.send(new_message.encode())
            #fill in end

            # initialize response to empty in binary format - works for any type of document
            total_response = b''

            # receive data from web server
            #Hint: You can use a while loop and get response in chunks until it is finished.
            #Fill in start
            while(1):
                chunk = proxyAsClientSocket.recv(1024)
                if not chunk:
                    break
                
                total_response += chunk
            
            #Fill in end

            #Separate header and object
            #Hint use split function. Check the lecture notes to see what separates the response header and object
            split_response = total_response.split(b'\r\n\r\n', 1)
            response_header = split_response[0]
            response_object = split_response[1]


            if b'200 OK' in response_header:
                # if the response is a 200 OK response create the directory and file and write the object into the file
                # Then, send http response header and object to the client
                #Fill in start
                os.makedirs(os.path.dirname(directory), exist_ok=True)
                newFile = open(directory, "wb")
                newFile.write(response_object)
                proxyCliSock.send('HTTP/1.1 200 OK\r\nConnection: close\r\n\r\n'.encode())
                proxyCliSock.send(response_header + b'\r\n\r\n' + response_object)
                #Fill in end
            else:
                #Otherwise, i.e., if response is not a 200 OK message,send 400 bad response
                #Fill in start
                proxyCliSock.send('HTTP/1.1 400 Bad Response\r\n\r\n'.encode())
                #Fill in end

            # close socket between proxy and origin server
            proxyAsClientSocket.close()
        else:
            break
    except:
        print("An Exception Occurred")
    finally:
        # close socket between proxy and client
        proxyCliSock.close()
    break #to test file with multiple objects. If the tested URLs have only one object you can remove "break"


#close the main proxy listening socket
proxySerSock.close()
print("finish")
