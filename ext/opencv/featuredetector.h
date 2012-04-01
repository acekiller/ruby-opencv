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

class RbFeatureDetector {
  int _is_legal;
 public:
  cv::FeatureDetector *detector;
  
  RbFeatureDetector() {
    _is_legal = 1;
  }

  ~RbFeatureDetector() {
    detector->~FeatureDetector();
  }

  int is_created_using_constructor() {
    return _is_legal;
  }

  static void featuredetector_free(RbFeatureDetector *ptr);
  VALUE allocate(VALUE klass);
  VALUE detect(int argc, VALUE *argv, VALUE self);
  VALUE detect_single(VALUE _images, VALUE _masks, VALUE self);
  VALUE detect_multi(VALUE _images, VALUE _masks, VALUE self);

 private:
  virtual size_t sizeof_class() = 0; // -> return sizeof(DerivedClass);
  virtual cv::FeatureDetector* value_to_featuredetector(VALUE object) = 0;
};

__NAMESPACE_BEGIN_FEATUREDETECTOR

VALUE rb_module();
void define_ruby_module();

__NAMESPACE_END_FEATUREDETECTOR
__NAMESPACE_END_OPENCV

#endif // RUBY_OPENCV_FEATUREDETECTOR_H


