/*
 * File:        SIDL_int_IOR.h
 * Copyright:   (c) 2001-2002 The Regents of the University of California
 * Release:     $Name$
 * Revision:    @(#) $Revision$
 * Date:        $Date$
 * Description: int array declarations and definitions
 * AUTOMATICALLY GENERATED BY createarrays.py
 *
 * Copyright (c) 2000-2001, The Regents of the University of Calfornia.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by the Components Team <components@llnl.gov>
 * UCRL-CODE-2002-054
 * All rights reserved.
 * 
 * This file is part of Babel. For more information, see
 * http://www.llnl.gov/CASC/components/. Please read the COPYRIGHT file
 * for Our Notice and the LICENSE file for the GNU Lesser General Public
 * License.
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License (as published by
 * the Free Software Foundation) version 2.1 dated February 1999.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the IMPLIED WARRANTY OF
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the terms and
 * conditions of the GNU Lesser General Public License for more details.
 * 
 * You should have recieved a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef included_SIDL_int_IOR_h
#define included_SIDL_int_IOR_h

#ifndef included_SIDLType_h
#include "SIDLType.h"
#endif

#ifndef included_SIDLArray_h
#include "SIDLArray.h"
#endif


/* forward declaration of struct SIDL_int__array */
struct SIDL_int__array;

/**
 * The virtual function table for the multi-dimensional arrays for
 * SIDL int.
 */
struct SIDL_int__vtable {
  /*
   * This function should release resources associates with the array
   * passed in.  It is called when the reference count goes to zero.
   */
  void (*d_destroy)(struct SIDL_int__array *);

  /*
   * If this array controls its own data (i.e. owns the memory), this
   * can simply increment the reference count of the argument and
   * return it.  If the data is borrowed (e.g. a borrowed array), this
   * should make a new array of the same size and copy data from the
   * passed in array to the new array.
   */
  struct SIDL_int__array *(*d_smartcopy)(struct SIDL_int__array *);
};

/**
 * The data structure for multi-dimensional arrays for SIDL int.
 * The client may access this with the functions below or using
 * the macros in the header file SIDLArray.h.
 */
struct SIDL_int__array {
  int32_t *d_firstElement;
  int32_t       *d_lower;
  int32_t       *d_upper;
  int32_t       *d_stride;
  int32_t        d_dimen;
  int32_t        d_refcount;
  const struct SIDL_int__vtable *d_vtable;
};


#ifdef __cplusplus
extern "C" { /*}*/
#endif

/**
 * Create a dense int array of the given dimension with specified
 * index bounds in column-major order.  This array owns and manages its data.
 * This function does not initialize the contents of the array.
 */
struct SIDL_int__array *
SIDL_int__array_createCol(int32_t       dimen,
                          const int32_t lower[],
                          const int32_t upper[]);

/**
 * Create a dense int array of the given dimension with specified
 * index bounds in row-major order.  This array owns and manages its data.
 * This function does not initialize the contents of the array.
 */
struct SIDL_int__array *
SIDL_int__array_createRow(int32_t       dimen,
                          const int32_t lower[],
                          const int32_t upper[]);

/**
 * Create a dense one-dimensional vector of ints with a lower
 * index of 0 and an upper index of len-1. This array owns and manages
 * its data.
 * This function does not initialize the contents of the array.
 */
struct SIDL_int__array *
SIDL_int__array_create1d(int32_t len);

/**
 * Create a dense two-dimensional array of ints with a lower
 * indices of (0,0) and an upper indices of (m-1,n-1). The array is
 * stored in column-major order, and it owns and manages its data.
 * This function does not initialize the contents of the array.
 */
struct SIDL_int__array *
SIDL_int__array_create2dCol(int32_t m, int32_t n);

/**
 * Create a dense two-dimensional array of ints with a lower
 * indices of (0,0) and an upper indices of (m-1,n-1). The array is
 * stored in row-major order, and it owns and manages its data.
 * This function does not initialize the contents of the array.
 */
struct SIDL_int__array *
SIDL_int__array_create2dRow(int32_t m, int32_t n);

/**
 * Create a sub-array of another array. This resulting array shares
 * data with the original array. The new array can be of the same
 * dimension or potentially less assuming the original array has
 * dimension greater than 1.  If you are removing dimension, indicate the
 * dimensions to remove by setting numElem[i] to zero for any dimension i
 * that should go away in the new array.  The meaning of each argument
 * is covered below.
 * 
 * src       the array to be created will be a subset of this array. If
 *           this argument is NULL, NULL will be returned. The array
 *           returned borrows data from src, so modifying src or the
 *           returned array will modify both arrays.
 * 
 * dimen     this argument must be greater than zero and less than or
 *           equal to the dimension of src. An illegal value will cause
 *           a NULL return value.
 *           
 * numElem   this specifies how many elements from src should be taken in
 *           each dimension. A zero entry indicates that the dimension
 *           should not appear in the new array.  This argument should be
 *           an array with an entry for each dimension of src.  Passing
 *           NULL here will cause NULL to be returned.  If
 *           srcStart[i] + numElem[i]*srcStride[i] is greater than
 *           upper[i] for src or if srcStart[i] + numElem[i]*srcStride[i]
 *           is less than lower[i] for src, NULL will be returned.
 * 
 * srcStart  this array holds the coordinates of the first element of the
 *           new array. If this argument is NULL, the first element of
 *           src will be the first element of the new array. If non-NULL,
 *           this argument should be an array with an entry for each
 *           dimension of src.  If srcStart[i] is less than lower[i] for
 *           the array src, NULL will be returned.
 * 
 * srcStride this array lets you specify the stride between elements in
 *           each dimension of src. This stride is relative to the
 *           coordinate system of the src array. If this argument is
 *           NULL, the stride is taken to be one in each dimension.
 *           If non-NULL, this argument should be an array with an entry
 *           for each dimension of src.
 * 
 * newLower  this argument is like lower in a create method. It sets the
 *           coordinates for the first element in the new array.  If this
 *           argument is NULL, the values indicated by srcStart will be
 *           used. If non-NULL, this should be an array with dimen
 *           elements.
 */
struct SIDL_int__array *
SIDL_int__array_slice(struct SIDL_int__array *src,
                      int32_t       dimen,
                      const int32_t numElem[],
                      const int32_t *srcStart,
                      const int32_t *srcStride,
                      const int32_t *newStart);

/**
 * Create an array that uses data memory from another source. This initial
 * contents are determined by the data being borrowed.
 */
struct SIDL_int__array *
SIDL_int__array_borrow(int32_t* firstElement,
                       int32_t        dimen,
                       const int32_t  lower[],
                       const int32_t  upper[],
                       const int32_t  stride[]);

/**
 * If array is borrowed, allocate a new self-sufficient array and copy
 * the borrowed array into the new array; otherwise, increment the
 * reference count and return the array passed in. Use this whenever
 * you want to make a copy of a method argument because arrays passed
 * into methods aren't guaranteed to exist after the method call.
 */
struct SIDL_int__array *
SIDL_int__array_smartCopy(struct SIDL_int__array *array);

/**
 * Increment the arrays internal reference count by one. To make a
 * persistent copy (i.e. that lives longer than the current method
 * call) use smartCopy.
 */
void
SIDL_int__array_addReference(struct SIDL_int__array* array);

/**
 * Decrement the arrays internal reference count by one. If the reference
 * count goes to zero, destroy the array.
 * Return true iff the array is destroyed
 */
void
SIDL_int__array_deleteReference(struct SIDL_int__array* array);

/**
 * Retrieve element i1 of a one-dimensional array.
 */
int32_t
SIDL_int__array_get1(const struct SIDL_int__array* array,
                     const int32_t i1);

/**
 * Retrieve element (i1,i2) of a two-dimensional array.
 */
int32_t
SIDL_int__array_get2(const struct SIDL_int__array* array,
                     const int32_t i1,
                     const int32_t i2);

/**
 * Retrieve element (i1,i2,i3) of a three-dimensional array.
 */
int32_t
SIDL_int__array_get3(const struct SIDL_int__array* array,
                     const int32_t i1,
                     const int32_t i2,
                     const int32_t i3);

/**
 * Retrieve element (i1,i2,i3,i4) of a four-dimensional array.
 */
int32_t
SIDL_int__array_get4(const struct SIDL_int__array* array,
                     const int32_t i1,
                     const int32_t i2,
                     const int32_t i3,
                     const int32_t i4);

/**
 * Retrieve element indices of an n-dimensional array. Indices is assumed
 * to have the right number of elements for the dimension of array.
 */
int32_t
SIDL_int__array_get(const struct SIDL_int__array* array,
                    const int32_t indices[]);

/**
 * Set element i1 of a one-dimensional array to value.
 */
void
SIDL_int__array_set1(struct SIDL_int__array* array,
                     const int32_t i1,
                     const int32_t value);

/**
 * Set element (i1,i2) of a two-dimensional array to value.
 */
void
SIDL_int__array_set2(struct SIDL_int__array* array,
                     const int32_t i1,
                     const int32_t i2,
                     const int32_t value);

/**
 * Set element (i1,i2,i3) of a three-dimensional array to value.
 */
void
SIDL_int__array_set3(struct SIDL_int__array* array,
                     const int32_t i1,
                     const int32_t i2,
                     const int32_t i3,
                     const int32_t value);

/**
 * Set element (i1,i2,i3,i4) of a four-dimensional array to value.
 */
void
SIDL_int__array_set4(struct SIDL_int__array* array,
                     const int32_t i1,
                     const int32_t i2,
                     const int32_t i3,
                     const int32_t i4,
                     const int32_t value);

/**
 * Set element indices of an n-dimensional array to value. indices is assumed
 * to have the right number of elements for the dimension of array.
 */
void
SIDL_int__array_set(struct SIDL_int__array* array,
                    const int32_t indices[],
                    const int32_t value);

/**
 * Return the dimension of array. If the array pointer is NULL,
 * zero is returned.
 */
int32_t
SIDL_int__array_dimen(const struct SIDL_int__array* array);

/**
 * Return the lower index bound on dimension ind. If ind is not a valid
 * dimension, zero is returned. The valid range for ind is 0 to dimen-1.
 */
int32_t
SIDL_int__array_lower(const struct SIDL_int__array* array,
                      const int32_t ind);

/**
 * Return the upper index bound on dimension ind. If ind is not a valid
 * dimension, negative one is returned. The valid range for ind is 0 to
 * dimen-1.
 */
int32_t
SIDL_int__array_upper(const struct SIDL_int__array* array,
                      const int32_t ind);

/**
 * Return the stride of dimension ind. If ind is not a valid
 * dimension, zero is returned. The valid range for ind is 0 to
 * dimen-1.
 */
int32_t
SIDL_int__array_stride(const struct SIDL_int__array* array,
                       const int32_t ind);

/**
 * Return a true value iff the array is a contiguous column-major ordered
 * array.  A NULL array argument causes 0 to be returned.
 */
SIDL_bool
SIDL_int__array_isColumnOrder(const struct SIDL_int__array* array);

/**
 * Return a true value iff the array is a contiguous row-major ordered
 * array.  A NULL array argument causes 0 to be returned.
 */
SIDL_bool
SIDL_int__array_isRowOrder(const struct SIDL_int__array* array);

/**
 * Copy the contents of one array (src) to a second array (dest). For
 * the copy to take place, both arrays must exist and be of the same
 * dimension. This method will not modify dest's size, index bounds,
 * or stride; only the array element values of dest may be changed by
 * this function. No part of src is ever changed by copy.
 * 
 * On exit, dest[i][j][k]... = src[i][j][k]... for all indices i,j,k...
 * that are in both arrays. If dest and src have no indices in common,
 * nothing is copied. For example, if src is a 1-d array with elements
 * 0-5 and dest is a 1-d array with elements 2-3, this function will
 * make the following assignments:
 *   dest[2] = src[2],
 *   dest[3] = src[3].
 * The function copied the elements that both arrays have in common.
 * If dest had elements 4-10, this function will make the following
 * assignments:
 *   dest[4] = src[4],
 *   dest[5] = src[5].
 * 
 */
void
SIDL_int__array_copy(const struct SIDL_int__array* src,
                           struct SIDL_int__array* dest);

/**
 * If necessary, convert a general matrix into a matrix with the required
 * properties. This checks the dimension and ordering of the matrix.
 * If both these match, it simply returns a new reference to the existing
 * matrix. If the dimension of the incoming array doesn't match, it
 * returns NULL. If the ordering of the incoming array doesn't match the
 * specification, a new array is created with the desired ordering and
 * the content of the incoming array is copied to the new array.
 * 
 * The ordering parameter should be one of the constants defined in
 * enum SIDL_array_ordering (e.g. SIDL_general_order,
 * SIDL_column_major_order, or SIDL_row_major_order). If you
 * specify SIDL_general_order, this routine will only check the
 * dimension because any matrix is SIDL_general_order.
 * 
 * The caller assumes ownership of the returned reference unless it's NULL.
 * 
 */
struct SIDL_int__array*
SIDL_int__array_ensure(struct SIDL_int__array* src,
                       int32_t                dimen,
                       int                    ordering);

/**
 * Return a pointer to the first element of the data space of the array.
 * Using the lower and stride information, you can access elements of the
 * array without using a function call. NULL is returned iff array is NULL.
 * 
 * Direct access should only be used when efficiency requires it.
 */
int32_t *
SIDL_int__array_first(const struct SIDL_int__array* array);

#ifdef __cplusplus
}
#endif
#endif /* included_SIDL_int_IOR_h */
