/************************************************************

   featuredetector.h -

   $Author: ser1zw $

   Copyright (C) 2012 ser1zw

************************************************************/
#ifndef RUBY_OPENCV_FEATUREDETECTOR_H
#define RUBY_OPENCV_FEATUREDETECTOR_H

#include "opencv.h"

#define __NAMESPACE_BEGIN_FEATUREDETECTOR namespace mFeatureDetector {
#define __NAMESPACE_END_FEATUREDETECTOR }

__NAMESPACE_BEGIN_OPENCV
__NAMESPACE_BEGIN_FEATUREDETECTOR

VALUE rb_module();

void define_ruby_module();

__NAMESPACE_END_FEATUREDETECTOR
__NAMESPACE_END_OPENCV

#endif // RUBY_OPENCV_FEATUREDETECTOR_H


