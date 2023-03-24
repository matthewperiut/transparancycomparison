# Transparency Depth Comparison
What this does, compares a bigger image and a smaller image at some scale. the bigger image finds it's corresponding pixel in the smaller image as it's just a scaled up version, the scaled up version has many comparisons to a single pixel in the smaller image, but ultimately results in one whole pixel coming out on top. This maintains pixel art aesthetics. It also allows subpixel movement of a scaled up pixel image on a bigger image.

The reasoning behind the depth is because it will be used for pixel art ray traced scenes. We will be able to find the depth by interpretting how far the ray has gone, and then feed that to an alpha channel.

This simple program is the basis of having fragment shaders work to generate the world for isometric 3D pixel art, but have smooth entities in the world. It allows for subpixel images by using a larger image.

Ideally you have the sprites rendered to an FBO, then pass it's texture into the larger image.
You also would have the world rendered into an FBO of smaller texture size and pass it in.

Considering both the previous fragments appropriately assign depth based on the physical world, the results should be promising, and smooth.