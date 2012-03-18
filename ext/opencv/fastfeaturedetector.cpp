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
__NAMESPACE_BEGIN_FASTFEATUREDETECTOR

VALUE rb_klass;
    
VALUE
rb_class()
{
  return rb_klass;
}

void
fastfeaturedetector_free(rbFastFeatureDetector *ptr)
{
  if (ptr) {
    if (ptr->is_created_using_constructor()) {
      delete ptr;
    }
    else {
      rbFastFeatureDetector::free(ptr);
    }
  }
}

VALUE
rb_allocate(VALUE klass)
{
  rbFastFeatureDetector *sval = rbFastFeatureDetector::alloc();
  return Data_Wrap_Struct(rb_klass, NULL, fastfeaturedetector_free, sval);
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
    rbFastFeatureDetector *ptr = RB_FASTFEATUREDETECTOR(self);
    new(ptr) rbFastFeatureDetector(IF_INT(threshold, 1), IF_BOOL(nonmax_suppression, 1, 0, 1));
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return self;
}

VALUE
rb_detect(int argc, VALUE *argv, VALUE self)
{
  VALUE image, mask;
  rb_scan_args(argc, argv, "11", &image, &mask);
  cv::FeatureDetector *ptr = FASTFEATUREDETECTOR(self);
  std::vector<cv::KeyPoint> keypoints;
  cv::Mat mat(CVMAT_WITH_CHECK(image)); // TODO: IplImage is OK?
  if (NIL_P(mask)) {
    ptr->detect(mat, keypoints);
  }
  else {
    cv::Mat mask_mat(MASK(mask));
    ptr->detect(mat, keypoints, mask_mat);
  }

  size_t size = keypoints.size();
  VALUE kp_result = rb_ary_new2(size);
  for (size_t i = 0; i < size; ++i) {
    rb_ary_push(kp_result, cKeyPoint::new_object(keypoints[i]));
  }
  return kp_result;
}

__NAMESPACE_END_FASTFEATUREDETECTOR
__NAMESPACE_END_OPENCV

