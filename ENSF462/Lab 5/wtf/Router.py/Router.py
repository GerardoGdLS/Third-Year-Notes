import socket
import threading
import time
import sys
import json
import heapq

INFINITY = 999

class Router:
    def __init__(self, router_id, router_port, config_file):
        self.router_id = int(router_id)
        self.router_port = int(router_port)
        self.config_file = config_file
        self.neighbors = {}
        self.network_topology = {}
        self.lock = threading.Lock()
        self.load_config()
        self.start_udp_socket()

    def load_config(self):
        with open(self.config_file, 'r') as file:
            lines = file.readlines()
            total_nodes = int(lines[0].strip())
            self.network_topology = {i: [INFINITY] * total_nodes for i in range(total_nodes)}
            for i in range(total_nodes):
                self.network_topology[i][i] = 0  # Link to self is 0
            for line in lines[1:]:
                parts = line.strip().split()
                if len(parts) != 4:  # Skip lines that don't have exactly 4 parts
                    continue
                neighbor_label, neighbor_id, link_cost, neighbor_port = parts
                neighbor_id = int(neighbor_id)
                link_cost = int(link_cost)
                neighbor_port = int(neighbor_port)
                self.neighbors[neighbor_id] = (link_cost, neighbor_port)
                self.network_topology[self.router_id][neighbor_id] = link_cost

    def start_udp_socket(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(('127.0.0.1', self.router_port))

    def send_link_state(self):
        while True:
            link_state_msg = json.dumps({
                'sender_id': self.router_id,
                'link_state': self.network_topology[self.router_id]
            })
            for neighbor_id, (_, neighbor_port) in self.neighbors.items():
                self.sock.sendto(link_state_msg.encode(), ('127.0.0.1', neighbor_port))
            time.sleep(1)

    def receive_link_state(self):
        while True:
            data, _ = self.sock.recvfrom(1024)
            message = json.loads(data.decode())
            sender_id = message['sender_id']
            link_state = message['link_state']
            with self.lock:
                for i in range(len(link_state)):
                    self.network_topology[sender_id][i] = link_state[i]

    def dijkstra(self):
        while True:
            time.sleep(10)
            with self.lock:
                total_nodes = len(self.network_topology)
                distances = [INFINITY] * total_nodes
                previous_nodes = [1] * total_nodes
                distances[self.router_id] = 0
                min_heap = [(0, self.router_id)]
                while min_heap:
                    current_distance, current_node = heapq.heappop(min_heap)
                    if current_distance > distances[current_node]:
                        continue
                    for neighbor_id, cost in enumerate(self.network_topology[current_node]):
                        if cost < INFINITY:
                            new_distance = current_distance + cost
                            if new_distance < distances[neighbor_id]:
                                distances[neighbor_id] = new_distance
                                previous_nodes[neighbor_id] = current_node
                                heapq.heappush(min_heap, (new_distance, neighbor_id))
                self.print_results(distances, previous_nodes)

    def print_results(self, distances, previous_nodes):
        print(f"\nDijkstra Algorithm Results for Router {chr(self.router_id + 65)}")
        print("Destination_Routerid\tDistance\tPrevious_node_id")
        for node_id in range(len(distances)):
            print(f"{node_id}\t\t\t{distances[node_id]}\t\t{previous_nodes[node_id]}")

        print("\nForwarding Table:")
        print("Destination_Routerid\tNext_hop_routerlabel")
        for node_id in range(len(distances)):
            if node_id != self.router_id:
                next_hop = node_id
                # Trace back to find the first hop
                while previous_nodes[next_hop] != self.router_id and previous_nodes[next_hop] != -1:
                    next_hop = previous_nodes[next_hop]
                print(f"{node_id}\t\t\t{chr(next_hop + 65)}")

    def start(self):
        threads = [
            threading.Thread(target=self.send_link_state),
            threading.Thread(target=self.receive_link_state),
            threading.Thread(target=self.dijkstra)
        ]
        for thread in threads:
            thread.start()
        for thread in threads:
            thread.join()


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python Router.py <routerid> <routerport> <configfile>")
        sys.exit(1)

    router_id, router_port, config_file = sys.argv[1], sys.argv[2], sys.argv[3]
    router = Router(router_id, router_port, config_file)
    router.start()