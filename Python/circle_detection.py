'''
Finds all the circles within your eye
'''

import cv2
import cv2.cv as cv
import numpy as np

image = cv2.imread('eye-image.jpg')
cv2.imshow('main_image', image)
gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
cv2.imwrite('gray_image.png', gray_image)
im_gray = cv2.imread('gray_image.png', cv2.CV_LOAD_IMAGE_GRAYSCALE)
blur_image = cv2.medianBlur(im_gray, 5)

circles = cv2.HoughCircles(blur_image, cv2.cv.CV_HOUGH_GRADIENT, 1, 
                            10, param1 = 100, param2 = 30, minRadius = 20, maxRadius = 22)
circles = np.uint16(np.around(circles))

# [x, y, radius]
for i in circles[0,:]:
    cv2.circle(image, (i[0], i[1]), i[2], (0, 255, 0), 1) # draw the outer circle
    cv2.circle(image, (i[0], i[1]), 1, (0, 0, 255), 2) # draw the center of the circle
    
cv2.imshow('detected_circles', image)
