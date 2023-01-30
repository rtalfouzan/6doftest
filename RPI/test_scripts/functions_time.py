import cv2
import numpy as np
from tensorflow.keras.models import load_model
import serial
import time

def start_model():
    global labels
    global model
    global image
    global ret

    # Load the model
    model = load_model('model.h5')
    print(model.summary())
    print("\n\n Model Loaded \n\n")

    # Grab the labels from the labels.txt file. This will be used later.
    labels = open('labels.txt', 'r').readlines()

def check_cam():
    global camera , detection , func_calls , state

    camera = cv2.VideoCapture(0)

    ret, image = camera.read()

    if ret:
        # Resize the raw image into (224-height,224-width) pixels.
        image = cv2.resize(image, (224, 224), interpolation=cv2.INTER_AREA)
        # Make the image a numpy array and reshape it to the models input shape.
        image = np.asarray(image, dtype=np.float32).reshape(1, 224, 224, 3)
        # Normalize the image array
        image = (image / 127.5) - 1
        probabilities = model.predict(image)
        pred = (labels[np.argmax(probabilities)][0])

        if pred == '0':
                ser.write(str(1).encode('utf-8'))
                print("Bottle")
        else:
            ser.write(str(2).encode('utf-8'))
            print("No Bottle")
        ser.reset_input_buffer()
    camera.release()

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    start_model()
    state = 0

    test_timing =True
    time_serial_read = True
    time_check_cam = False

    print_all_serial = False

    # Use a while loop to continuously check for serial data
    while test_timing:
        if time_serial_read:
            start_time = time.time()
            state = ser.readline().decode('utf-8').strip()
            print("State ", state)
            print("Time Read Serial : ", time.time() - start_time)
        elif time_check_cam:
            start_time = time.time()
            check_cam()
            print("Time Check Cam: ", time.time() - start_time)

    while print_all_serial:
        while ser.in_waiting:
            serial_data = ser.readline().decode('utf-8').strip()
            print(serial_data)

