import sys
import os

sys.path.append('/Users/renren/OpenCodeNLP/PCI/source');
sys.path.append('/Users/renren/OpenCodeNLP/PCI/lib');

from recommendations import critics
from calculateSimilarity import *
from recommendation import*

print sim_distance(critics,'Lisa Rose','Gene Seymour')

print sim_pearson(critics,'Lisa Rose','Gene Seymour')

print topMatches(critics,'Lisa Rose');

print getRecommendations(critics,'Lisa Rose');
