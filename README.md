# Larc2016

This repository contains a set of C++ and OpenCV experiments related to computer vision, image processing, and camera-based detection. The project appears to be a collection of small prototypes and test programs rather than a single finished application.

## Project purpose

The code focuses on:

- loading and displaying images
- thresholding colors in HSV format
- detecting contours and circles/ellipses
- processing live camera frames
- experimenting with object detection and tracking for robotics or vision tasks

Most of the examples use OpenCV and are designed to run on a Raspberry Pi or a Linux environment with a camera.

---

## Repository structure

- `Larc2016/` - main project folder with the OpenCV programs
  - `Dispaly.cpp` - loads an image and displays it
  - `DetectarRojo/Detect.cpp` - camera stream + HSV filtering for red detection
  - `VasosBase/circulos.cpp` - contour and ellipse detection on images
  - `Vacas/vacas.cpp` - experimental line/shape detection logic
  - `CamaravVasos/` - camera and vessel-related tests
  - `logos/` - logo/template matching experiments
  - `Test/`, `Testeos/`, `Trayectos/` - additional prototypes and experiments

---

## Requirements

- C++ compiler
- CMake
- OpenCV installed on the system
- Raspberry Pi camera libraries if using the camera examples (`raspicam/raspicam_cv.h`)

---

## Build instructions

From the project root:

```bash
cd Larc2016
cmake .
make
```

You can then run programs such as:

```bash
./DisplayImage test.jpg
```

Some folders contain their own `CMakeLists.txt` and can be built separately.

---

## Main code explanations

### 1) Image display example (`Larc2016/Dispaly.cpp`)

This is the simplest program in the project.

It:

- checks that an image path was provided
- reads the image with `imread()`
- verifies the file loaded correctly
- creates a window named `Display Image`
- shows the image until the user presses a key

Core logic:

```cpp
Mat image;
image = imread(argv[1], 1);

if (!image.data) {
    printf("No image data \n");
    return -1;
}

namedWindow("Display Image", WINDOW_AUTOSIZE);
imshow("Display Image", image);
waitKey(0);
```

This is a basic OpenCV starter program used to verify image loading and display.

### 2) Red detection / color segmentation (`Larc2016/DetectarRojo/Detect.cpp`)

This file captures frames from a Raspberry Pi camera and filters the image using HSV thresholds.

Important steps:

- opens the camera with `raspicam::RaspiCam_Cv`
- converts each frame from `BGR` to `HSV`
- creates a threshold mask with `inRange()`
- applies morphological operations (`erode` and `dilate`) to clean the mask
- shows the original camera frame and the processed thresholded version

This is useful for detecting objects like red markers or colored objects in a scene.

The key idea is:

```cpp
cvtColor(image, imgHSV, COLOR_BGR2HSV);
inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
```

The program also defines trackbars to let the user adjust HSV values interactively.

### 3) Contour and ellipse detection (`Larc2016/VasosBase/circulos.cpp`)

This file finds contours in an image and then tries to fit ellipses around them.

Flow:

- reads an image
- converts it to HSV
- uses a slider to modify the minimum value threshold
- applies `inRange()`
- finds contours with `findContours()`
- checks contour size
- fits ellipses with `fitEllipse()`
- draws the contours and ellipses on the output image

This is a classic shape detection pipeline for identifying circular or elliptical objects.

### 4) Experimental line detection (`Larc2016/Vacas/vacas.cpp`)

This file is more exploratory. It appears to use the Hough Transform to detect lines in an image and group them by angle/distance.

The code tries to:

- apply Canny edge detection
- detect lines using `HoughLinesP()`
- separate vertical and horizontal lines
- compute geometric relationships
- group nearby lines together
- estimate a center point and object structure

This is more advanced and looks like prototype logic for finding patterns or objects in a scene, possibly for robotics or industrial visual detection.

---

## Summary of the project

This codebase is not a polished application; it is a set of OpenCV experiments in various stages of completion. Most of the files are examples of:

- camera access
- color filtering
- contour and ellipse detection
- line detection
- image analysis in real time

The patterns repeat across multiple examples: read frame, convert color space, threshold the image, filter noise, find contours, and display the result.

---

## Notes

- Some files are heavily commented or partially incomplete.
- Some examples are likely educational or test code from an earlier robotics vision project.
- If you want to use this project, the most relevant starting points are:
  - `Larc2016/Dispaly.cpp`
  - `Larc2016/DetectarRojo/Detect.cpp`
  - `Larc2016/VasosBase/circulos.cpp`

---

## Suggested next steps

1. Keep only the modules you need.
2. Create a single main application for your final project.
3. Add reusable functions for image preprocessing and detection.
4. Replace hardcoded thresholds with configurable parameters or calibration logic.
5. Add a proper project README and documentation for each module.
