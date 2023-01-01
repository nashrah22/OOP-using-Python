# -*- coding: utf-8 -*-
"""
Created on Wed Dec 14 19:21:59 2022

@author: user
"""

#from skin_detection import skinTraining
import numpy as np
import os
#import sys
from PIL import Image
from os.path import join

#print(skinTraining.skin_probability)

def test(image, probability,i):
    img = image
    
    width, height=img.size
    for x in range(width):
        for y in range(height):
            red,green,blue = img.getpixel((x,y))
       

            if probability[red][green][blue] < .40:
                img.putpixel((x,y),(255,255,255))
           


    img.save(f"finalimage{i}.jpg")


def readImage(path_test_image, test_image, probability):

    for i,x in enumerate(test_image):
        image = Image.open(join(path_test_image, x)).convert("RGB")

       

        test(image, probability,i)

if __name__ == "__main__":
    print(os.path.join(os.getcwd(), "testimage"))
    path_test_image = os.path.join(os.getcwd(), "testimage")
    test_image = os.listdir(path_test_image)

    probability = np.zeros((256, 256, 256))
    file = open('probability.txt', 'r')
    lines = file.readlines()

    for line in lines:
        r, g, b, prob = line.split('->')
        probability[int(r)][int(g)][int(b)] = float(prob)

    readImage(path_test_image, test_image, probability)

