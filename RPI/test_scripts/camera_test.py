import cv2

# Start the camera
cap = cv2.VideoCapture(0)

while True:
    # Capture the image from the camera
    ret, image = cap.read()

    # Resize the image
    image = cv2.resize(image, (224, 224), interpolation=cv2.INTER_AREA)

    # Display the image
    cv2.imshow("Camera Feed", image)

    # Press 'q' to exit the loop
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera and close the window
cap.release()
cv2.destroyAllWindows()

