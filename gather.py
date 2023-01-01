# -*- coding: utf-8 -*-
"""
Created on Wed Dec 14 18:25:37 2022

@author: user
"""

# -*- coding: utf-8 -*-
"""
Created on Wed Dec 14 18:25:37 2022

@author: user
"""
import numpy as  np
from PIL import Image
import os

def absoluteFilePaths(directory):
  filePaths = []
  for dirpath,_,filenames in os.walk(directory):
    for f in filenames:
      filePaths.append(os.path.abspath(os.path.join(dirpath, f))) 
  return filePaths



def process_images(imagePaths, maskPaths):
  global skinPixelNumber, nonskinPixelNumber
  for i in range(len(imagePaths)):
    im = Image.open(imagePaths[i])
    ms = Image.open(maskPaths[i])
    im = im.convert('RGB')
    ms = ms.convert('RGB')

    width, height = im.size

    for y in range(height):
      for x in range(width):
        red, green, blue = im.getpixel((x, y))
        maskRed, maskGreen, maskBlue = ms.getpixel((x, y))
        
        if(maskRed>250 and maskGreen>250 and maskBlue>250):
          nonskinPixelNumber[red][green][blue] += 1
         
        else:
          skinPixelNumber[red][green][blue] += 1
    print('image no: ' + str(i) + ' processed!')
    im.close()
    ms.close()
  """
    probability = np.zeros((256, 256, 256))
    file = open('probability.txt', 'r')
    lines = file.readlines()

    for line in lines:
        r, g, b, prob = line.split('->')
        probability[int(r)][int(g)][int(b)] = float(prob)
"""
def calculate_probability(skin, non_skin):
    skin_count = np.sum(skin)
    non_skin_count = np.sum(non_skin)
    skin_probability = skin/ skin_count
    non_skin_probability =non_skin / non_skin_count
    threshold = np.zeros((256, 256, 256))

    for i in range(256):
        for j in range(256):
            for k in range(256):
                if non_skin_probability[i][j][k] == 0.0 and skin_probability[i][j][k] == 0.0 :
                    threshold[i][j][k] = 0.0
                elif non_skin_probability[i][j][k] == 0.0 and skin_probability[i][j][k] != 0.0 :
                    threshold[i][j][k] = skin_probability[i][j][k]
                else:
                    threshold[i][j][k] = skin_probability[i][j][k] / non_skin_probability[i][j][k]
    #skin_probability = p * np.divide(skin, np.add(skin, non_skin))

    return threshold

def probability_file(skin_probability):
    out = open('probability.txt', 'w')
    hmm = open('value.txt', 'w')
    #out.write("Red->Green->Blue->Probability\n")

    for i in range(256):
        for j in range(256):
            for k in range(256):
                out.write(str(i)+'->'+str(j)+'->'+str(k)+'->'+str(skin_probability[i][j][k])+'\n')
                if skin_probability[i][j][k] > 0.0:
                    hmm.write(str(i) + '->' + str(j) + '->' + str(k) + '->' + str(skin_probability[i][j][k]) + '\n')

    out.close()
    hmm.close()

if __name__=='__main__':
  imagePaths = absoluteFilePaths("./data/image")
  maskPaths = absoluteFilePaths("./data/mask")

  # skinPixelNumber = [[[0 for k in range(256)] for j in range(256)] for i in range(256)]
  # nonskinPixelNumber = [[[0 for k in range(256)] for j in range(256)] for i in range(256)]
  skinPixelNumber = np.zeros((256, 256, 256), dtype=np.float64)
  nonskinPixelNumber = np.zeros((256, 256, 256), dtype=np.float64)

  process_images(imagePaths, maskPaths)
  skin_probability = calculate_probability(skinPixelNumber, nonskinPixelNumber)
  probability_file(skin_probability)
