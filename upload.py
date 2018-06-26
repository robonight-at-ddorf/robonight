Import('env')
from base64 import b64decode

#
# Dump build environment (for debug)
 #print env.Dump()
#
print("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH")
env.Replace(UPLOADHEXCMD='echo ' + str(ARGUMENTS))

# uncomment line below to see environment variables
print(ARGUMENTS)
