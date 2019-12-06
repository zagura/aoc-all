#!/usr/bin/python3

target = int(input("Give the target number: "))
print("Target: {}".format(target))
d = 1
while d*d < target:
    d += 2 

d -= 2
print("Left bottom: {}".format(d))
## distance to d corner

corner = d*d
diff = 0
while corner <= target:
    corner += (d + 1)
   

corner -= (d + 1)
#d += diff
print("Corner: {}, d value: {}".format(corner, d))
print("Distance to corner: {}".format(d-1))

# We're taking middle as the nearest point
d += 1 
distance = d 
if target - corner > d // 2:
    distance -=  (target - corner - (d // 2))
else:
    distance -=  (target - corner)

print("Calculated distance: {}".format(distance))
print('')
