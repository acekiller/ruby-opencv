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
class rbFastFeatureDetector {
  int _is_legal;
 public:
  cv::FastFeatureDetector *detector;
  
  rbFastFeatureDetector(int threshold = 1, int nonmax_suppression = 1) {
    detector = new cv::FastFeatureDetector(threshold, nonmax_suppression);
    _is_legal = 1;
  }

  ~rbFastFeatureDetector() {
    detector->~FastFeatureDetector();
  }

  int is_created_using_constructor() {
    return _is_legal;
  }

  static rbFastFeatureDetector* alloc() {
    rbFastFeatureDetector *val = ALLOC(rbFastFeatureDetector);
    val->_is_legal = 0;
    return val;
  }

  static void free(rbFastFeatureDetector* ptr) {
    ruby_xfree(ptr);
  }
};

__NAMESPACE_BEGIN_FASTFEATUREDETECTOR

VALUE rb_class();

void define_ruby_class();
VALUE rb_initialize(int argc, VALUE *argv, VALUE self);
VALUE rb_detect(int argc, VALUE *argv, VALUE self);

__NAMESPACE_END_FASTFEATUREDETECTOR

inline rbFastFeatureDetector*
RB_FASTFEATUREDETECTOR(VALUE object)
{
  rbFastFeatureDetector *ptr;
  Data_Get_Struct(object, rbFastFeatureDetector, ptr);
  return ptr;
}

inline cv::FastFeatureDetector*
FASTFEATUREDETECTOR(VALUE object)
{
  return RB_FASTFEATUREDETECTOR(object)->detector;
}

inline cv::FastFeatureDetector*
FASTFEATUREDETECTOR_WITH_CHECK(VALUE object)
{
  if (!rb_obj_is_kind_of(object, cFastFeatureDetector::rb_class()))
    raise_typeerror(object, cFastFeatureDetector::rb_class());
  return FASTFEATUREDETECTOR(object);
}

__NAMESPACE_END_OPENCV

#endif // RUBY_OPENCV_FASTFEATUREDETECTOR_H


