from math import sqrt
def getSim(dict1,dict2):
       # Get the list of mutually rated items
       si={}
       for item in dict1:
         if item in dict2: si[item]=1
       # Find the number of elements
       n=len(si)
       # if they are no ratings in common, return 0
       if n==0: return 0
       # Add up all the preferences
       sum1=sum([dict1[it] for it in si])
       sum2=sum([dict2[it] for it in si])
       # Sum up the squares
       sum1Sq=sum([pow(dict1[it],2) for it in si])
       sum2Sq=sum([pow(dict2[it],2) for it in si])
       # Sum up the products
       pSum=sum([dict1[it]*dict2[it] for it in si])
       # Calculate Pearson score
       num=pSum-(sum1*sum2/n)
       den=sqrt((sum1Sq-pow(sum1,2)/n)*(sum2Sq-pow(sum2,2)/n))
       if den==0: return 0
       r=num/den
       return r
       