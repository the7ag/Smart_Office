# Smart Office Project

![image](https://github.com/the7ag/Smart_Office/assets/95578914/e60abf90-dc12-49d7-a41f-493d0ecc29fd)

The Smart Office Project is a comprehensive solution for automating and enhancing various aspects of an office environment. It incorporates several smart systems, including a smart gate, smart lighting, temperature-controlled fans, and a smart desk system. Additionally, it integrates facial recognition technology for client and employee identification. This repository provides the necessary code and resources to set up and operate the Smart Office Project.

## Features

- **Smart Gate:** The smart gate automatically opens and closes upon detecting authorized individuals, ensuring a seamless and secure entry/exit process.

- **Smart Lighting:** The smart lighting system adjusts the lighting levels based on occupancy, optimizing energy consumption and creating a comfortable workspace.

- **Temperature-Controlled Fan:** The temperature-controlled fan maintains a pleasant and productive environment by regulating the air circulation based on temperature readings.

- **Smart Desk System:** The smart desk system provides real-time availability status for employees, enabling efficient communication and collaboration.

- **Facial Recognition:** The project incorporates facial recognition technology to identify both clients and employees, enhancing security and providing personalized experiences.
## Video

### Design video
https://github.com/the7ag/Smart_Office/assets/95578914/17691323-7c7a-44a1-8efa-74277bf2a7f5
### Hardware Video


https://github.com/the7ag/Smart_Office/assets/95578914/a07760a1-5c0b-4cb7-a0f1-007fba58c286



## Architecture
![image](https://github.com/the7ag/Smart_Office/assets/95578914/9b2df036-6fa4-4a88-994f-3dbc63a22289)


The Smart Office Project architecture consists of the following components:

- **Smart Gate:** The smart gate module utilizes sensors and a motor to control the gate's opening and closing mechanism based on input received from the facial recognition system.

- **Smart Lighting:** The smart lighting system uses motion sensors to detect occupancy and adjusts the lighting levels accordingly. It is connected to the central controller.

- **Temperature-Controlled Fan:** The temperature-controlled fan employs temperature sensors to measure the ambient temperature and adjusts the fan speed accordingly. It is connected to the central controller.

- **Smart Desk System:** The smart desk system comprises smart discs placed on each desk to indicate employee availability. The discs are connected to the central controller and display the status of each employee.

- **Facial Recognition System:** The facial recognition system captures and analyzes facial features to identify individuals. It maintains separate databases for clients and employees, allowing for efficient access control and personalized experiences.

- **NodeMCU with UART:** The NodeMCU board acts as the central controller, receiving data from the various smart systems via UART communication.

- **Blynk App:** The Blynk mobile application provides a user-friendly interface to monitor and control the smart office systems. It receives data from the NodeMCU and displays it to the users.

## Installation and Setup

1. Clone the repository:

   ```bash
   git clone https://github.com/the7ag/Smart_Office.git
   ```

2. Install the required dependencies by referring to the individual component's setup instructions in their respective directories.

3. Configure the NodeMCU board to establish UART communication with the smart systems.

4. Set up the Blynk app by creating an account and configuring it to receive data from the NodeMCU.

5. Customize and upload the code provided in the repository to the NodeMCU.

6. Connect the smart gate, smart lighting, temperature-controlled fan, smart desk system, and facial recognition components to the NodeMCU as per the wiring diagrams and instructions provided.

7. Power on the system and monitor the Blynk app to observe the real-time data and control the smart office functionalities.

## Contributing

Contributions are welcome! If you encounter any issues or have suggestions for improvements, please submit an issue or a pull request. Make sure to follow the code of conduct when contributing to this project.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

We would like to thank the following resources and libraries that contributed to the development of the Smart Office Project:

- [OpenCV](https://opencv.org/) - Open Source Computer Vision Library
- [Blynk](https://blynk.io/) - Internet of Things Platform
- [NodeMCU](https://nodemcu.readthedocs.io/) - Lua-based firmware for IoT development

## Contact

For any inquiries or further information, please contact [the7ag22477@gmail.com](mailto:the7ag22477@gmail.com).

Happy Smart Office-ing!
