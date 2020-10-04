# Leader election in distributed systems

Simulated implementation of leader election in distributed systems.

In distributed systems it is common for some tasks to require a leader / coordinator node. Because of that, it is necessary an algorithm to elect a new leader if the previous one fails.

## Ring Election

- At most 3n-1 messages

## Bully Election

- Order N^2 messages
- More robust
