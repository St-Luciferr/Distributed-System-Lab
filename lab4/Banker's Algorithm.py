class BankerAlgorithm:
    def __init__(self, total_resources, total_processes):
        # Initialize the Banker's Algorithm with the total number of resources and processes
        self.total_resources = total_resources
        self.total_processes = total_processes
        self.available = total_resources.copy()
        self.maximum = [[0 for _ in range(len(total_resources))] for _ in range(total_processes)]
        self.allocated = [[0 for _ in range(len(total_resources))] for _ in range(total_processes)]
        self.need = [[0 for _ in range(len(total_resources))] for _ in range(total_processes)]
        self.finish = [False] * total_processes

    def set_maximum_resources(self, max_resources):
        # Set the maximum need of each process
        for i in range(self.total_processes):
            for j in range(len(max_resources[i])):
                self.maximum[i][j] = max_resources[i][j]
                self.need[i][j] = max_resources[i][j] - self.allocated[i][j]

    def set_allocated_resources(self, allocated_resources):
        # Set the allocated resources of each process
        for i in range(self.total_processes):
            for j in range(len(allocated_resources[i])):
                self.allocated[i][j] = allocated_resources[i][j]
                self.available[j] -= allocated_resources[i][j]
                self.need[i][j] = self.maximum[i][j] - self.allocated[i][j]

    def request_resources(self, process_id, requested_resources):
        # Check if the requested resources can be granted while keeping the system in a safe state
        for i in range(len(requested_resources)):
            if requested_resources[i] > self.need[process_id][i]:
                print("Error: Process has exceeded its maximum claim.")
                return False

            if requested_resources[i] > self.available[i]:
                print("Process must wait. Resources are not available.")
                return False

        # Temporary allocation to check for safety
        for i in range(len(requested_resources)):
            self.available[i] -= requested_resources[i]
            self.allocated[process_id][i] += requested_resources[i]
            self.need[process_id][i] -= requested_resources[i]

        if self.is_safe_state():
            print("Resources allocated to Process", process_id)
            return True
        else:
            print("Resources denied for Process", process_id, "to avoid deadlock.")
            # Roll back the temporary allocation
            for i in range(len(requested_resources)):
                self.available[i] += requested_resources[i]
                self.allocated[process_id][i] -= requested_resources[i]
                self.need[process_id][i] += requested_resources[i]
            return False

    def release_resources(self, process_id):
        # Release the resources held by the specified process
        for i in range(len(self.allocated[process_id])):
            self.available[i] += self.allocated[process_id][i]
            self.allocated[process_id][i] = 0
            self.need[process_id][i] = self.maximum[process_id][i]

    def is_safe_state(self):
        # Check if the current system state is safe (no deadlock)
        work = self.available.copy()
        self.finish = [False] * self.total_processes
        safe_sequence = []

        while True:
            found = False
            for i in range(self.total_processes):
                if not self.finish[i] and all(self.need[i][j] <= work[j] for j in range(len(work))):
                    work = [work[j] + self.allocated[i][j] for j in range(len(work))]
                    self.finish[i] = True
                    safe_sequence.append(i)
                    found = True

            if not found:
                break

        if all(self.finish):
            print("Safe Sequence:", safe_sequence)
            return True
        else:
            print("System is in an unsafe state (deadlock).")
            return False


# Example usage
total_resources = [8, 6, 9]
total_processes = 6
banker_algorithm = BankerAlgorithm(total_resources, total_processes)

maximum_resources = [
    [4, 3, 2],
    [1, 2, 2],
    [7, 0, 5],
    [0, 1, 1],
    [4, 3, 1],
    [3, 2, 1]
]

allocated_resources = [
    [1, 0, 0],
    [0, 1, 1],
    [3, 0, 2],
    [2, 1, 1],
    [0, 0, 2],
    [0, 0, 0]
]

banker_algorithm.set_maximum_resources(maximum_resources)
banker_algorithm.set_allocated_resources(allocated_resources)

if banker_algorithm.is_safe_state():
    # Resource request for Process 5
    process_id = 5
    requested_resources = [1, 1, 0]
    banker_algorithm.request_resources(process_id, requested_resources)

    # Resource release for Process 2
    process_id = 2
    banker_algorithm.release_resources(process_id)