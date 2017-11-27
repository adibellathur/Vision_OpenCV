import cv2
import numpy as np

camera = cv2.VideoCapture(0)

while True:
	# grab the current frame
	(grabbed, frame) = camera.read()
		 
	# if we are viewing a video and we did not grab a frame,
	# then we have reached the end of the video
	if not grabbed:
		break

	#Do stuff here
	# define range of blue color in HSV
	lower_blue = np.array([110,50,50])
	upper_blue = np.array([130,255,255])
	
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
	
	# Threshold the HSV image to get only blue colors
	mask = cv2.inRange(hsv, lower_blue, upper_blue)
	
	# Bitwise-AND mask and original image
	blue_only = cv2.bitwise_and(frame,frame, mask= mask)
	
	
	# show the frame to our screen
	cv2.imshow("Frame", hsv)
	cv2.imshow("BLUEFRAME", blue_only)

	key = cv2.waitKey(1) & 0xFF
			 
	# if the 'q' key is pressed, stop the loop
	if key == ord("q"):
		break

# cleanup the camera and close any open windows
camera.release()
cv2.destroyAllWindows()
