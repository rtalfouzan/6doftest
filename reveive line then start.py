#after receving signal from arduino that an obstical/object is infront of the robot the code will check if this obstical is a bottle send 1 back to 
# arduino or not a bottle and sends 2 to the arduino



import cv2
import numpy as np
#import tensorflow as tf
#import tensorflow as tf
from tensorflow.keras.models import load_model
#from keras.models import load_model
import tensorflow
import serial



def  start_model():
    global labels
    global model
    global image
    global ret
    
    # Load the model
    model = load_model('keras_model.h5')
    #custom_objects={'Functional': tensorflow.keras.models.Model})

    print(model.summary())

    # CAMERA can be 0 or 1 based on default camera of your computer.
    

    # Grab the labels from the labels.txt file. This will be used later.
    labels = open('labels.txt', 'r').readlines()
            # Grab the webcameras image.
    
        

        # Make the image a numpy array and reshape it to the models input shape.
   

def check_cam():
    global camera
    
    
    camera = cv2.VideoCapture(0)

    count = 0
    counta = 0
    countb = 0

    while True:
        ret, image = camera.read()
        if ret:
            # Resize the raw image into (224-height,224-width) pixels.
            image = cv2.resize(image, (224, 224), interpolation=cv2.INTER_AREA)
            # Show the image in a window
            #cv2.imshow('Webcam Image', image)
            # Make the image a numpy array and reshape it to the models input shape.
            image = np.asarray(image, dtype=np.float32).reshape(1, 224, 224, 3)
            # Normalize the imagNo training configuration found in the save file, so the model was *not* compiled. Compile it manually.e array
            image = (image / 127.5) - 1
            probabilities = model.predict(image)
            count = count +1
            #print(labels[np.argmax(probabilities)])
            pred = (labels[np.argmax(probabilities)][0])

                  
            if ( count < 11):
                if ( pred == '0'):
                    counta = counta + 1
                elif ( pred == '1'):
                    countb = countb + 1
            else:
                if (counta > countb):
                    print("Bottle WINS")
                    ser.write(str(1).encode('utf-8'))
                    break
                else:
                    print("NoBottle WINS")
                    ser.write(str(2).encode('utf-8'))
                    break
        

    
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    start_model()
    camera_once_done = False
    count_ones = 0
    while True:
        if ser.in_waiting > 0:
            line = ser.readline()
            if line.decode('utf-8').strip() == '1':
                count_ones += 1
            if line.decode('utf-8').strip() == '1' and camera_once_done != True and count_ones > 50:
                print('im in')
                check_cam()
                print('im Done')
                camera.release()
                #cv2.destroyAllWindows()
                camera_once_done = True
                count_ones = 0
            elif line.decode('utf-8').strip() == '0':
                camera_once_done = False
                count_ones = 0
