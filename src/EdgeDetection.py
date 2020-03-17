import cv2 
import numpy as np 

input = cv2.VideoCapture(0)

if (!input.isOpened()):
    print("Video not working")
    

while(input.isOpened()):
    ret, frame = input.read()

    if ret:
        gray =  cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        grayFiltered = cv2.bilateralFilter(gray, 7, 50, 50)

        edges = cv2.Canny(gray, 20, 30)
        edgesFiltered = cv2.Canny(grayFiltered, 60, 120)
        edgesHighTresh = cv2.Canny(gray, 60, 120)

        images = np.hstack((gray, edges, edgesFilters))

        cv2.imshow('frame', images)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        break


input.release()
input.destroyAllWindows()