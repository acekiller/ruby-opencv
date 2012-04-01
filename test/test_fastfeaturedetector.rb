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
    assert_in_delta(3291, kp1.size, 3291 * 0.1)

    kp1 = @detector1.detect(mat, mask)
    assert_equal(Array, kp1.class)
    kp1.each {|kp|
      assert_equal(KeyPoint, kp.class)
    }
    assert_in_delta(1572, kp1.size, 1572 * 0.1)


    kp2 = @detector2.detect(mat)
    assert_equal(Array, kp2.class)
    kp2.each {|kp|
      assert_equal(KeyPoint, kp.class)
    }
    assert_in_delta(30, kp2.size, 30 * 0.1)

    kp2 = @detector2.detect(mat, mask)
    assert_equal(Array, kp2.class)
    kp2.each {|kp|
      assert_equal(KeyPoint, kp.class)
    }
    assert_in_delta(8, kp2.size, (8 * 0.1).ceil)
    

    kp3 = @detector3.detect(mat)
    assert_equal(Array, kp3.class)
    kp3.each {|kp|
      assert_equal(KeyPoint, kp.class)
    }
    assert_in_delta(55, kp3.size, 55 * 0.1)

    kp3 = @detector3.detect(mat, mask)
    assert_equal(Array, kp3.class)
    kp3.each {|kp|
      assert_equal(KeyPoint, kp.class)
    }
    assert_in_delta(13, kp3.size, 13 * 0.1)

    assert_raise(TypeError) {
      @detector1.detect(DUMMY_OBJ)
    }
    assert_raise(TypeError) {
      @detector1.detect(mat, DUMMY_OBJ)
    }
  end

  def test_detect_multi
    filenames = [FILENAME_LENA256x256, FILENAME_FRUITS]
    images = filenames.map { |fn| CvMat.load(fn) }
    masks = images.map { |img|
      mask = img.BGR2GRAY.clear
      (img.rows / 2).times { |j|
        img.cols.times { |i|
          mask[j, i] = CvScalar.new(1, 1, 1, 1)
        }
      }
      mask
    }

    # threshold = 1, nonmax_suppression = true (default)
    kp1 = @detector1.detect(images)
    assert_equal(Array, kp1.class)
    assert_equal(2, kp1.size)
    kp1.each {|kp|
      assert_equal(Array, kp.class)
    }
    assert_in_delta(3291, kp1[0].size, 3291 * 0.1)
    assert_in_delta(11798, kp1[1].size, 11798 * 0.1)

    kp1 = @detector1.detect(images, masks)
    assert_equal(Array, kp1.class)
    assert_equal(2, kp1.size)
    kp1.each {|kp|
      assert_equal(Array, kp.class)
    }
    assert_in_delta(1572, kp1[0].size, 1572 * 0.1)
    assert_in_delta(5789, kp1[1].size, 5789 * 0.1)


    # threshold = 70, nonmax_suppression = true
    kp2 = @detector2.detect(images)
    assert_equal(Array, kp2.class)
    assert_equal(2, kp2.size)
    kp2.each {|kp|
      assert_equal(Array, kp.class)
    }
    assert_in_delta(30, kp2[0].size, 30 * 0.1)
    assert_in_delta(170, kp2[1].size, 170 * 0.1)

    kp2 = @detector2.detect(images, masks)
    assert_equal(Array, kp2.class)
    kp2.each {|kp|
      assert_equal(Array, kp.class)
    }
    assert_in_delta(8, kp2[0].size, (8 * 0.1).ceil)
    assert_in_delta(48, kp2[1].size, 48 * 0.1)


    # threshold = 70, nonmax_suppression = false
    kp3 = @detector3.detect(images)
    assert_equal(Array, kp3.class)
    assert_equal(2, kp3.size)
    kp3.each {|kp|
      assert_equal(Array, kp.class)
    }
    assert_in_delta(55, kp3[0].size, 55 * 0.1)
    assert_in_delta(416, kp3[1].size, 416 * 0.1)

    kp3 = @detector3.detect(images, masks)
    assert_equal(Array, kp3.class)
    kp3.each {|kp|
      assert_equal(Array, kp.class)
    }
    assert_in_delta(13, kp3[0].size, 13 * 0.1)
    assert_in_delta(118, kp3[1].size, 118 * 0.1)


    # type error
    assert_raise(TypeError) {
      @detector1.detect([DUMMY_OBJ])
    }
    assert_raise(TypeError) {
      @detector1.detect(images, [DUMMY_OBJ])
    }
  end
end

