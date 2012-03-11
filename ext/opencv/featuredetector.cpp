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

