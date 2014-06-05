import cv2
import numpy as np

def randomSelection(i, image):
    x, y, radius, total = i[1], i[0], i[2], 0
    total += image[x][y][2]
    total += image[int(x + (radius/2))][y][2]
    total += image[int(x - (radius/2))][y][2]
    total += image[x][int(y + (radius/2))][2]
    total += image[x][int(y + (radius/2))][2]
    return total
    
def pickBestCircle(circles, image):
    bestCircle = []
    minValue = pow(2, 30)
    for i in circles[0, :]:
        total = randomSelection(i, image) 
        if total < minValue:
            minValue = total
            bestCircle = i
    return bestCircle
    
def useImage():
    # get image
    image = cv2.imread('eye-image.jpg')
    cv2.imshow('main_image', image)
    
    # grayscale conversion
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blurredgray_image = cv2.medianBlur(gray_image, 5)
    cv2.imwrite('gray_image.png', blurredgray_image)
    
    # threshold calculation
    thresh = 21
    im_bw = cv2.threshold(blurredgray_image, thresh, 400, cv2.THRESH_BINARY)[1]
    cv2.imshow('gray_image', im_bw)
    
    # Hough Circles -> Finds all circles
    circles = cv2.HoughCircles(blurredgray_image, cv2.cv.CV_HOUGH_GRADIENT, 1, 20, param1 = 50, param2 = 30, minRadius = 0, maxRadius = 80)
    circles = np.uint16(np.around(circles))
    
    # Pick best circle according to our needs
    bestCircle = pickBestCircle(circles, image)
    
    # Draw the best circle on the current image
    cv2.circle(image,(bestCircle[0],bestCircle[1]),bestCircle[2],(0,255,0),2)
    cv2.circle(image,(bestCircle[0],bestCircle[1]),2,(0,0,255),3)
    
    # Prints the other circles
    # [x, y, radius]
    for i in circles[0,:]:
        x, y, radius = i[0], i[1], i[2]
        cv2.circle(image, (x, y), radius, (0, 255, 0), 1) # draw the outer circle
        cv2.circle(image, (x, y), 1, (0, 0, 255), 2) # draw the center of the circle
        
    cv2.imshow('detected circles', image)
    
if __name__ == "__main__":
    useImage()
