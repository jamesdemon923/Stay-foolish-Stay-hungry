def Score(x):
     print("Before: "+Rating)
     return(str(int(Rating) + int(x)))

x = input ("Additional score: ")
Rating = input("Original score: ")
Z = Score(x)
print("After: "+Z)