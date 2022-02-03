# arnold-cat
A simple project made in OpenCV to showcase Arnold's Cat Map.
Please make sure that you have OpenCV installed to run this project.

# Chaos!
The one way to know how many iterations it will take for the image to return to its original state without brute forcing through it is taking the LCM of all pixels' path size (the number of iteration they take to return to their original position).
However, there's also no set formula to determine that, and so the nature of this mapping still resides in chaos.

# Image Cryptography
Due to its chaotic nature, this algorithm can be used to encrypt images: it pretty much works like a safe, where you need to follow a specific set of combinations to decrypt the image.
Breaking the original image by brute force requires reconstituting it as many times as there are pixel combinations.

# Running
`make build` compiles the code;  
`make run` runs the generated executable;  
`make all` combines both of the above.
