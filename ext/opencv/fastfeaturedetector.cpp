/************************************************************

   fastfeaturedetector.cpp -

   $Author: ser1zw $

   Copyright (C) 2012 ser1zw

************************************************************/
#include "fastfeaturedetector.h"
/*
 * Document-class: OpenCV::FastFeatureDetector
 *
 * Feature detector
 */
__NAMESPACE_BEGIN_OPENCV

class RbFastFeatureDetector : public RbFeatureDetector {
public:
  RbFastFeatureDetector(int threshold = 1, int nonmax_suppression = 1) {
    detector = new cv::FastFeatureDetector(threshold, nonmax_suppression);
  }

  size_t sizeof_class() {
    return sizeof(RbFastFeatureDetector);
  }

  cv::FeatureDetector* value_to_featuredetector(VALUE object);
};

cv::FeatureDetector*
RbFastFeatureDetector::value_to_featuredetector(VALUE object)
{
  RbFastFeatureDetector *ptr;
  Data_Get_Struct(object, RbFastFeatureDetector, ptr);
  return dynamic_cast<cv::FastFeatureDetector*> (ptr->detector);
}

inline RbFastFeatureDetector*
RB_FASTFEATUREDETECTOR(VALUE object)
{
  RbFastFeatureDetector *ptr;
  Data_Get_Struct(object, RbFastFeatureDetector, ptr);
  return ptr;
}

inline cv::FastFeatureDetector*
FASTFEATUREDETECTOR(VALUE object)
{
  return dynamic_cast<cv::FastFeatureDetector*> (RB_FASTFEATUREDETECTOR(object)->detector);
}

inline cv::FastFeatureDetector*
FASTFEATUREDETECTOR_WITH_CHECK(VALUE object)
{
  if (!rb_obj_is_kind_of(object, cFastFeatureDetector::rb_class()))
    raise_typeerror(object, cFastFeatureDetector::rb_class());
  return FASTFEATUREDETECTOR(object);
}

__NAMESPACE_BEGIN_FASTFEATUREDETECTOR

RbFastFeatureDetector *rbFastFeatureDetector;
VALUE rb_klass;

VALUE
rb_class()
{
  return rb_klass;
}

VALUE
rb_allocate(VALUE klass)
{
  return rbFastFeatureDetector->allocate(klass);
}

void
define_ruby_class()
{
  if (rb_klass)
    return;
  /* 
   * opencv = rb_define_module("OpenCV");
   *
   * note: this comment is used by rdoc.
   */
  rbFastFeatureDetector = new RbFastFeatureDetector();
  VALUE opencv = rb_module_opencv();
  // VALUE featuredetector = mFeatureDetector::rb_module();
  // rb_include_module(rb_klass, featuredetector);
  rb_klass = rb_define_class_under(opencv, "FastFeatureDetector", rb_cObject);
  rb_define_alloc_func(rb_klass, rb_allocate);
  rb_define_private_method(rb_klass, "initialize", RUBY_METHOD_FUNC(rb_initialize), -1);
  rb_define_method(rb_klass, "detect", RUBY_METHOD_FUNC(rb_detect), -1);
}

/* 
 * call-seq:
 *   FastFeatureDetector.new([threshold = 1, nonmax_suppression = true])
 *
 * Create FastFeatureDetector
 *
 */
VALUE
rb_initialize(int argc, VALUE *argv, VALUE self)
{
  VALUE threshold, nonmax_suppression;
  rb_scan_args(argc, argv, "02", &threshold, &nonmax_suppression);
  try {
    RbFastFeatureDetector *ptr = RB_FASTFEATUREDETECTOR(self);
    new(ptr) RbFastFeatureDetector(IF_INT(threshold, 1), IF_BOOL(nonmax_suppression, 1, 0, 1));
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return self;
}

VALUE
rb_detect(int argc, VALUE *argv, VALUE self)
{
  return rbFastFeatureDetector->detect(argc, argv, self);
}

__NAMESPACE_END_FASTFEATUREDETECTOR
__NAMESPACE_END_OPENCV

