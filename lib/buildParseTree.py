import sys
import os
import random

sys.path.append('/Users/renren/OpenCodeNLP/PCI/lib');
sys.path.append('/Users/renren/OpenCodeNLP/PCI/source')

from getWordCount import *
from getSim import *
from buildParseTree import *

def buildParseTree(k=4):
      # Determine the minimum and maximum values for each point
      dictData = {}
      for i in range(20):
            fileName = "blogData"
            fileName += '%d' %i
            fileName += ".txt"
            dictData[fileName] = getWordCount(fileName);
      ranges = {};
      for fileKey in dictData:
              for word in dictData[fileKey]:
                  if ranges.has_key(word):
                      if ranges[word] < dictData[fileKey][word]:
                          ranges[word] = 8 * dictData[fileKey][word]
                  else:
                      ranges[word] = 8 * dictData[fileKey][word]
      # Create k randomly placed centroids
      clusters = {}
      for i in range(k):
          tmpDict = {}
          keyWord = "keyTemp" + '%d' %i
          for word in ranges:
              tmpDict[word] = random.random()*(ranges[word])
          clusters[keyWord] = tmpDict;
      # print clusters['keyTemp0']
      lastmatches=None
      for t in range(100):
            bestmatches = {}
            for i in range(k):
                tmpDict = {}
                keyWord = "keyTemp" + '%d' %i
                bestmatches[keyWord] = {};
            for dictTmp in dictData:
                  bestmatch = ""
                  if len(dictTmp) == 0 : continue;
                  for i in range(k):
                      keyWord = "keyTemp" + '%d' %i
                      d = getSim(clusters[keyWord],dictData[dictTmp])
                      if len(bestmatch) != 0:
                          if d < getSim(clusters[bestmatch],dictData[dictTmp]): 
                                bestmatch = keyWord
                      else  :
                            bestmatch = keyWord;
                  bestmatches[bestmatch][dictTmp]=dictData[dictTmp]
            clusterTmp = {}
            for i in range(k):
                keyWord = "keyTemp" + '%d' %i
                avgs= {}
                if len(bestmatches[keyWord])>0:
                    for item in bestmatches[keyWord]:
                        for word in bestmatches[keyWord][item]:
                            if avgs.has_key(word):
                                avgs[word] += bestmatches[keyWord][item][word]
                            else :
                                avgs[word] = bestmatches[keyWord][item][word]
                for word in avgs:
                    avgs[word] /= len(bestmatches[keyWord])
                clusterTmp[keyWord]=avgs
      return bestmatches
