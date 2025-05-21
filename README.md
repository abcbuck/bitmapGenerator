# Usage

1. Customize the variables `height` and `width` and the `defineColorValueOfPixel` function.
2. Compile.
3. Run `bitmapGenerator bitmapFileName` to save your bitmap in `bitmapFileName`. Default file name is `bitmap.bmp`.

# Examples

The [default code](src/main.cpp) creates this image:

![example](https://github.com/user-attachments/assets/539047fc-c9f3-4190-bb2d-f31adf1fc790)

You may create a wallpaper-sized version of this image by setting `height` and `width` to your screen resolution.

You can extend the program's functionality to iteratively work on generated data by customizing the procedure in the main function.\
This is how I created my profile image, for example.
