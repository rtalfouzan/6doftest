import cv2
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import load_model
import serial

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
    global camera
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
    prev_state = 1

    # Use a while loop to continuously check for serial data
    while True:
        if ser.in_waiting > 0:
            state = ser.readline().decode('utf-8').strip()
            if state != prev_state:
                print("State ",state)
            if state == '1': # Obstacle detected by US
                check_cam()
            elif(state == '2'):
                print("Robot Throwing Bottle")
            elif(state == '3'):
                print("Arm back in Origin Position")
            prev_state = state



