## Bottle Picking Robotic Arm
### Summary
This project consists of two parts: one is written in Python and the other in Arduino.

The Python code uses OpenCV and TensorFlow to implement an object detection system. It starts by loading a pre-trained model and capturing video feed from a camera.
- The captured video frames are then resized
- Transformed into a numpy array, and normalized.
- The normalized image is passed through the model to get a prediction on the object in the image.

The Arduino code uses the serial communication protocol to receive data from the Python code.
- It waits for the data to arrive and performs actions based on the received data. For example, when the data received is "1", the Arduino code will send data  "1" RPI using Serial as  indicating the presence of a object. When the data received is "0", no object is there.

Overall, this project is a simple object detection system that can be used to detect objects in real-time. The Python code performs image processing and object detection, while the Arduino code provides a way to interact with the physical world based on the prediction made by the Python code.
### To Run
- Run Raspberry pi code
    - python **detection.py**
- Run code on arduino using arduino ide
    - **robot_move.ino**
- Connect arduino to RPI through serial (USB)

### Programs Explanation
- Raspberry Pi : Run the script for Detection of bottles
    ```
    python detection.py
    ```
    - For detection of bottles you need to run on RPI
    - Defines a start_model function to load a TensorFlow model (keras_model.h5) and read class labels from a file (labels.txt)
    - Defines a check_cam function to capture an image from a camera, preprocess it, and use the model to predict the image's class
    - Establishes a serial connection to /dev/ttyACM0 at 9600 baud rate
    - Calls start_model to load the model and labels
    - Starts a while loop to continuously check for serial data
    - If serial data is received and the state is not 3:
    - Reads the state from the serial data and sets it as the current state
    - If the state changed, it:
    - Prints the state
    - If state is 1, calls check_cam to capture and predict an image
    - If state is 2, prints "Robot Throwing Bottle"
    - If state is 3, prints "Arm back in Origin Position" and resets detection
    - Updates prev_state to be the current state

- Arduino : Run script to start arm motion and ultra sonic detection
    ```
    robot_move.ino
    ```

    - Ultrasonic Sensor

        - TrigPin and EchoPin defined for the sensor
        Code for measuring distance using pulseIn() function
        Servos

    - Six servo motors are used for different joints of the arm
    Servo objects for each servo motor are defined
    Servos are attached to corresponding pins
    - setArm() function

        - This function moves all the servos to the specified angles
        setup() function

    - Initializes serial communication and sets the baud rate
    Initializes the pins for the ultrasonic sensor and LED
    Attaches the servo motors to the corresponding pins
    Calls setArm() function to initialize the arm position
    - read_distance() function

        - Reads the distance from the ultrasonic sensor and stores it in the distance variable
        -If the distance is between 7 and 17, it sends "1" to the serial port
        -If the distance is greater than 17, it sends "0" to the serial port
    - loop() function

        - Reads the serial data if available
        - If the data is "1", it calls the setArm() function to move the arm
        - It also calls the read_distance() function every 300 milliseconds to update the distance information

---

- **functions_time.py**
    - Defines a start_model function to load a pre-trained model from a .h5 file, and read labels from a .txt file.
    - Defines a check_cam function to capture video from a camera, process the image with the model, and write the predicted result to serial port.
    - Connects to the serial port using '/dev/ttyACM0' with baudrate 9600.
    - Initializes the global variables and calls start_model.
    - Uses a while loop to continuously check for serial data and time performance.
    - If time_serial_read is True, it reads data from the serial port and measures time.
    - If time_check_cam is True, it calls the check_cam function and measures time.
    - Uses another while loop to print all incoming serial data if print_all_serial is True.