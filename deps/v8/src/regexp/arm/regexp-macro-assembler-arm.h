// Copyright 2012 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_REGEXP_ARM_REGEXP_MACRO_ASSEMBLER_ARM_H_
#define V8_REGEXP_ARM_REGEXP_MACRO_ASSEMBLER_ARM_H_

#include "src/codegen/macro-assembler.h"
#include "src/regexp/regexp-macro-assembler.h"

namespace v8 {
namespace internal {

class V8_EXPORT_PRIVATE RegExpMacroAssemblerARM
    : public NativeRegExpMacroAssembler {
 public:
  RegExpMacroAssemblerARM(Isolate* isolate, Zone* zone, Mode mode,
                          int registers_to_save);
  ~RegExpMacroAssemblerARM() override;
  void AbortedCodeGeneration() override;
  int stack_limit_slack() override;
  void AdvanceCurrentPosition(int by) override;
  void AdvanceRegister(int reg, int by) override;
  void Backtrack() override;
  void Bind(Label* label) override;
  void CheckAtStart(int cp_offset, Label* on_at_start) override;
  void CheckCharacter(unsigned c, Label* on_equal) override;
  void CheckCharacterAfterAnd(unsigned c, unsigned mask,
                              Label* on_equal) override;
  void CheckCharacterGT(base::uc16 limit, Label* on_greater) override;
  void CheckCharacterLT(base::uc16 limit, Label* on_less) override;
  // A "greedy loop" is a loop that is both greedy and with a simple
  // body. It has a particularly simple implementation.
  void CheckGreedyLoop(Label* on_tos_equals_current_position) override;
  void CheckNotAtStart(int cp_offset, Label* on_not_at_start) override;
  void CheckNotBackReference(int start_reg, bool read_backward,
                             Label* on_no_match) override;
  void CheckNotBackReferenceIgnoreCase(int start_reg, bool read_backward,
                                       bool unicode,
                                       Label* on_no_match) override;
  void CheckNotCharacter(unsigned c, Label* on_not_equal) override;
  void CheckNotCharacterAfterAnd(unsigned c, unsigned mask,
                                 Label* on_not_equal) override;
  void CheckNotCharacterAfterMinusAnd(base::uc16 c, base::uc16 minus,
                                      base::uc16 mask,
                                      Label* on_not_equal) override;
  void CheckCharacterInRange(base::uc16 from, base::uc16 to,
                             Label* on_in_range) override;
  void CheckCharacterNotInRange(base::uc16 from, base::uc16 to,
                                Label* on_not_in_range) override;
  bool CheckCharacterInRangeArray(const ZoneList<CharacterRange>* ranges,
                                  Label* on_in_range) override;
  bool CheckCharacterNotInRangeArray(const ZoneList<CharacterRange>* ranges,
                                     Label* on_not_in_range) override;
  void CheckBitInTable(Handle<ByteArray> table, Label* on_bit_set) override;

  // Checks whether the given offset from the current position is before
  // the end of the string.
  void CheckPosition(int cp_offset, Label* on_outside_input) override;
  bool CheckSpecialClassRanges(StandardCharacterSet type,
                               Label* on_no_match) override;
  void Fail() override;
  Handle<HeapObject> GetCode(Handle<String> source) override;
  void GoTo(Label* label) override;
  void IfRegisterGE(int reg, int comparand, Label* if_ge) override;
  void IfRegisterLT(int reg, int comparand, Label* if_lt) override;
  void IfRegisterEqPos(int reg, Label* if_eq) override;
  IrregexpImplementation Implementation() override;
  void LoadCurrentCharacterUnchecked(int cp_offset,
                                     int character_count) override;
  void PopCurrentPosition() override;
  void PopRegister(int register_index) override;
  void PushBacktrack(Label* label) override;
  void PushCurrentPosition() override;
  void PushRegister(int register_index,
                    StackCheckFlag check_stack_limit) override;
  void ReadCurrentPositionFromRegister(int reg) override;
  void ReadStackPointerFromRegister(int reg) override;
  void SetCurrentPositionFromEnd(int by) override;
  void SetRegister(int register_index, int to) override;
  bool Succeed() override;
  void WriteCurrentPositionToRegister(int reg, int cp_offset) override;
  void ClearRegisters(int reg_from, int reg_to) override;
  void WriteStackPointerToRegister(int reg) override;

  // Called from RegExp if the stack-guard is triggered.
  // If the code object is relocated, the return address is fixed before
  // returning.
  // {raw_code} is an Address because this is called via ExternalReference.
  static int CheckStackGuardState(Address* return_address, Address raw_code,
                                  Address re_frame);

 private:
  // Offsets from frame_pointer() of function parameters and stored registers.
  static const int kFramePointer = 0;

  // Above the frame pointer - Stored registers and stack passed parameters.
  static const int kStoredRegisters = kFramePointer;
  // Return address (stored from link register, read into pc on return).
  static const int kReturnAddress = kStoredRegisters + 8 * kPointerSize;
  // Stack parameters placed by caller.
  static const int kRegisterOutput = kReturnAddress + kPointerSize;
  static const int kNumOutputRegisters = kRegisterOutput + kPointerSize;
  static const int kDirectCall = kNumOutputRegisters + kPointerSize;
  static const int kIsolate = kDirectCall + kPointerSize;

  // Below the frame pointer.
  // Register parameters stored by setup code.
  static const int kInputEnd = kFramePointer - kPointerSize;
  static const int kInputStart = kInputEnd - kPointerSize;
  static const int kStartIndex = kInputStart - kPointerSize;
  static const int kInputString = kStartIndex - kPointerSize;
  // When adding local variables remember to push space for them in
  // the frame in GetCode.
  static const int kSuccessfulCaptures = kInputString - kPointerSize;
  static const int kStringStartMinusOne = kSuccessfulCaptures - kPointerSize;
  static const int kBacktrackCount = kStringStartMinusOne - kSystemPointerSize;
  // Stores the initial value of the regexp stack pointer in a
  // position-independent representation (in case the regexp stack grows and
  // thus moves).
  static const int kRegExpStackBasePointer =
      kBacktrackCount - kSystemPointerSize;

  // First register address. Following registers are below it on the stack.
  static const int kRegisterZero = kRegExpStackBasePointer - kSystemPointerSize;

  // Initial size of code buffer.
  static const int kRegExpCodeSize = 1024;

  static const int kBacktrackConstantPoolSize = 4;

  // Check whether preemption has been requested.
  void CheckPreemption();

  // Check whether we are exceeding the stack limit on the backtrack stack.
  void CheckStackLimit();

  void CallCheckStackGuardState();
  void CallIsCharacterInRangeArray(const ZoneList<CharacterRange>* ranges);

  // The ebp-relative location of a regexp register.
  MemOperand register_location(int register_index);

  // Register holding the current input position as negative offset from
  // the end of the string.
  static constexpr Register current_input_offset() { return r6; }

  // The register containing the current character after LoadCurrentCharacter.
  static constexpr Register current_character() { return r7; }

  // Register holding address of the end of the input string.
  static constexpr Register end_of_input_address() { return r10; }

  // Register holding the frame address. Local variables, parameters and
  // regexp registers are addressed relative to this.
  static constexpr Register frame_pointer() { return fp; }

  // The register containing the backtrack stack top. Provides a meaningful
  // name to the register.
  static constexpr Register backtrack_stackpointer() { return r8; }

  // Register holding pointer to the current code object.
  static constexpr Register code_pointer() { return r5; }

  // Byte size of chars in the string to match (decided by the Mode argument)
  inline int char_size() const { return static_cast<int>(mode_); }

  // Equivalent to a conditional branch to the label, unless the label
  // is nullptr, in which case it is a conditional Backtrack.
  void BranchOrBacktrack(Condition condition, Label* to);

  // Call and return internally in the generated code in a way that
  // is GC-safe (i.e., doesn't leave absolute code addresses on the stack)
  inline void SafeCall(Label* to, Condition cond = al);
  inline void SafeReturn();
  inline void SafeCallTarget(Label* name);

  // Pushes the value of a register on the backtrack stack. Decrements the
  // stack pointer by a word size and stores the register's value there.
  inline void Push(Register source);

  // Pops a value from the backtrack stack. Reads the word at the stack pointer
  // and increments it by a word size.
  inline void Pop(Register target);

  void LoadRegExpStackPointerFromMemory(Register dst);
  void StoreRegExpStackPointerToMemory(Register src, Register scratch);
  void PushRegExpBasePointer(Register stack_pointer, Register scratch);
  void PopRegExpBasePointer(Register stack_pointer_out, Register scratch);

  Isolate* isolate() const { return masm_->isolate(); }

  const std::unique_ptr<MacroAssembler> masm_;
  const NoRootArrayScope no_root_array_scope_;

  // Which mode to generate code for (Latin1 or UC16).
  const Mode mode_;

  // One greater than maximal register index actually used.
  int num_registers_;

  // Number of registers to output at the end (the saved registers
  // are always 0..num_saved_registers_-1)
  const int num_saved_registers_;

  // Labels used internally.
  Label entry_label_;
  Label start_label_;
  Label success_label_;
  Label backtrack_label_;
  Label exit_label_;
  Label check_preempt_label_;
  Label stack_overflow_label_;
  Label fallback_label_;
};

}  // namespace internal
}  // namespace v8

#endif  // V8_REGEXP_ARM_REGEXP_MACRO_ASSEMBLER_ARM_H_
