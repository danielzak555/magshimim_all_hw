# Ex12 - Synchronisation

Link to ex12 google drive folder: <a href="https://drive.google.com/drive/u/0/folders/1ixuiGWpzmVDjs2SOgnXmesXpUbFegEFo/" target="_blank">Ex12 Google Drive</a>

Exercise twelve in 'Advanced Programming' course .<br>
In the previous exercise, we saw that working with threads is not always easy, especially when multiple threads are trying to access a shared resource.<br>
Through this exercise, we will learn different methods to synchronize thread access to shared resources, specifically using mutexes.<br>
We will build a program that manages a 'Message Board' and distribute messages to different users.<br>
Our code will consist several synchronization elements such as:
- std::mutex
- std::lock_guard
- std::unique_lock
- std::condition_variable

The purpose of this exercise is to understand how to synchronize threads and make sure they don't "step on each other's toes...".

### Ex12Part2Files
Contains base files for Ex12 main part - Message Board

### Ex12Part3Files
Contains base files for Ex12 first bonus - Readers & Writers

### Ex12Part4Files
Contains base files for Ex12 second bonus - Dining Philosophers Problem

### .gitlab-ci.yml
Pipeline file for auto-tests

## Submission details
Files to submit:

#### project1 - Threads
In this part you need to fix the previous exercise, so that the prints to the files will not be scrambled.
- Threads.h
- Threads.cpp
- main11.cpp

#### project2 - Message Board
This exercise focuses on synchronizing a system that reads messages and writes messages in parallel.
- MessageSender.h
- MessageSender.cpp
- main12.cpp