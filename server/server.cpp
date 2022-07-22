// Reference: https://ncona.com/2019/05/using-thread-pools-in-cpp/
#include "server.hpp"

Server::Server(QueryEngine *engine) : done(false)
{

    // Initialize the worker pool to handle requests

    // This returns the number of threads supported by the system. If the
    // function can't figure out this information, it returns 0. 0 is not good,
    // so we create at least 1
    auto numberOfThreads = std::thread::hardware_concurrency();
    if (numberOfThreads == 0)
    {
        numberOfThreads = 1;
    }

    for (unsigned i = 0; i < numberOfThreads; ++i)
    {
        // The threads will execute the private member `doWork`. Note that we need
        // to pass a reference to the function (namespaced with the class name) as
        // the first argument, and the current object as second argument
        threads.push_back(std::thread(&Server::doWork, this));
    }

    query_engine = engine;
}

void Server::start_listening(int PORT)
{

    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == 0)
    {
        std::cout << "Failed to create socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    // Listen to a port
    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        std::cout << "Failed to bind to port " << PORT << "errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    // Start listening
    if (listen(sockfd, 10) < 0)
    {
        std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Started listning on " << PORT << "\n";

    while (true)
    {
        // Grab a connection from the queue
        auto addrlen = sizeof(sockaddr);
        int connection = accept(sockfd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);
        std::cout << "Grabbed a connection " << connection << "\n";
        if (connection < 0)
        {
            std::cout << "Failed to grab connection. errno: " << errno << std::endl;
            exit(EXIT_FAILURE);
        }

        queueWork(connection);

        // Read from the connection
    }

    close(sockfd);
}

Server::~Server()
{
    // So threads know it's time to shut down
    done = true;

    // Wake up all the threads, so they can finish and be joined
    workQueueConditionVariable.notify_all();

    for (auto &thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

void Server::queueWork(int fd)
{
    // Grab the mutex
    std::lock_guard<std::mutex> g(workQueueMutex);

    // Push the request to the queue
    workQueue.push(fd);

    // Notify one thread that there are requests to process
    workQueueConditionVariable.notify_one();
}

void Server::doWork()
{
    // Loop while the queue is not destructing
    while (!done)
    {
        int connection;

        // Create a scope, so we don't lock the queue for longer than necessary
        {
            std::unique_lock<std::mutex> g(workQueueMutex);
            workQueueConditionVariable.wait(g, [&]
                                            {
          // Only wake up if there are elements in the queue or the program is
          // shutting down
          return !workQueue.empty() || done; });

            if (!workQueue.empty())
            {
                connection = workQueue.front();
                workQueue.pop();
            }
        }

        processRequest(connection);
    }
}

std::string Server::make_server_response_from_query_response(QueryResponse *query_response)
{
    // Should parse in a better way
    // Alternative is JSON
    return query_response->response_status + "\n" + query_response->message + "\n" + query_response->result.second;
}

void Server::processRequest(int connection)
{
    while (true)
    {
        char buffer[1024];

        auto bytesRead = read(connection, buffer, 1024);

        if (bytesRead < 0)
            continue;

        if (bytesRead == 0)
        {
            close(connection);
            std::cout << "Closing client connection";
            break;
        }

        std::string query = buffer;
        QueryResponse *query_response = query_engine->process_and_execute(query);

        std::string response = make_server_response_from_query_response(query_response);
        send(connection, response.c_str(), response.size(), 0);

        // Add some work to the thread pool
        bzero(buffer, 1024);
    }
}

int main()
{
    Storage *storage_engine = Storage::factory(IN_MEMORY);
    QueryEngine *query_engine = new QueryEngine(storage_engine);
    Server *server = new Server(query_engine);

    server->start_listening(8080);
}