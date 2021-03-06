PROJECT OVERVIEW:
I was supposed to create a way to have a client and data server that could communicate to each other when 3 different user requests from a client were sent to the server. The 3 different requests were "hello", "data person", and "bye" where "person" in the data request returned an integer from 1 to 100 from the data server back to the client when the client sent the data server a request for data of a person. The project only used 3 people that could be requested of data, John Doe, Jane Smith, and Joe Smith. The use of only 3 people allowed for only 3 major response buffers to be created, 1 for each person, in conjunction with 1 request buffer. (we didn't have to handle anything too complicated, this is a simple client/server exercise). Each person also had a certain number of worker threads allocated to them, so splitting of threads/buffers and all that was simpler to use a static amount of people during the exercise and learning experience. 

EXPLANATION OF PROJECT FOLDERS: 
I did each of these 4 projects during the Introduction to Computer Systems course and each of them added into one overall project. The final stage of the overall project is within the Network_Handling folder. The other folders were just starting/intermediate project leading to the final one. 

The projects were done in this order:
1. Process_Forking - forked a process to separately handle the data server. 
2. Thread_Handling - implemented worker threads using bounded buffer and semaphores instead of how workers were defined in the previous project folder
3. Thread_Handling_Improvement - implemented a single event handler thread instead of spawning tons and tons of worker threads. 
4. NetworkHandling - turned the request channels into Network_request_channels, using sockets and network programming to communicate rather than pipelines and local files. This was the final stage of the overall project and implements all of the changes of the previous project folder as well (referring to the process_forking folder, and thread_handling_improvement folder projects). 

ISSUES WITH PROJECT: 
Overall, there are a few issues and glitches when running the project in general. Sometimes, for some strange reason, the data server would get hung up and basically stop functioning correctly. It may have been the fault of the client somewhere too, however. 

GOOD SIDE OF PROJECT: 
When it works correctly, usually for some perfect ratio of worker threads compared to the buffer size and input request size, the client/data server communicates well, outputs overall answer and totally can handle MULTIPLE clients at the same time on the same server. 
