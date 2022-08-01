# Image Feature Extraction: Traditional and Deep Learning Techniques
+ Brief write up focused on giving an over-view of the traditional and deep learning techniques for feature extraction.
  + 所写的重点是概述用于特征提取的传统方法和深度学习方法的
1. What are features?
   1. Features are parts or patterns of an object in an image that help to identify it. 
   2. Traditional Computer Vision techniques for feature detection include:
      1. **Harris Corner Detection** : Uses a Gaussian window function to detect corners.
      2. **Shi-Tomasi Corner Detector** : The authors modified the scoring function used in Harris Corner Detection to achieve a better corner detection technique.
      3. **Scale-Invariant Feature Transform(SIFT)** : This technique is scale invariant unlike the previous two.
      4. **Speeded-Up Robust Features(SURF)** : This is faster version of SIFT as the name says.
      5. **Features from Accelerated Segment Test(FAST)** : This is a much more faster corner detection technique compared to SURF.
      6. **Binary Robust Independent Elementary Features(BRIEF)** : This is only a feature descriptor that can be used with any other feature detector. This technique reduces the memory usage by converting descriptors in floating point numbers to binary strings.
      7. **Oriented FAST and Rotated BRIEF(ORB)** : SIEF and SURF are patented and this algorithm from OpenCV labs is a free alternative to them, that uses FAST keypoint detector and BRIEF descriptor.
   3. Deep Learning feature extraction:
      1. **SuperPoint: Self-Supervised Interest Point Detection and Description** : The authors suggest a fully convolutional neural network that computes SIFT like interest point locations and descriptors in a single forward pass. It uses an VGG-style encode for extracting features and then two decoders, one for point detection and the other for point description.
      2. **D2-Net: A Trainable CNN for Joint Description and Detection of Local Features** : The authors suggest a single convolutional neural network that is both a dense feature descriptor and a feature detector.
      3. **LF-Net: Learning Local Features from Images** : The authors suggest using a sparse-matching deep architecture and use an end-to-end training approach on image pairs having relative pose and depth maps. They run their detector on the first image, find the maxima and then optimize the weights so that when run on the second image, produces a clean response map with sharp maxima at the right locations.
      4. **Image Feature Matching Based on Deep Learning** : They adopt a deep Convolutional neural network model, which attention on image parch, in image feature  points matching.
      5. **Deep Graphical Feature Learning for the Feature Matching Problem** : They suggest using a graph neural network to transform coordinates of feature points into local features, which would then make it easy to use a simple inference algorithm for feature matching.