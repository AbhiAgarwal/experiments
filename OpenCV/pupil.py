import cv2
import numpy as np
import random

image = cv2.imread('eye.jpg')
cv2.imshow('main_image', image)

gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) #makes into grayscale
blurredgray_image = cv2.medianBlur(gray_image, 5)

cv2.imwrite('gray_image.png', blurredgray_image)

thresh = 21
im_bw = cv2.threshold(blurredgray_image, thresh, 400, cv2.THRESH_BINARY)[1]

cv2.imshow('gray_image', im_bw)

circles = cv2.HoughCircles(blurredgray_image, cv2.cv.CV_HOUGH_GRADIENT, 1, 20, param1 = 50, param2 = 30, minRadius = 0, maxRadius = 50)
circles = np.uint16(np.around(circles))

bestCircle = []
minValue = pow(2, 30)

for i in circles[0, :]:
    total = 0
    total += image[i[1]][i[0]][2]
    total += image[int(i[1] + (i[2]/2))][i[0]][2]
    total += image[int(i[1] - (i[2]/2))][i[0]][2]
    total += image[i[1]][int(i[0] + (i[2]/2))][2]
    total += image[i[1]][int(i[0] + (i[2]/2))][2]
        
    if total < minValue:
        minValue = total
        bestCircle = i
        
cv2.circle(image,(bestCircle[0],bestCircle[1]),bestCircle[2],(0,255,0),2)
cv2.circle(image,(bestCircle[0],bestCircle[1]),2,(0,0,255),3)
cv2.imshow('detected circles', image)
