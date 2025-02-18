# News Broadcasting System - Concurrent Programming & Synchronization

This project simulates a **news broadcasting system** using concurrent programming and synchronization techniques. The system consists of four main components: Producers, Dispatcher, Co-Editors, and Screen Manager, each communicating via thread-safe queues.

## Components

### 1. Producers
- Generate messages in the format: `producer <id> <type> <count>`
- Types: `'SPORTS'`, `'NEWS'`, `'WEATHER'`
- Each Producer passes its messages to a private bounded queue, followed by a "DONE" signal once production is complete.

### 2. Dispatcher
- Reads from producer queues using **Round Robin**.
- Sorts messages into three queues based on type: **SPORTS**, **NEWS**, **WEATHER**.
- Sends a "DONE" signal to Co-Editors once all Producers have finished.

### 3. Co-Editors
- Process messages from the Dispatcher queues.
- Simulate "editing" with a 0.1-second delay before passing messages to the Screen Manager.
- Forward "DONE" signals to the Screen Manager.

### 4. Screen Manager
- Receives and displays messages from the Co-Editors.
- After receiving three "DONE" signals (one from each Co-Editor), it displays a final "DONE" message.

## Synchronization

- **Bounded Buffers** are used between Producers and Dispatcher, managed with semaphores for mutual exclusion and counting semaphores for tracking full/empty states.
- **Unbounded Buffers** are used between Dispatcher and Co-Editors, allowing for unrestricted message flow.

## Configuration

The system reads a configuration file that specifies the number of products for each Producer, their queue sizes, and the Co-Editor queue size.

Example configuration:

```txt
PRODUCER 1
30
queue size = 5

PRODUCER 2
25
queue size = 3

PRODUCER 3
16
queue size = 30

Co-Editor queue size = 17
```
## Running the Program

### Compile the program using the Makefile:
```bash
make
```
### Run the program with the configuration file as an argument:

```bash
./main config.txt
```
## Files

- `main.c`: The entry point of the program.
- `producer.c`: Handles the logic for the Producer threads.
- `dispatcher.c`: Implements the Dispatcher thread logic.
- `coeditor.c`: Contains the logic for the Co-Editors.
- `screen_manager.c`: Manages the display of messages on the screen.
- `bounded_buffer.c`: Implements the bounded buffer using semaphores.
- `makefile`: For compiling the project.

## Conclusion

This project demonstrates how to handle concurrent threads and synchronization using semaphores, ensuring thread-safe communication between Producers, Dispatcher, Co-Editors, and the Screen Manager.


