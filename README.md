#PiBoard -  A Concept on Communication over Serial using a custom-implmemented protocol

This repository contains the code and documentation for PiBoard, a whiteboard chat application for the Raspberry Pi, developed as part of Lab P20. The application allows users to draw on a canvas and share their drawings with others in real-time.

## Features

- **Separate Send and Receive Windows**: The application has two windows, one for sending drawings and another for receiving drawings from others.
- **Drawing Tools**: Users can draw lines, points, circles, rectangles, and erase parts of the canvas using various drawing tools.
- **Serialization and Deserialization**: The application uses QDataStream to serialize and deserialize the drawing data, allowing it to be transmitted over the network.
- **Multi-threading**: The sending and receiving of data are handled by separate threads, ensuring smooth operation and responsiveness.
- **Thread Safety**: Mutexes are used to ensure thread safety and prevent race conditions when accessing shared resources.
- **Communication Protocol**: A simple communication protocol has been implemented to test the GPIO connectivity between the sender and receiver.

## Installation

1. Clone the repository: `git clone https://github.com/Bananz0/PiBoard.git`
2. Install the required dependencies (Qt, WiringPi, etc.).
3. Build the project using your preferred C++ build system.

## Usage

1. Run the application.
2. On the send window, use the drawing tools to create your drawings.
3. The receive window will display the drawings shared by others in real-time.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE.txt).

## Acknowledgments

- Special thanks to the instructors and teaching assistants for their guidance and support during the lab.
- The Qt documentation and examples were invaluable resources.
