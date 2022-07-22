// Reference: https://ncona.com/2019/05/using-thread-pools-in-cpp/

#include <sys/socket.h>       // For socket()
#include <netinet/in.h>       // For sockaddr_in
#include <cstdlib>            // For exit() and EXIT_FAILURE
#include <iostream>           // For cout
#include <unistd.h>           // For read
#include <thread>             // std::thread
#include <vector>             // std::vector
#include <queue>              // std::queue
#include <mutex>              // std::mutex
#include <condition_variable> // std::condition_variable

#include "../query-engine/query-engine.hpp"

// This class manages a thread pool that will process requests
class Server
{
public:
  Server(QueryEngine *engine);

  // The destructor joins all the threads so the program can exit gracefully.
  // This will be executed if there is any exception (e.g. creating the threads)
  ~Server();

  QueryEngine *query_engine;
  
  void start_listening(int PORT);
  

private:
  // This function will be called by the server, every time there is a request
  // that needs to be processed by the thread pool
  void queueWork(int fd);

  std::string make_server_response_from_query_response(QueryResponse *query_response);
  // This condition variable is used for the threads to wait until there is work
  // to do
  std::condition_variable_any workQueueConditionVariable;

  // We store the threads in a vector, so we can later stop them gracefully
  std::vector<std::thread> threads;

  // Mutex to protect workQueue
  std::mutex workQueueMutex;

  // Queue of requests waiting to be processed
  std::queue<int> workQueue;

  // This will be set to true when the thread pool is shutting down. This tells
  // the threads to stop looping and finish
  bool done;

  void (*work)(std::string request);

  // Function used by the threads to grab work from the queue
  void doWork();

  void processRequest(int connection);
};
