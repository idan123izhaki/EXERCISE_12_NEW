# EXERCISE_12_NEW

EXERCISE_1: fixed the last exercise 12. Files: in last ex_12.

EXERCISE_2_1: Implements the MessageSender class. The system writes into text file messages, that it read from data file, according all the current users that connect. using SET to manage the data structher. Files: MessageSender.hpp, MessageSender.cpp, mainMessageSender.cpp, output.txt.

EXERCISE_2_2: Creating 2 threads in order to read the data from admin file, and send the messages to logged in users -> simultaneously. Files: same files as EXERCISE_2_1.

BONUS_1: Implements the option of reading and writing from the same file simultaneously. Using shared_mutex and shared_lock. Files: readersWriters.hpp, readersWriters.cpp, mainreadersWriters.cpp, example.txt.

BONUS_2: Solving the dining philosophers problem. Files: philosopher.hpp, philosopher.cpp.

BONUS_3_1: Threads Synchronization using atomic operations. Files: exercise_3_1.cpp.

BONUS_3_2: Threads Synchronization using Peterson's Algorithm. Files: exercise_3_2.cpp.

BONUS_3_3: Threads Synchronization using Bakery Algorithm. Files: exercise_3_3.cpp.
