import time
import socket

# The manual say this can be used as local host
serverName = '127.0.0.1'
serverPort = 12000

# Number of pings to send
num_pings = 10

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# This is the line which sets the timeout on the datagram socket
clientSocket.settimeout(1)

rtts = []
# We track successful/lost pings so we can calcualte the percent at the end
successful_pings = 0
lost_pings = 0

for ping_number in range(1, num_pings + 1):
    start_time = time.time()
    
    message = f"Ping {ping_number} {start_time}"
    
    try:

        clientSocket.sendto(message.encode(), (serverName, serverPort))
        
        # Wait for the response for one second, otherwise timeout
        response, serverAddress = clientSocket.recvfrom(1024)
        
        end_time = time.time()
        rtt = end_time - start_time
        
        print(f"Received from server: {response.decode()} in {rtt:.6f} seconds")
        rtts.append(rtt)
        successful_pings += 1
    
    except socket.timeout:
        print(f"Request timed out")
        lost_pings += 1
    
    # We do two seconds in between pings to allow for a second to pass and verify the packet is "lost" before sending another
    time.sleep(2)


min_rtt = min(rtts)
max_rtt = max(rtts)
avg_rtt = sum(rtts) / len(rtts)

packet_loss_percent = (lost_pings / num_pings) * 100

print("\nPings")
print(f"Packets: Sent 10 pings, Received = {successful_pings}, Lost = {lost_pings} ({packet_loss_percent:.1f}% loss)")
print(f"RTTs: Min = {min_rtt:.6f}s, Max = {max_rtt:.6f}s, Avg = {avg_rtt:.6f}s")

# Close the socket
clientSocket.close()
