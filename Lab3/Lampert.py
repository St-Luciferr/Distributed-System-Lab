# define Lampert clock
class LamportClock:
    # initialize clock
    def __init__(self):
        self.clock = 0
    # increment clock 
    def increment(self):
        self.clock += 1
    # update clock
    def update(self, received_time):
        self.clock = max(self.clock, received_time) + 1
    # get current clock
    def get_timestamp(self):
        return self.clock

# define Process to use Lampert clock
class Process:
    # Initialize process with name
    def __init__(self, name):
        self.name = name
        self.clock = LamportClock()
    # Send message to another Process
    def send_message(self, receiver, message):
        print("\tBefore Synchronization:")
        print(f"\t{self.name}'s Lamport Clock: {self.clock.get_timestamp()}")
        print(f"\t{receiver.name}'s Lamport Clock: {receiver.clock.get_timestamp()}")
        receiver.clock.update(self.clock.get_timestamp())
        self.clock.increment()
        print("\tAfter Synchronization:")
        print(f"\tMessage: {message}")
        print(f"\t{self.name}'s Lamport Clock: {self.clock.get_timestamp()}")
        print(f"\t{receiver.name}'s Lamport Clock: {receiver.clock.get_timestamp()}\n")

if __name__ == "__main__":
    # Create two processes
    process1 = Process("Sam")
    process2 = Process("Harry")
    
    # Initial clock values before the exchange
    print("Initial Lamport Clock values")
    print(f"Timestamp of Process 1: {process1.clock.get_timestamp()}")
    print(f"Timestamp of Process 2: {process2.clock.get_timestamp()}\n")
    
    # Simulate some message exchanges
    process1.send_message(process2, "Hello from Sam to Harry")
    process2.send_message(process1, "Hello from Harry to Sam")
    process2.clock.increment()
    process2.clock.increment()
    process1.send_message(process2, "How are you?")
    process2.send_message(process1, "I'm doing fine, thanks!")
    
    # Final clock values after the exchanges
    print("Final Lamport Clock Values:")
    print(f"Timestamp of Process 1: {process1.clock.get_timestamp()}")
    print(f"Timestamp of Process 2: {process2.clock.get_timestamp()}")