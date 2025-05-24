import threading
import socket
import sys
import time
import heapq

class Router:
    def __init__(self, router_id, port, config_file):
        self.router_id = router_id
        self.port = port
        self.config_file = config_file
        self.neighbors = {}
        self.link_state = {}
        self.all_link_states = {}
        self.forwarding_table = {}
        self.total_nodes = 0
        self.lock = threading.Lock()
        self._load_config()

    def _load_config(self):
        with open(self.config_file, 'r') as file:
            self.total_nodes = int(file.readline().strip())
            for line in file:
                label, node_id, cost, neighbor_port = line.split()
                node_id = int(node_id)
                self.neighbors[node_id] = {
                    'cost': int(cost),
                    'port': int(neighbor_port),
                    'label': label
                }
        self.link_state = {i: (0 if i == self.router_id else self.neighbors.get(i, {}).get('cost', float('inf')))
                           for i in range(self.total_nodes)}
        self.all_link_states[self.router_id] = self.link_state.copy()

    def _serialize_link_state(self):
        """Convert the link-state vector into a space-separated string."""
        serialized = f"{self.router_id} " + " ".join(str(self.link_state[i]) for i in range(self.total_nodes))
        return serialized

    def _deserialize_link_state(self, message):
        """Convert a received space-separated string back into a link-state vector."""
        parts = list(map(int, message.strip().split()))
        router_id = parts[0]
        link_state = {i: parts[i + 1] for i in range(self.total_nodes)}
        return router_id, link_state

    def _send_link_state(self):
        # Wait for all routers to initialize
        time.sleep(5)  # Adjust this delay as needed
        while True:
            message = self._serialize_link_state().encode()
            for neighbor in self.neighbors.values():
                with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
                    print(f"Router {self.router_id}: Sending link state to port {neighbor['port']} -> {message.decode()}")
                    sock.sendto(message, ('127.0.0.1', neighbor['port']))


    def _receive_link_state(self):
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
            sock.bind(('127.0.0.1', self.port))
            print(f"Router {self.router_id}: Listening on port {self.port}")
            while True:
                data, addr = sock.recvfrom(1024)
                message = data.decode()
                print(f"Router {self.router_id}: Received link state from {addr} -> {message}")
                router_id, link_state = self._deserialize_link_state(message)
                with self.lock:
                    self.all_link_states[router_id] = link_state


    def _compute_paths(self):
        while True:
            time.sleep(10)  # Adjust to allow enough time for link states to propagate
            with self.lock:
                # Check if we have received all link states
                if len(self.all_link_states) < self.total_nodes:
                    print(f"Router {self.router_id}: Waiting for all link states. Known: {len(self.all_link_states)}/{self.total_nodes}")
                    continue  # Wait until all link states are received

                print(f"Router {self.router_id}: All link states received. Computing paths...")
                
                # Initialize Dijkstra's algorithm
                distances = {i: float('inf') for i in range(self.total_nodes)}
                previous_nodes = {i: None for i in range(self.total_nodes)}
                distances[self.router_id] = 0

                visited = set()
                priority_queue = [(0, self.router_id)]  # (distance, node)

                while priority_queue:
                    current_distance, current_node = heapq.heappop(priority_queue)

                    if current_node in visited:
                        continue
                    visited.add(current_node)

                    for neighbor_id, cost in self.all_link_states[current_node].items():
                        if cost == float('inf'):  # Skip unreachable neighbors
                            continue
                        distance = current_distance + cost
                        if distance < distances[neighbor_id]:
                            distances[neighbor_id] = distance
                            previous_nodes[neighbor_id] = current_node
                            heapq.heappush(priority_queue, (distance, neighbor_id))

                # Build forwarding table
                self.forwarding_table = {}
                for dest in range(self.total_nodes):
                    if dest == self.router_id or distances[dest] == float('inf'):
                        continue
                    next_hop = dest
                    while previous_nodes[next_hop] != self.router_id:
                        next_hop = previous_nodes[next_hop]
                    self.forwarding_table[dest] = next_hop

                self._print_tables(distances, previous_nodes)


    def _print_tables(self, distances, previous_nodes):
        print("\nDestination_Routerid\tDistance\tPrevious_node_id")
        for node in range(self.total_nodes):
            print(f"{node}\t\t{distances[node]}\t\t{previous_nodes[node]}")

        print("\nForwarding Table:")
        print("Destination_Routerid\tNext_hop_routerlabel")
        for dest, next_hop in self.forwarding_table.items():
            print(f"{dest}\t\t{chr(65 + next_hop)}")  # Convert ID to router label


    def start(self):
        threads = [
            threading.Thread(target=self._send_link_state, daemon=True),
            threading.Thread(target=self._receive_link_state, daemon=True),
            threading.Thread(target=self._compute_paths, daemon=True)
        ]

        for thread in threads:
            thread.start()
        for thread in threads:
            thread.join()


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python Router.py <routerid> <routerport> <configfile>")
        sys.exit(1)

    router_id = int(sys.argv[1])
    port = int(sys.argv[2])
    config_file = sys.argv[3]
    router = Router(router_id, port, config_file)
    router.start()
