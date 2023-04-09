// Copyright 2020 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_HEAP_CPPGC_MARKING_VERIFIER_H_
#define V8_HEAP_CPPGC_MARKING_VERIFIER_H_

#include <unordered_set>

#include "src/base/optional.h"
#include "src/heap/base/stack.h"
#include "src/heap/cppgc/heap-object-header.h"
#include "src/heap/cppgc/heap-visitor.h"
#include "src/heap/cppgc/heap.h"
#include "src/heap/cppgc/visitor.h"

namespace cppgc {
namespace internal {

class VerificationState {
 public:
  void VerifyMarked(const void*) const;
  void SetCurrentParent(const HeapObjectHeader* header) { parent_ = header; }

  // No parent means parent was on stack.
  bool IsParentOnStack() const { return !parent_; }

 private:
  const HeapObjectHeader* parent_ = nullptr;
};

class V8_EXPORT_PRIVATE MarkingVerifierBase
    : private HeapVisitor<MarkingVerifierBase>,
      public ConservativeTracingVisitor,
      public heap::base::StackVisitor {
  friend class HeapVisitor<MarkingVerifierBase>;

 public:
  ~MarkingVerifierBase() override = default;

  MarkingVerifierBase(const MarkingVerifierBase&) = delete;
  MarkingVerifierBase& operator=(const MarkingVerifierBase&) = delete;

  void Run(StackState, uintptr_t, v8::base::Optional<size_t>);

 protected:
  MarkingVerifierBase(HeapBase&, CollectionType, VerificationState&,
                      std::unique_ptr<cppgc::Visitor>);

 private:
  void VisitInConstructionConservatively(HeapObjectHeader&,
                                         TraceConservativelyCallback) final;
  void VisitPointer(const void*) final;

  bool VisitHeapObjectHeader(HeapObjectHeader&);

  VerificationState& verification_state_;
  std::unique_ptr<cppgc::Visitor> visitor_;

  std::unordered_set<const HeapObjectHeader*> in_construction_objects_heap_;
  std::unordered_set<const HeapObjectHeader*> in_construction_objects_stack_;
  std::unordered_set<const HeapObjectHeader*>* in_construction_objects_ =
      &in_construction_objects_heap_;
  size_t verifier_found_marked_bytes_ = 0;
  bool verifier_found_marked_bytes_are_exact_ = true;
  CollectionType collection_type_;
};

class V8_EXPORT_PRIVATE MarkingVerifier final : public MarkingVerifierBase {
 public:
  MarkingVerifier(HeapBase&, CollectionType);
  ~MarkingVerifier() final = default;

 private:
  VerificationState state_;
};

}  // namespace internal
}  // namespace cppgc

#endif  // V8_HEAP_CPPGC_MARKING_VERIFIER_H_
