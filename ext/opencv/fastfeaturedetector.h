/************************************************************

   fastfeaturedetector.h -

   $Author: ser1zw $

   Copyright (C) 2012 ser1zw

************************************************************/
#ifndef RUBY_OPENCV_FASTFEATUREDETECTOR_H
#define RUBY_OPENCV_FASTFEATUREDETECTOR_H

#include "opencv.h"

#define __NAMESPACE_BEGIN_FASTFEATUREDETECTOR namespace cFastFeatureDetector {
#define __NAMESPACE_END_FASTFEATUREDETECTOR }

__NAMESPACE_BEGIN_OPENCV

class RbFastFeatureDetector;

__NAMESPACE_BEGIN_FASTFEATUREDETECTOR

VALUE rb_class();
void define_ruby_class();
VALUE rb_initialize(int argc, VALUE *argv, VALUE self);
VALUE rb_detect(int argc, VALUE *argv, VALUE self);

__NAMESPACE_END_FASTFEATUREDETECTOR

inline RbFastFeatureDetector* RB_FASTFEATUREDETECTOR(VALUE object);
inline cv::FastFeatureDetector* FASTFEATUREDETECTOR(VALUE object);
inline cv::FastFeatureDetector* FASTFEATUREDETECTOR_WITH_CHECK(VALUE object);

__NAMESPACE_END_OPENCV

#endif // RUBY_OPENCV_FASTFEATUREDETECTOR_H


