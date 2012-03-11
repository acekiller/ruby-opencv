/************************************************************

   keypoint.h -

   $Author: ser1zw $

   Copyright (C) 2012 ser1zw

************************************************************/
#ifndef RUBY_OPENCV_KEYPOINT_H
#define RUBY_OPENCV_KEYPOINT_H

#include "opencv.h"

#define __NAMESPACE_BEGIN_KEYPOINT namespace cKeyPoint {
#define __NAMESPACE_END_KEYPOINT }

__NAMESPACE_BEGIN_OPENCV

class rbKeyPoint {
 public:
  cv::KeyPoint keypoint;
  VALUE point;
  void set_point(VALUE pt);
  void set_point(float x, float y);
};

__NAMESPACE_BEGIN_KEYPOINT

VALUE rb_class();

void define_ruby_class();

VALUE rb_allocate(VALUE klass);
VALUE rb_initialize(int argc, VALUE *argv, VALUE self);
VALUE rb_get_pt(VALUE self);
VALUE rb_set_pt(VALUE self, VALUE pt);
VALUE rb_get_size(VALUE self);
VALUE rb_set_size(VALUE self, VALUE size);
VALUE rb_get_angle(VALUE self);
VALUE rb_set_angle(VALUE self, VALUE angle);
VALUE rb_get_response(VALUE self);
VALUE rb_set_response(VALUE self, VALUE response);
VALUE rb_get_octave(VALUE self);
VALUE rb_set_octave(VALUE self, VALUE octave);
VALUE rb_get_class_id(VALUE self);
VALUE rb_set_class_id(VALUE self, VALUE class_id);

VALUE rb_overlap(VALUE self, VALUE kp1, VALUE kp2);

VALUE new_object(cv::KeyPoint &keypoint);

__NAMESPACE_END_KEYPOINT

inline rbKeyPoint*
RB_KEYPOINT(VALUE object)
{
  rbKeyPoint *ptr;
  Data_Get_Struct(object, rbKeyPoint, ptr);  
  return ptr;
}

inline cv::KeyPoint*
KEYPOINT(VALUE object)
{
  // cv::KeyPoint *ptr;
  // Data_Get_Struct(object, cv::KeyPoint, ptr);
  rbKeyPoint *ptr;
  Data_Get_Struct(object, rbKeyPoint, ptr);  
  return &(ptr->keypoint);
}

inline cv::KeyPoint*
KEYPOINT_WITH_CHECK(VALUE object)
{
  if (!rb_obj_is_kind_of(object, cKeyPoint::rb_class()))
    raise_typeerror(object, cKeyPoint::rb_class());
  return KEYPOINT(object);
}

__NAMESPACE_END_OPENCV

#endif // RUBY_OPENCV_KEYPOINT_H
