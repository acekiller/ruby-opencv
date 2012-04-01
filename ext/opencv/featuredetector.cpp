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
  VALUE image, mask, keypoints;
  rb_scan_args(argc, argv, "11", &image, &mask);
  if (TYPE(image) == T_ARRAY) {
    keypoints = detect_multi(image, mask, self);
  }
  else {
    keypoints = detect_single(image, mask, self);
  }
  return keypoints;
}

VALUE
RbFeatureDetector::detect_single(VALUE _image, VALUE _mask, VALUE self)
{
  cv::FeatureDetector *ptr = value_to_featuredetector(self);
  std::vector<cv::KeyPoint> keypoints;
  cv::Mat mat(CVMAT_WITH_CHECK(_image));

  if (NIL_P(_mask)) {
    ptr->detect(mat, keypoints);
  }
  else {
    cv::Mat mask_mat(MASK(_mask));
    ptr->detect(mat, keypoints, mask_mat);
  }

  size_t size = keypoints.size();
  VALUE kp_result = rb_ary_new2(size);
  for (size_t i = 0; i < size; ++i) {
    rb_ary_push(kp_result, cKeyPoint::new_object(keypoints[i]));
  }
  return kp_result;
}

VALUE
RbFeatureDetector::detect_multi(VALUE _images, VALUE _masks, VALUE self)
{
  cv::FeatureDetector *ptr = value_to_featuredetector(self);
  int images_len = RARRAY_LEN(_images);
  VALUE* images_ptr = RARRAY_PTR(_images);

  std::vector<cv::Mat> images(images_len);
  std::vector< std::vector<cv::KeyPoint> > keypoints(images_len);
  for (int i = 0; i < images_len; ++i) {
    cv::Mat img(CVMAT_WITH_CHECK(images_ptr[i]));
    images[i] = img;
    std::vector<cv::KeyPoint> kp;
    keypoints[i] = kp;
  }

  if (NIL_P(_masks)) {
    ptr->detect(images, keypoints);
  }
  else {
    Check_Type(_masks, T_ARRAY);
    int masks_len = RARRAY_LEN(_masks);
    VALUE* masks_ptr = RARRAY_PTR(_masks);
    std::vector<cv::Mat> masks(masks_len);
    for (int i = 0; i < masks_len; ++i) {
      cv::Mat mask(CVMAT_WITH_CHECK(masks_ptr[i]));
      masks[i] = mask;
    }
    ptr->detect(images, keypoints, masks);
  }

  VALUE kp_result = rb_ary_new2(images_len);
  for (int i = 0; i < images_len; ++i) {
    size_t size = keypoints[i].size();
    VALUE kps = rb_ary_new2(images_len);
    for (size_t j = 0; j < size; ++j) {
      rb_ary_push(kps, cKeyPoint::new_object(keypoints[i][j]));
    }
    rb_ary_push(kp_result, kps);
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

