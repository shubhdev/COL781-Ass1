from PIL import Image
import math
res = raw_input().split()
print res
res = [int(x) for x in res]
im = Image.new("RGB",(res[0],res[1]))
pix = im.load()
for i in xrange(0,res[0]):
  for j in xrange(0,res[1]):
    c = raw_input().split()
    c = [int(math.ceil(255*float(x) - 1e-5)) for x in c]
    # if(i < 300 and j < 100):
    #   c = [255,0,0]
    # else:
    #   c = [0,0,0]
    pix[i,j] = tuple(c)
im.format = "PNG"
im.save("abc.png")