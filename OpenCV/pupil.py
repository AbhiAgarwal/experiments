import cv2
import numpy as np

'''
# param: i -> current y, x, radius
# param: image -> current image
# Randomly selects points on the image finds their color and returns their 
# added value
'''
def randomSelection(i, image):
    x, y, radius, total = i[1], i[0], i[2], 0
    total += image[x][y][2]
    total += image[int(x + (radius/2))][y][2]
    total += image[int(x - (radius/2))][y][2]
    total += image[x][int(y + (radius/2))][2]
    total += image[x][int(y + (radius/2))][2]
    return total
    
'''
# param: circles -> all the circles we consider
# param: image -> the image in consideration
# Traverses through all the circles and finds the minimum value
# minimum value implies that it's the closest to true black
# as true black in RGB is 0
'''
def pickBestCircle(circles, image):
    bestCircle = []
    minValue = pow(2, 30)
    for i in circles[0, :]:
        total = randomSelection(i, image) 
        if total < minValue:
            minValue = total
            bestCircle = i
    return bestCircle

'''
# param: blurredgray_image -> image that we consider to threshold
# param: imageName -> name of the particular file
# Does a threshold analysis on the file and only picks parts of the 
# image that fall under a particular 'thresh' that we define.
'''
def showThreshold(blurredgray_image, imageName):
    thresh = 21
    im_bw = cv2.threshold(blurredgray_image, thresh, 400, cv2.THRESH_BINARY)[1]
    cv2.imshow('gray_image_' + imageName, im_bw)

'''
# param: imageName -> the name of the file to consider
# Reads the image and does processing on it to determine the location
# of your eye-lid
'''
def useImage(imageName):
    # get image
    image = cv2.imread(imageName)
    cv2.imshow('main_image_' + imageName, image)
    
    # grayscale conversion
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blurredgray_image = cv2.medianBlur(gray_image, 5)
    cv2.imwrite('gray_image_' + imageName + '.png', blurredgray_image)
    
    # threshold calculation
    # showThreshold(blurredgray_image, imageName)
    
    # Hough Circles -> Finds all circles
    circles = cv2.HoughCircles(blurredgray_image, cv2.cv.CV_HOUGH_GRADIENT, 1, 20, 
                                param1 = 50, param2 = 30, minRadius = 0, maxRadius = 80)
    circles = np.uint16(np.around(circles))
    
    # Pick best circle according to our needs
    bestCircle = pickBestCircle(circles, image)
    
    # Draw the best circle on the current image
    cv2.circle(image, (bestCircle[0], bestCircle[1]), bestCircle[2], (0, 255, 0), 2)
    cv2.circle(image, (bestCircle[0], bestCircle[1]), 2, (0, 0, 255), 3)
    
    # Prints the other circles
    # [x, y, radius]
    for i in circles[0,:]:
        x, y, radius = i[0], i[1], i[2]
        cv2.circle(image, (x, y), radius, (0, 255, 0), 1) # draw the outer circle
        cv2.circle(image, (x, y), 1, (0, 0, 255), 2) # draw the center of the circle
    
    cv2.imshow('detected_circles_' + imageName, image)
    
if __name__ == "__main__":
    useImage('eye-image.jpg')
