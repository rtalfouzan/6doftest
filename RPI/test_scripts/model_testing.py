import cv2
import numpy as np

import tensorflow as tf
from tensorflow.keras.models import load_model

# Start the camera
cap = cv2.VideoCapture(0)
model = load_model('model.h5')
print(model.summary())
print("\n\n Model Loaded \n\n")

# Grab the labels from the labels.txt file. This will be used later.
labels = open('labels.txt', 'r').readlines()


while True:
    # Capture the image from the camera
    ret, image = cap.read()

    # Resize the image
    image_ = cv2.resize(image, (224, 224), interpolation=cv2.INTER_AREA)
    image = np.asarray(image_, dtype=np.float32).reshape(1, 224, 224, 3)
    # Normalize the image array
    image = (image / 127.5) - 1
    probabilities = model.predict(image)
    pred = (labels[np.argmax(probabilities)][0])
    print("Prediction :" , pred)
    # Display the image
    cv2.imshow("Camera Feed", image_)

    # Press 'q' to exit the loop
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera and close the window
cap.release()
cv2.destroyAllWindows()


