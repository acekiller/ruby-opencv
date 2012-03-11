/************************************************************

   keypoint.cpp -

   $Author: ser1zw $

   Copyright (C) 2012 ser1zw

************************************************************/
#include "keypoint.h"
/*
 * Document-class: OpenCV::KeyPoint
 */
__NAMESPACE_BEGIN_OPENCV

void
rbKeyPoint::set_point(VALUE pt)
{
  CvPoint2D32f pt2d32f = VALUE_TO_CVPOINT2D32F(pt);
  keypoint.pt.x = pt2d32f.x;
  keypoint.pt.y = pt2d32f.y;
  point = pt;
}

void
rbKeyPoint::set_point(float x, float y)
{
  keypoint.pt.x = x;
  keypoint.pt.y = y;
  CvPoint2D32f *ptr = CVPOINT2D32F(point);
  ptr->x = x;
  ptr->y = y;
}

__NAMESPACE_BEGIN_KEYPOINT

VALUE rb_klass;

VALUE
rb_class()
{
  return rb_klass;
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
  rb_klass = rb_define_class_under(opencv, "KeyPoint", rb_cObject);
  rb_define_alloc_func(rb_klass, rb_allocate);
  rb_define_private_method(rb_klass, "initialize", RUBY_METHOD_FUNC(rb_initialize), -1);
  rb_define_singleton_method(rb_klass, "overlap", RUBY_METHOD_FUNC(rb_overlap), 2);

  rb_define_method(rb_klass, "pt", RUBY_METHOD_FUNC(rb_get_pt), 0);
  rb_define_method(rb_klass, "pt=", RUBY_METHOD_FUNC(rb_set_pt), 1);
  rb_define_method(rb_klass, "size", RUBY_METHOD_FUNC(rb_get_size), 0);
  rb_define_method(rb_klass, "size=", RUBY_METHOD_FUNC(rb_set_size), 1);
  rb_define_method(rb_klass, "angle", RUBY_METHOD_FUNC(rb_get_angle), 0);
  rb_define_method(rb_klass, "angle=", RUBY_METHOD_FUNC(rb_set_angle), 1);
  rb_define_method(rb_klass, "octave", RUBY_METHOD_FUNC(rb_get_octave), 0);
  rb_define_method(rb_klass, "octave=", RUBY_METHOD_FUNC(rb_set_octave), 1);
  rb_define_method(rb_klass, "response", RUBY_METHOD_FUNC(rb_get_response), 0);
  rb_define_method(rb_klass, "response=", RUBY_METHOD_FUNC(rb_set_response), 1);
  rb_define_method(rb_klass, "class_id", RUBY_METHOD_FUNC(rb_get_class_id), 0);
  rb_define_method(rb_klass, "class_id=", RUBY_METHOD_FUNC(rb_set_class_id), 1);
}

void
mark_rbkeypoint(void* ptr)
{
  if (ptr) {
    VALUE pt = ((rbKeyPoint*)ptr)->point;
    rb_gc_mark(pt);
  }
}

VALUE
rb_allocate(VALUE klass)
{
  rbKeyPoint *keypoint;
  VALUE self = Data_Make_Struct(klass, rbKeyPoint, mark_rbkeypoint, -1, keypoint);
  RB_KEYPOINT(self)->point = cCvPoint2D32f::new_object(cvPoint2D32f(0, 0));
  return self;
}

/* 
 * call-seq:
 *   KeyPoint.new([pt = CvPoint2D32f(0,0), size = 0, angle = -1, response = 0, octave = 0, class_id = -1]) -> keypoint
 *
 * Create KeyPoint
 *
 */
VALUE
rb_initialize(int argc, VALUE *argv, VALUE self)
{
  VALUE pt, size, angle, response, octave, class_id;
  rb_scan_args(argc, argv, "06", &pt, &size, &angle, &response, &octave, &class_id);

  cv::KeyPoint *self_ptr = KEYPOINT(self);
  rbKeyPoint *ptr = RB_KEYPOINT(self);
  if (NIL_P(pt)) {
    ptr->set_point(0.0, 0.0);
  }
  else {
    ptr->set_point(pt);
  }
  self_ptr->size = NIL_P(size) ? 0.0 : (float)NUM2DBL(size);
  self_ptr->angle = NIL_P(angle) ? -1.0 : (float)NUM2DBL(angle);
  self_ptr->response = NIL_P(response) ? 0.0 : (float)NUM2DBL(response);
  self_ptr->octave = NIL_P(octave) ? 0 : NUM2INT(octave);
  self_ptr->class_id = NIL_P(class_id) ? -1 : NUM2INT(class_id);

  return self;
}

VALUE
rb_get_pt(VALUE self)
{
  return RB_KEYPOINT(self)->point;
}

VALUE
rb_set_pt(VALUE self, VALUE pt)
{
  rbKeyPoint *self_ptr = RB_KEYPOINT(self);
  self_ptr->set_point(pt);
  return self;
}

VALUE
rb_get_size(VALUE self)
{
  return DBL2NUM(KEYPOINT(self)->size);
}

VALUE
rb_set_size(VALUE self, VALUE size)
{
  KEYPOINT(self)->size = (float)NUM2DBL(size);
  return self;
}

VALUE
rb_get_angle(VALUE self)
{
  return DBL2NUM(KEYPOINT(self)->angle);
}

VALUE
rb_set_angle(VALUE self, VALUE angle)
{
  KEYPOINT(self)->angle = (float)NUM2DBL(angle);
  return self;
}

VALUE
rb_get_response(VALUE self)
{
  return DBL2NUM(KEYPOINT(self)->response);
}

VALUE
rb_set_response(VALUE self, VALUE response)
{
  KEYPOINT(self)->response = (float)NUM2DBL(response);
  return self;
}

VALUE
rb_get_octave(VALUE self)
{
  return INT2NUM(KEYPOINT(self)->octave);
}

VALUE
rb_set_octave(VALUE self, VALUE octave)
{
  KEYPOINT(self)->octave = (float)NUM2INT(octave);
  return self;
}

VALUE
rb_get_class_id(VALUE self)
{
  return INT2NUM(KEYPOINT(self)->class_id);
}

VALUE
rb_set_class_id(VALUE self, VALUE class_id)
{
  KEYPOINT(self)->class_id = (float)NUM2INT(class_id);
  return self;
}

VALUE
rb_overlap(VALUE self, VALUE kp1, VALUE kp2)
{
  cv::KeyPoint *kp1_ptr = KEYPOINT_WITH_CHECK(kp1);
  cv::KeyPoint *kp2_ptr = KEYPOINT_WITH_CHECK(kp2);
  return DBL2NUM((double)cv::KeyPoint::overlap(*kp1_ptr, *kp2_ptr));
}

VALUE
new_object(cv::KeyPoint &keypoint)
{
  VALUE object = rb_allocate(rb_klass);
  cv::KeyPoint *obj_ptr = KEYPOINT(object);
  RB_KEYPOINT(object)->set_point(keypoint.pt.x, keypoint.pt.y);
  obj_ptr->size = keypoint.size;
  obj_ptr->angle = keypoint.angle;
  obj_ptr->response = keypoint.response;
  obj_ptr->octave = keypoint.octave;
  obj_ptr->class_id = keypoint.class_id;

  return object;
}

__NAMESPACE_END_KEYPOINT
__NAMESPACE_END_OPENCV
