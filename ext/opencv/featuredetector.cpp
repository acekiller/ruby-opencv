/************************************************************

   featuredetector.cpp -

   $Author: ser1zw $

   Copyright (C) 2012 ser1zw

************************************************************/
#include "featuredetector.h"
/*
 * Document-class: OpenCV::FeatureDetector
 *
 * Feature detector
 */
__NAMESPACE_BEGIN_OPENCV

void
RbFeatureDetector::featuredetector_free(RbFeatureDetector *ptr)
{
  if (ptr) {
    if (ptr->is_created_using_constructor()) {
      delete ptr;
    }
    else {
      ruby_xfree(ptr);
    }
  }
}

VALUE
RbFeatureDetector::allocate(VALUE klass)
{
  RbFeatureDetector *sval = (RbFeatureDetector*)ruby_xmalloc(sizeof_class());
  sval->_is_legal = 0;
  return Data_Wrap_Struct(klass, NULL, &featuredetector_free, sval);
}

VALUE
RbFeatureDetector::detect(int argc, VALUE *argv, VALUE self)
{
  VALUE image, mask;
  rb_scan_args(argc, argv, "11", &image, &mask);
  cv::FeatureDetector *ptr = value_to_featuredetector(self);
  std::vector<cv::KeyPoint> keypoints;
  cv::Mat mat(CVMAT_WITH_CHECK(image));

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

__NAMESPACE_BEGIN_FEATUREDETECTOR

VALUE module;
    
VALUE
rb_module()
{
  return module;
}

void
define_ruby_module()
{
  if (module)
    return;
  /* 
   * opencv = rb_define_module("OpenCV");
   *
   * note: this comment is used by rdoc.
   */
  VALUE opencv = rb_module_opencv();
  module = rb_define_module_under(opencv, "FeatureDetector");
}

__NAMESPACE_END_FEATUREDETECTOR
__NAMESPACE_END_OPENCV

