# Usage

1. Customize the variables `height` and `width` (in pixels) and the `defineColorValueOfPixel` function by specifying [RGB](https://en.wikipedia.org/wiki/RGB_color_model) values (from 0 to 255) for each pixel.
2. Compile.
3. Run `bitmapGenerator bitmapFileName` to save your bitmap in `bitmapFileName`. Default file name is `bitmap.bmp`.
4. If you need your image in a file format other than 24-bit .bmp, open the file in a graphics editor of your choice (e.g. Microsoft Paint) and save it in the desired file format.

# Examples

The [default code](src/main.cpp) creates this image:

![example](https://github.com/user-attachments/assets/5c7fe666-28b9-48cc-be33-3bde9f60268c)

You may create a wallpaper-sized version of this image by setting `height` and `width` to your screen resolution.

You can extend the program's functionality to iteratively work on generated data by customizing the procedure in the main function.\
This is how I created my profile image, for example.
