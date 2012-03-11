#!/usr/bin/env ruby
# -*- mode: ruby; coding: utf-8-unix -*- 
require 'test/unit'
require 'opencv'
require File.expand_path(File.dirname(__FILE__)) + '/helper'

include OpenCV

# Tests for OpenCV::FastFeatureDetector
class TestFastFeatureDetector < OpenCVTestCase
  def setup
    @detector1 = FastFeatureDetector.new
    @detector2 = FastFeatureDetector.new(70)
    @detector3 = FastFeatureDetector.new(70, false)
  end
  
  def test_initialize
    detector1 = FastFeatureDetector.new
    detector2 = FastFeatureDetector.new(10)
    detector3 = FastFeatureDetector.new(10, false)
    
    assert_raise(TypeError) {
      FastFeatureDetector.new(DUMMY_OBJ)
    }
    FastFeatureDetector.new(10, DUMMY_OBJ) # No error
  end

  def test_detect
    mat = CvMat.load(FILENAME_LENA256x256)
    mask = CvMat.new(mat.rows, mat.cols, :cv8u, 1).clear
    (mat.rows / 2).times { |j|
      mat.cols.times { |i|
        mask[j, i] = CvScalar.new(1, 1, 1, 1)
      }
    }
    
    kp1 = @detector1.detect(mat)
    assert_equal(Array, kp1.class)
    kp1.each {|kp|
      assert_equal(KeyPoint, kp.class)
    }
    assert_equal(3291, kp1.size)

    kp1 = @detector1.detect(mat, mask)
    assert_equal(Array, kp1.class)
    kp1.each {|kp|
      assert_equal(KeyPoint, kp.class)
    }
    assert_equal(1572, kp1.size)


    kp2 = @detector2.detect(mat)
    assert_equal(Array, kp2.class)
    kp2.each {|kp|
      assert_equal(KeyPoint, kp.class)
    }
    assert_equal(30, kp2.size)

    kp2 = @detector2.detect(mat, mask)
    assert_equal(Array, kp2.class)
    kp2.each {|kp|
      assert_equal(KeyPoint, kp.class)
    }
    assert_equal(8, kp2.size)


    kp3 = @detector3.detect(mat)
    assert_equal(Array, kp3.class)
    kp3.each {|kp|
      assert_equal(KeyPoint, kp.class)
    }
    assert_equal(55, kp3.size)

    kp3 = @detector3.detect(mat, mask)
    assert_equal(Array, kp3.class)
    kp3.each {|kp|
      assert_equal(KeyPoint, kp.class)
    }
    assert_equal(13, kp3.size)

    assert_raise(TypeError) {
      @detector1.detect(DUMMY_OBJ)
    }
    assert_raise(TypeError) {
      @detector1.detect(mat, DUMMY_OBJ)
    }
  end
end



