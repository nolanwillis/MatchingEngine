
## About
#### The main goal of this project was to create a smaller tech demo with features usually scene in high freuency trading. The backend is done completely in C++ 20 with a basic single webpage for the client. Communication between the two is done exclusivly through WebSockets for simplicity and all data is saved using a sqlite database on the server. With this demo multiple users can log on, place limit or market orders, view live order book feeds, and completed trades. 
## Features
- Multithreading, enabling multiple users and high throughput.
- Custom messaging via WebSockets using binary for smaller messaging.
- Database has a seperate writer thread, so reads and writes from the database don't slow things down.
- Responsive event driven UI.
- Uses Google Test for unit testing all aspects of the project. 
## Architecture
### Engine
- Keeps track of users and WebSocket connections.
- Initial message handling, decides if the message should go to the OrderBookManager or directly to DatabaseManager.
- Defines broadcast functions to send information back to the client.
### Order Book Manager
- Creates and manages all the OrderBooks. 
- Directs order related messages to the correct OrderBook.
- Manages the lifetimes of all the OrderBookWorkers using a promise/shared future.
    #### Simplified UML 
    ![Class Diagram](OrderBookUML.png)
    #### Sequence Diagram
    ![Class Diagram](OrderBookSequence.png)
### Database Manager
- Initializes the SQLite database.
- Provides functions for adding/retrieving users and trades from the database.
- Manages writer thread for writing trades to the database.
