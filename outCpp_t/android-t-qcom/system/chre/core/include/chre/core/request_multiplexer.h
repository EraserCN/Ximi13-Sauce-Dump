/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CHRE_CORE_REQUEST_MULTIPLEXER_H_
#define CHRE_CORE_REQUEST_MULTIPLEXER_H_

#include "chre/util/dynamic_vector.h"
#include "chre/util/non_copyable.h"

namespace chre {

/**
 * This class multiplexes multiple generic requests into one maximal request.
 * This is a templated class and the template type is required to implement the
 * following API:
 *
 * 1. RequestType();
 *
 *     RequestTypes must be default constructable and constructed to a state
 *     that is the lowest possible priority for a request. The lowest priority
 *     state must be equivalent to being restored to the initial state for the
 *     RequestType.
 *
 * 2. bool isEquivalentTo(const RequestType& request) const;
 *
 *     Perform a comparison to another request to determine if they are
 *     equivalent. This is different from equality in that the request object
 *     may have other internal state that makes two requests different, but
 *     their net request is considered to be equal. This function returns true
 *     if the requests are equivalent.
 *
 * 3. bool mergeWith(const RequestType& request);
 *
 *     Merges a request with the current request. This method must set the
 *     attributes of the current request to the highest priority attributes of
 *     both the current and other. The method returns true if the current
 *     request has changed.
 *
 *     NOTE: The request multiplexer makes use of move-semantics for certain
 *     operations so mergeWith must perform a deep copy when creating the merged
 *     output.
 */
template <typename RequestType>
class RequestMultiplexer : public NonCopyable {
 public:
  RequestMultiplexer() = default;
  RequestMultiplexer(RequestMultiplexer &&other) {
    *this = std::move(other);
  }

  RequestMultiplexer &operator=(RequestMultiplexer &&other) {
    mRequests = std::move(other.mRequests);

    mCurrentMaximalRequest = other.mCurrentMaximalRequest;
    other.mCurrentMaximalRequest = RequestType();

    return *this;
  }

  /**
   * Adds a request to the list of requests being managed by this multiplexer.
   *
   * @param request The request to add to the list.
   * @param index A non-null pointer to an index that is populated with the
   *              location that the request was added.
   * @param maximalRequestChanged A non-null pointer to a bool that is set to
   *        true if current maximal request has changed. The user of this API
   *        must query the getCurrentMaximalRequest method to get the new
   *        maximal request.
   * @return Returns false if the request cannot be inserted into the
   *         multiplexer.
   */
  bool addRequest(const RequestType &request, size_t *index,
                  bool *maximalRequestChanged);

  /**
   * Same as addRequest above, but uses move semantics.
   */
  bool addRequest(RequestType &&request, size_t *index,
                  bool *maximalRequestChanged);

  /**
   * Updates a request in the list of requests being managed by this
   * multiplexer.
   *
   * @param index The index of the request to be updated. This param must fall
   *        in the range of indices provided by getRequests().
   * @param request The request to update to.
   * @param maximalRequestChanged A non-null pointer to a bool that is set to
   *        true if the current maximal request has changed. The user of this
   *        API must query the getCurrentMaximalRequest() method to get the new
   *        maximal request.
   */
  void updateRequest(size_t index, const RequestType &request,
                     bool *maximalRequestChanged);

  /**
   * Same as updateRequest above, but uses move semantics.
   */
  void updateRequest(size_t index, RequestType &&request,
                     bool *maximalRequestChanged);

  /**
   * Removes a request from the list of requests being managed by this
   * multiplexer.
   *
   * @param index The index of the request to be removed. This index must fall
   *        in the range of indices provided by getRequests().
   * @param maximalRequestChanged A non-null pointer to a bool that is set to
   *        true if the current maximal request has changed. The user of this
   *        API must query the getCurrentMaximalRequest method to get the new
   *        maximal request.
   */
  void removeRequest(size_t index, bool *maximalRequestChanged);

  /*
   * Removes all requests managed by this multiplexer. The maximal request will
   * change if the multiplexer is not empty.
   *
   * @param maximalRequestChanged A non-null pointer to a bool that is set to
   *        true if the current maximal request has changed.
   */
  void removeAllRequests(bool *maximalRequestChanged);

  /**
   * @return The list of requests managed by this multiplexer.
   */
  const DynamicVector<RequestType> &getRequests() const;

  /**
   * @return Returns the current maximal request.
   */
  const RequestType &getCurrentMaximalRequest() const;

 protected:
  //! The list of requests to track.
  DynamicVector<RequestType> mRequests;

  /**
   * Iterates over all tracked requests and updates the current maximal request
   * if it has changed.
   *
   * @param maximalRequestChanged A non-null pointer to a bool that is set to
   *        true if the current maximal request has changed.
   */
  void updateMaximalRequest(bool *maximalRequestChanged);

 private:
  //! The current maximal request as generated by this multiplexer.
  RequestType mCurrentMaximalRequest;
};

}  // namespace chre

#include "chre/core/request_multiplexer_impl.h"

#endif  // CHRE_CORE_REQUEST_MULTIPLEXER_H_
