'''
Finds edges in your eye
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

edges = cv2.Canny(blur_image, 100, 200)
cv2.imshow('edge_detection', edges)
