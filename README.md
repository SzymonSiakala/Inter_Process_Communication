# Inter-Process Communication
This project demonstrates the implementation of a basic client-server application in C++, utilizing Boost::Asio. The main objective of this application is to facilitate the seamless transfer of a file from the client to the server over a network connection. The following functionality is implemented:

## Server Functionality
- The server listens for incoming connections from clients.
- Upon connection, clients can send files to the server.

## Client Functionality
- File is passed to the client as a command-line parameter.
- The client can connect to the server using its IP address and port number.
- The client can send files to the server over the established TCP connection.

## Running the Project
To run the project, you can use the following terminal commands:
1. Run the server:
   ```cmd
   "Server application.exe"
   ```
2. Run the client:
   ```cmd
   "Client application.exe" file_to_send.txt
   ```

## Usage
1. **Server:**
   - Compile and run the server program using the provided source code.
   - The server will listen for incoming connections on a specified port.
   - It will process client files as described above.

2. **Client:**
   - Compile and run the client program using the provided source code.
   - The client can establish a connection to the server by providing the server's IP address and port number.
   - Send file to the server.

Please refer to the source code and comments for detailed implementation details. Enjoy experimenting with this simple client-server application for sending files!