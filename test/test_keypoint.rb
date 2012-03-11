#!/usr/bin/env ruby
# -*- mode: ruby; coding: utf-8-unix -*- 
require 'test/unit'
require 'opencv'
require File.expand_path(File.dirname(__FILE__)) + '/helper'

include OpenCV

# Tests for OpenCV::KeyPoint
class TestKeyPoint < OpenCVTestCase
  def setup
    @keypoint1 = KeyPoint.new
  end
  
  def test_initialize
    kp1 = KeyPoint.new
    assert_in_delta(0.0, kp1.pt.x, 0.001)
    assert_in_delta(0.0, kp1.pt.y, 0.001)
    assert_in_delta(0.0, kp1.size, 0.001)
    assert_in_delta(-1.0, kp1.angle, 0.001)
    assert_in_delta(0.0, kp1.response, 0.001)
    assert_equal(0, kp1.octave)
    assert_equal(-1, kp1.class_id)

    kp2 = KeyPoint.new(CvPoint2D32f.new(1.1, 2.2), 3.3, 4.4, 5.5, 6, 7)
    assert_in_delta(1.1, kp2.pt.x, 0.001)
    assert_in_delta(2.2, kp2.pt.y, 0.001)
    assert_in_delta(3.3, kp2.size, 0.001)
    assert_in_delta(4.4, kp2.angle, 0.001)
    assert_in_delta(5.5, kp2.response, 0.001)
    assert_equal(6, kp2.octave)
    assert_equal(7, kp2.class_id)

    assert_raise(TypeError) {
      KeyPoint.new(DUMMY_OBJ)
    }
    assert_raise(TypeError) {
      KeyPoint.new(CvPoint2D32f.new, DUMMY_OBJ)
    }
    assert_raise(TypeError) {
      KeyPoint.new(CvPoint2D32f.new, 0, DUMMY_OBJ)
    }
    assert_raise(TypeError) {
      KeyPoint.new(CvPoint2D32f.new, 0, 0, DUMMY_OBJ)
    }
    assert_raise(TypeError) {
      KeyPoint.new(CvPoint2D32f.new, 0, 0, 0, DUMMY_OBJ)
    }
    assert_raise(TypeError) {
      KeyPoint.new(CvPoint2D32f.new, 0, 0, 0, 0, DUMMY_OBJ)
    }
  end

  def test_pt
    assert_equal(CvPoint2D32f, @keypoint1.pt.class)
    @keypoint1.pt = CvPoint2D32f.new(1.1, 2.2)
    assert_in_delta(1.1, @keypoint1.pt.x, 0.001)
    assert_in_delta(2.2, @keypoint1.pt.y, 0.001)

    @keypoint1.pt = CvPoint2D32f.new(3.3, 4.4)
    assert_in_delta(3.3, @keypoint1.pt.x, 0.001)
    assert_in_delta(4.4, @keypoint1.pt.y, 0.001)

    @keypoint1.pt.x = 5.5
    @keypoint1.pt.y = 6.6
    assert_in_delta(5.5, @keypoint1.pt.x, 0.001)
    assert_in_delta(6.6, @keypoint1.pt.y, 0.001)

    assert_raise(TypeError) {
      @keypoint1.pt = DUMMY_OBJ
    }
  end

  def test_size
    @keypoint1.size = 1.1
    assert_in_delta(1.1, @keypoint1.size, 0.001)

    @keypoint1.size = 2.2
    assert_in_delta(2.2, @keypoint1.size, 0.001)
  end

  def test_angle
    @keypoint1.angle = 1.1
    assert_in_delta(1.1, @keypoint1.angle, 0.001)

    @keypoint1.angle = 2.2
    assert_in_delta(2.2, @keypoint1.angle, 0.001)
  end

  def test_response
    @keypoint1.response = 1.1
    assert_in_delta(1.1, @keypoint1.response, 0.001)

    @keypoint1.response = 2.2
    assert_in_delta(2.2, @keypoint1.response, 0.001)
  end

  def test_octave
    @keypoint1.octave = 1
    assert_equal(1, @keypoint1.octave)

    @keypoint1.octave = 2
    assert_equal(2, @keypoint1.octave)
  end

  def test_class_id
    @keypoint1.class_id = 1
    assert_equal(1, @keypoint1.class_id)

    @keypoint1.class_id = 2
    assert_equal(2, @keypoint1.class_id)
  end

  def test_convert
    flunk('Not implemented yet')
  end

  def test_overlap
    kp1 = KeyPoint.new(CvPoint2D32f.new(0, 0), 10)
    kp2 = KeyPoint.new(CvPoint2D32f.new(0, 0), 10)
    assert_in_delta(1.0, KeyPoint.overlap(kp1, kp2), 0.001)

    kp1 = KeyPoint.new(CvPoint2D32f.new(-100, 0), 10)
    kp2 = KeyPoint.new(CvPoint2D32f.new(100, 0), 10)
    assert_in_delta(0.0, KeyPoint.overlap(kp1, kp2), 0.001)

    kp1 = KeyPoint.new(CvPoint2D32f.new(2, 0), 10)
    kp2 = KeyPoint.new(CvPoint2D32f.new(-2, 0), 10)
    assert_in_delta(0.3375, KeyPoint.overlap(kp1, kp2), 0.001)

    assert_raise(TypeError) {
      KeyPoint.overlap(DUMMY_OBJ, kp2)
    }
    assert_raise(TypeError) {
      KeyPoint.overlap(kp1, DUMMY_OBJ)
    }
  end
end


