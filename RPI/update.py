# Code Flow
# Import necessary libraries (cv2, numpy, tensorflow, serial)
# Define a function called "start_model" to load the model and labels
# Define a function called "check_cam" to capture image from camera, preprocess it, make predictions using the model, and send the result back to Arduino via serial communication
# Initialize serial communication in the main function
# In the main function, create a while loop to continuously listen for incoming data from the Arduino
# When a signal is received from Arduino indicating an obstacle is detected, check if the obstacle has been detected multiple times in a row to ensure it is not a false positive
# If the obstacle has been detected multiple times, call the "check_cam" function to capture an image and make a prediction
# Send the result of the prediction back to Arduino via serial communication
# Repeat this process until the program is manually stopped
# Be ready to handle serial data like an interrupt.

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
            print("Bottle WINS")
        else:
            ser.write(str(2).encode('utf-8'))
            print("NoBottle WINS")
    camera.release()

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    start_model()
    camera_once_done = False
    count_ones = 0

    # Use a while loop to continuously check for serial data
    while True:
        # Use the in_waiting attribute to check if there is data waiting to be read
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if line == '1':
                count_ones += 1
            if line == '1' and camera_once_done != True and count_ones > 50:
                check_cam()
                camera_once_done = True
                count_ones = 0
            elif line == '0':
                camera_once_done = False
                count_ones = 0
